/*
 * TritSys: Ternary Computing System
 * A command-line utility for ternary arithmetic and operations.
 */

/*
 * Key Updates Recap 1.00
 * Ternary Arithmetic Operations:
 * t81bigint_add, t81bigint_sub, t81bigint_mul, t81bigint_div, t81bigint_mod, t81bigint_exp, t81bigint_tand, t81bigint_tor fully implemented.
 *
 * Integrated into tritjs_eval_expression with operators +, -, *, /, %, &, |.
 *
 * Hanoi Solver:
 * Updated solve_hanoi to pause every n lines, configurable via command-line (-n N PAUSE) and interactive mode (hanoi N PAUSE).
 * 
 * Opcode System:
 * Added TSUB, TMOD, TAND, TOR to discrete_opcode_execute.
 * 
 * Command-Line Utility:
 * Enhanced to support all operations, including exponentiation (-p) and dynamic Hanoi pausing.
 * 
 * Compilation Notes
 * User Space: Compile with gcc -o tritsys tritsys.c -lreadline -lm.
 * 
 * Kernel Module: Use a kernel build system (e.g., Makefile with obj-m += axion.o) for the __KERNEL__ section.
 */

/* ============================================================
 * Section 1: Shared Header (ternary_common.h)
 */
#ifndef TERNARY_COMMON_H
#define TERNARY_COMMON_H

#ifdef __KERNEL__
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/wait.h>
#define TS_MALLOC(sz) kmalloc((sz), GFP_KERNEL)
#define TS_FREE(ptr) kfree(ptr)
#define TS_PRINT(fmt, ...) printk(KERN_INFO "[%s %ld] " fmt, log_names[LOG_INFO], jiffies, ##__VA_ARGS__)
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#define TS_MALLOC(sz) malloc(sz)
#define TS_FREE(ptr) free(ptr)
#define TS_PRINT(fmt, ...) do { time_t t = time(NULL); fprintf(stderr, "[%s %s] " fmt, log_names[LOG_INFO], ctime(&t), ##__VA_ARGS__); } while (0)
#endif

#define TERNARY_NEGATIVE -1
#define TERNARY_ZERO      0
#define TERNARY_POSITIVE  1
#define BASE_81 81
#define PI 3.14159265358979323846

enum LogLevel { LOG_DEBUG = 0, LOG_INFO, LOG_WARN, LOG_ERROR };
static const char *log_names[] = {"DEBUG", "INFO", "WARN", "ERROR"};
extern int log_level;

#define TADD      0x01
#define TSUB      0x02
#define TMUL      0x03
#define TMOD      0x04
#define TAND      0x05
#define TOR       0x06
#define TMAT_ADD  0x08
#define TMAT_MUL  0x09
#define THANOI    0x0A
#define TEXP      0x0B
#define TGCD      0x0C

typedef enum {
    TERNARY_NO_ERROR = 0,
    TERNARY_ERR_MEMALLOC,
    TERNARY_ERR_INVALID_INPUT,
    TERNARY_ERR_DIVZERO
} TernaryError;

typedef struct {
    int sign;
    unsigned char *digits;
    size_t len;
    int is_mapped;
    int fd;
} T81BigInt;

typedef struct {
    int rows;
    int cols;
    T81BigInt *data;
} T81Matrix;

TernaryError allocate_t81bigint(T81BigInt *x, size_t len);
void free_t81bigint(T81BigInt *x);
TernaryError t81bigint_copy(const T81BigInt *src, T81BigInt *dest);
TernaryError t81bigint_add(const T81BigInt *a, const T81BigInt *b, T81BigInt **result);
TernaryError t81bigint_sub(const T81BigInt *a, const T81BigInt *b, T81BigInt **result);
TernaryError t81bigint_mul(const T81BigInt *a, const T81BigInt *b, T81BigInt **result);
TernaryError t81bigint_div(const T81BigInt *a, const T81BigInt *b, T81BigInt **quotient);
TernaryError t81bigint_mod(const T81BigInt *a, const T81BigInt *b, T81BigInt **result);
TernaryError t81bigint_exp(const T81BigInt *base, unsigned int exponent, T81BigInt **result);
TernaryError t81bigint_tand(const T81BigInt *a, const T81BigInt *b, T81BigInt **result);
TernaryError t81bigint_tor(const T81BigInt *a, const T81BigInt *b, T81BigInt **result);
T81BigInt *t81bigint_from_int(int num);
int t81bigint_to_int(const T81BigInt *num, TernaryError *err);
void t81bigint_to_string(const T81BigInt *num, char *buffer);
T81Matrix *create_matrix(int rows, int cols);
void free_matrix(T81Matrix *m);
TernaryError tmat_add(T81Matrix *a, T81Matrix *b, T81Matrix **result);
TernaryError tmat_mul(T81Matrix *a, T81Matrix *b, T81Matrix **result);
T81Matrix *tmat_transpose(T81Matrix *m);
void discrete_opcode_encode(int opcode, char *encoded_buffer);
int discrete_opcode_validate(const char *encoded_opcode);
int discrete_opcode_execute(const char *encoded_opcode, int operand1, int operand2);
T81BigInt *tritjs_eval_expression(const char *expr);

#endif /* TERNARY_COMMON_H */

/* ============================================================
 * Section 2: Axion Kernel Module
 */
#ifdef __KERNEL__
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include <linux/device.h>
#include <linux/mm.h>
#include "ternary_common.h"

#define DEVICE_NAME "axion"
#define SHARED_BUFFER_SIZE 4096
#define T81_MMAP_THRESHOLD (500 * 1024)

int log_level = LOG_INFO;

struct tritjs_call {
    int op;
    T81BigInt in1;
    T81BigInt in2;
    T81Matrix mat_in1;
    T81Matrix mat_in2;
    union { T81BigInt scalar; T81Matrix matrix; } result;
};

struct axion_state {
    void *shared_buffer;
    wait_queue_head_t tritjs_wait;
    volatile int request_pending;
};

#define AXION_CALL_TRITJS _IOWR('a', 1, struct tritjs_call)

static dev_t dev_num;
static struct cdev axion_cdev;
static struct class *axion_class;
static struct device *axion_device;
static struct axion_state state = { .request_pending = 0 };

TernaryError allocate_t81bigint(T81BigInt *x, size_t len) {
    size_t bytes = len ? len : 1;
    x->len = len;
    x->is_mapped = 0;
    x->fd = -1;
    if (bytes < T81_MMAP_THRESHOLD) {
        x->digits = kmalloc(bytes, GFP_KERNEL);
        if (!x->digits) return TERNARY_ERR_MEMALLOC;
        memset(x->digits, 0, bytes);
    } else {
        struct file *file = shmem_file_setup("axion_t81", bytes, 0);
        if (IS_ERR(file)) return TERNARY_ERR_MEMALLOC;
        x->fd = get_unused_fd_flags(O_RDWR);
        if (x->fd < 0) { fput(file); return TERNARY_ERR_MEMALLOC; }
        fd_install(x->fd, file);
        x->digits = vm_map_ram(NULL, bytes / PAGE_SIZE + 1, 0, PAGE_KERNEL);
        if (!x->digits) { close(x->fd); return TERNARY_ERR_MEMALLOC; }
        x->is_mapped = 1;
        memset(x->digits, 0, bytes);
    }
    return TERNARY_NO_ERROR;
}

void free_t81bigint(T81BigInt *x) {
    if (!x || !x->digits) return;
    if (x->is_mapped) {
        vm_unmap_ram(x->digits, x->len / PAGE_SIZE + 1);
        close(x->fd);
    } else {
        kfree(x->digits);
    }
}

static int call_tritjs(struct tritjs_call *call) {
    if (!state.shared_buffer) return -EINVAL;
    if (sizeof(*call) > SHARED_BUFFER_SIZE) {
        TS_PRINT("Call structure too large for shared buffer\n");
        return -EINVAL;
    }
    state.request_pending = 1;
    memcpy(state.shared_buffer, call, sizeof(*call));
    TS_PRINT("Waiting for TritJS response\n");
    if (wait_event_interruptible_timeout(state.tritjs_wait, !state.request_pending, HZ * 5) == 0) {
        TS_PRINT("Timeout waiting for TritJS response\n");
        state.request_pending = 0;
        return -ETIMEDOUT;
    }
    if (state.request_pending) return -ERESTARTSYS;
    memcpy(call, state.shared_buffer, sizeof(*call));
    return 0;
}

static long axion_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    if (cmd == AXION_CALL_TRITJS) {
        struct tritjs_call call;
        if (copy_from_user(&call, (void __user *)arg, sizeof(call))) return -EFAULT;
        if (call_tritjs(&call)) return -EINVAL;
        if (copy_to_user((void __user *)arg, &call, sizeof(call))) return -EFAULT;
        return 0;
    }
    return -EINVAL;
}

static const struct file_operations axion_fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = axion_ioctl
};

static int __init axion_init(void) {
    int ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) return ret;
    cdev_init(&axion_cdev, &axion_fops);
    if (cdev_add(&axion_cdev, dev_num, 1) < 0) goto err_dev;
    axion_class = class_create(THIS_MODULE, DEVICE_NAME);
    if (IS_ERR(axion_class)) { ret = PTR_ERR(axion_class); goto err_cdev; }
    axion_device = device_create(axion_class, NULL, dev_num, NULL, DEVICE_NAME);
    if (IS_ERR(axion_device)) { ret = PTR_ERR(axion_device); goto err_class; }
    state.shared_buffer = vmalloc(SHARED_BUFFER_SIZE);
    if (!state.shared_buffer) { ret = -ENOMEM; goto err_device; }
    init_waitqueue_head(&state.tritjs_wait);
    TS_PRINT("Axion initialized\n");
    return 0;
err_device:
    device_destroy(axion_class, dev_num);
err_class:
    class_destroy(axion_class);
err_cdev:
    cdev_del(&axion_cdev);
err_dev:
    unregister_chrdev_region(dev_num, 1);
    return ret;
}

static void __exit axion_exit(void) {
    if (state.shared_buffer) vfree(state.shared_buffer);
    device_destroy(axion_class, dev_num);
    class_destroy(axion_class);
    cdev_del(&axion_cdev);
    unregister_chrdev_region(dev_num, 1);
    TS_PRINT("Axion unloaded\n");
}

module_init(axion_init);
module_exit(axion_exit);
MODULE_LICENSE("GPL");
#endif

/* ============================================================
 * Section 3: Extended Operations
 */
TernaryError allocate_t81bigint(T81BigInt *x, size_t len) {
    size_t bytes = len ? len : 1;
    x->len = len;
    x->is_mapped = 0;
    x->fd = -1;
    x->digits = TS_MALLOC(bytes);
    if (!x->digits) return TERNARY_ERR_MEMALLOC;
    memset(x->digits, 0, bytes);
    return TERNARY_NO_ERROR;
}

void free_t81bigint(T81BigInt *x) {
    if (!x || !x->digits) return;
    TS_FREE(x->digits);
    x->digits = NULL;
}

TernaryError t81bigint_copy(const T81BigInt *src, T81BigInt *dest) {
    if (allocate_t81bigint(dest, src->len) != TERNARY_NO_ERROR) return TERNARY_ERR_MEMALLOC;
    memcpy(dest->digits, src->digits, src->len);
    dest->sign = src->sign;
    return TERNARY_NO_ERROR;
}

TernaryError t81bigint_add(const T81BigInt *a, const T81BigInt *b, T81BigInt **result) {
    size_t max_len = (a->len > b->len) ? a->len : b->len;
    T81BigInt *res = TS_MALLOC(sizeof(T81BigInt));
    if (!res) return TERNARY_ERR_MEMALLOC;
    if (allocate_t81bigint(res, max_len + 1) != TERNARY_NO_ERROR) {
        TS_FREE(res);
        return TERNARY_ERR_MEMALLOC;
    }
    int carry = 0;
    for (size_t i = 0; i < max_len || carry; i++) {
        if (i >= res->len) break;
        int digit_a = (i < a->len) ? (signed char)a->digits[i] * a->sign : 0;
        int digit_b = (i < b->len) ? (signed char)b->digits[i] * b->sign : 0;
        int sum = digit_a + digit_b + carry;
        carry = 0;
        while (sum > 1) { sum -= 3; carry++; }
        while (sum < -1) { sum += 3; carry--; }
        res->digits[i] = (unsigned char)sum;
    }
    res->sign = (carry < 0) ? TERNARY_NEGATIVE : (carry > 0) ? TERNARY_POSITIVE : TERNARY_ZERO;
    if (res->sign == TERNARY_ZERO && max_len == 0) res->sign = TERNARY_ZERO;
    *result = res;
    return TERNARY_NO_ERROR;
}

TernaryError t81bigint_sub(const T81BigInt *a, const T81BigInt *b, T81BigInt **result) {
    if (!a || !b || !result) return TERNARY_ERR_INVALID_INPUT;
    T81BigInt *neg_b = TS_MALLOC(sizeof(T81BigInt));
    if (!neg_b || t81bigint_copy(b, neg_b) != TERNARY_NO_ERROR) {
        TS_FREE(neg_b);
        return TERNARY_ERR_MEMALLOC;
    }
    neg_b->sign = (b->sign == TERNARY_POSITIVE) ? TERNARY_NEGATIVE : 
                  (b->sign == TERNARY_NEGATIVE) ? TERNARY_POSITIVE : TERNARY_ZERO;
    TernaryError err = t81bigint_add(a, neg_b, result);
    free_t81bigint(neg_b);
    TS_FREE(neg_b);
    return err;
}

static void fft(double *a, size_t n, int inverse) {
    if (n <= 1) return;

    double *even = TS_MALLOC(n / 2 * sizeof(double));
    double *odd = TS_MALLOC(n / 2 * sizeof(double));
    if (!even || !odd) {
        TS_FREE(even); TS_FREE(odd);
        return;
    }

    for (size_t i = 0; i < n / 2; i++) {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }

    fft(even, n / 2, inverse);
    fft(odd, n / 2, inverse);

    for (size_t k = 0; k < n / 2; k++) {
        double theta = (inverse ? -2.0 : 2.0) * PI * k / n;
        double w_re = cos(theta);
        double w_im = sin(theta);
        double t_re = odd[k] * w_re - odd[k] * w_im;
        a[k] = even[k] + t_re;
        a[k + n / 2] = even[k] - t_re;
        if (inverse) {
            a[k] /= 2;
            a[k + n / 2] /= 2;
        }
    }

    TS_FREE(even);
    TS_FREE(odd);
}

TernaryError t81bigint_mul(const T81BigInt *a, const T81BigInt *b, T81BigInt **result) {
    if (a->sign == TERNARY_ZERO || b->sign == TERNARY_ZERO) {
        *result = TS_MALLOC(sizeof(T81BigInt));
        if (allocate_t81bigint(*result, 1) != TERNARY_NO_ERROR) return TERNARY_ERR_MEMALLOC;
        (*result)->sign = TERNARY_ZERO;
        (*result)->digits[0] = 0;
        return TERNARY_NO_ERROR;
    }

    size_t len = a->len + b->len;
    size_t n = 1;
    while (n < len) n <<= 1;

    double *a_fft = TS_MALLOC(n * sizeof(double));
    double *b_fft = TS_MALLOC(n * sizeof(double));
    if (!a_fft || !b_fft) {
        TS_FREE(a_fft); TS_FREE(b_fft);
        return TERNARY_ERR_MEMALLOC;
    }
    memset(a_fft, 0, n * sizeof(double));
    memset(b_fft, 0, n * sizeof(double));

    for (size_t i = 0; i < a->len; i++) a_fft[i] = (signed char)a->digits[i] * a->sign;
    for (size_t i = 0; i < b->len; i++) b_fft[i] = (signed char)b->digits[i] * b->sign;

    fft(a_fft, n, 0);
    fft(b_fft, n, 0);

    double *c_fft = TS_MALLOC(n * sizeof(double));
    if (!c_fft) {
        TS_FREE(a_fft); TS_FREE(b_fft); TS_FREE(c_fft);
        return TERNARY_ERR_MEMALLOC;
    }
    for (size_t i = 0; i < n; i++) {
        c_fft[i] = a_fft[i] * b_fft[i];
    }

    fft(c_fft, n, 1);

    T81BigInt *res = TS_MALLOC(sizeof(T81BigInt));
    if (!res || allocate_t81bigint(res, len) != TERNARY_NO_ERROR) {
        TS_FREE(a_fft); TS_FREE(b_fft); TS_FREE(c_fft); TS_FREE(res);
        return TERNARY_ERR_MEMALLOC;
    }
    res->sign = (a->sign == b->sign) ? TERNARY_POSITIVE : TERNARY_NEGATIVE;

    int carry = 0;
    for (size_t i = 0; i < len; i++) {
        double val = c_fft[i] + carry;
        int digit = (int)round(val);
        carry = 0;
        while (digit > 1) { digit -= 3; carry++; }
        while (digit < -1) { digit += 3; carry--; }
        res->digits[i] = (unsigned char)digit;
    }
    if (carry) TS_PRINT("Warning: Carry overflow in FFT multiplication\n");

    TS_FREE(a_fft);
    TS_FREE(b_fft);
    TS_FREE(c_fft);
    *result = res;
    return TERNARY_NO_ERROR;
}

TernaryError t81bigint_div(const T81BigInt *a, const T81BigInt *b, T81BigInt **quotient) {
    if (b->sign == TERNARY_ZERO) return TERNARY_ERR_DIVZERO;
    if (a->sign == TERNARY_ZERO) {
        *quotient = TS_MALLOC(sizeof(T81BigInt));
        if (allocate_t81bigint(*quotient, 1) != TERNARY_NO_ERROR) return TERNARY_ERR_MEMALLOC;
        (*quotient)->sign = TERNARY_ZERO;
        (*quotient)->digits[0] = 0;
        return TERNARY_NO_ERROR;
    }

    T81BigInt *abs_a = TS_MALLOC(sizeof(T81BigInt));
    T81BigInt *abs_b = TS_MALLOC(sizeof(T81BigInt));
    if (!abs_a || !abs_b || t81bigint_copy(a, abs_a) != TERNARY_NO_ERROR || t81bigint_copy(b, abs_b) != TERNARY_NO_ERROR) {
        free_t81bigint(abs_a); TS_FREE(abs_a);
        free_t81bigint(abs_b); TS_FREE(abs_b);
        return TERNARY_ERR_MEMALLOC;
    }
    abs_a->sign = TERNARY_POSITIVE;
    abs_b->sign = TERNARY_POSITIVE;

    T81BigInt *x = TS_MALLOC(sizeof(T81BigInt));
    if (!x || allocate_t81bigint(x, abs_b->len + 1) != TERNARY_NO_ERROR) {
        free_t81bigint(abs_a); TS_FREE(abs_a);
        free_t81bigint(abs_b); TS_FREE(abs_b);
        free_t81bigint(x); TS_FREE(x);
        return TERNARY_ERR_MEMALLOC;
    }
    x->sign = TERNARY_POSITIVE;
    x->digits[0] = 1;

    T81BigInt *two = t81bigint_from_int(2);
    for (int i = 0; i < 5; i++) {
        T81BigInt *bx = NULL;
        if (t81bigint_mul(abs_b, x, &bx) != TERNARY_NO_ERROR) {
            free_t81bigint(abs_a); TS_FREE(abs_a);
            free_t81bigint(abs_b); TS_FREE(abs_b);
            free_t81bigint(x); TS_FREE(x);
            free_t81bigint(two); TS_FREE(two);
            return TERNARY_ERR_MEMALLOC;
        }
        T81BigInt *two_minus_bx = NULL;
        if (t81bigint_add(two, bx, &two_minus_bx) != TERNARY_NO_ERROR) {
            free_t81bigint(abs_a); TS_FREE(abs_a);
            free_t81bigint(abs_b); TS_FREE(abs_b);
            free_t81bigint(x); TS_FREE(x);
            free_t81bigint(two); TS_FREE(two);
            free_t81bigint(bx); TS_FREE(bx);
            return TERNARY_ERR_MEMALLOC;
        }
        two_minus_bx->sign = (two_minus_bx->sign == TERNARY_POSITIVE) ? TERNARY_NEGATIVE : TERNARY_POSITIVE;
        T81BigInt *temp_x = x;
        if (t81bigint_mul(x, two_minus_bx, &x) != TERNARY_NO_ERROR) {
            free_t81bigint(abs_a); TS_FREE(abs_a);
            free_t81bigint(abs_b); TS_FREE(abs_b);
            free_t81bigint(temp_x); TS_FREE(temp_x);
            free_t81bigint(two); TS_FREE(two);
            free_t81bigint(bx); TS_FREE(bx);
            free_t81bigint(two_minus_bx); TS_FREE(two_minus_bx);
            return TERNARY_ERR_MEMALLOC;
        }
        free_t81bigint(temp_x); TS_FREE(temp_x);
        free_t81bigint(bx); TS_FREE(bx);
        free_t81bigint(two_minus_bx); TS_FREE(two_minus_bx);
    }

    T81BigInt *q = NULL;
    if (t81bigint_mul(abs_a, x, &q) != TERNARY_NO_ERROR) {
        free_t81bigint(abs_a); TS_FREE(abs_a);
        free_t81bigint(abs_b); TS_FREE(abs_b);
        free_t81bigint(x); TS_FREE(x);
        free_t81bigint(two); TS_FREE(two);
        return TERNARY_ERR_MEMALLOC;
    }
    q->sign = (a->sign == b->sign) ? TERNARY_POSITIVE : TERNARY_NEGATIVE;

    free_t81bigint(abs_a); TS_FREE(abs_a);
    free_t81bigint(abs_b); TS_FREE(abs_b);
    free_t81bigint(x); TS_FREE(x);
    free_t81bigint(two); TS_FREE(two);
    *quotient = q;
    return TERNARY_NO_ERROR;
}

TernaryError t81bigint_mod(const T81BigInt *a, const T81BigInt *b, T81BigInt **result) {
    if (!a || !b || !result || b->sign == TERNARY_ZERO) return TERNARY_ERR_DIVZERO;

    T81BigInt *quotient = NULL;
    TernaryError err = t81bigint_div(a, b, &quotient);
    if (err != TERNARY_NO_ERROR) return err;

    T81BigInt *prod = NULL;
    err = t81bigint_mul(quotient, b, &prod);
    if (err != TERNARY_NO_ERROR) {
        free_t81bigint(quotient); TS_FREE(quotient);
        return err;
    }

    err = t81bigint_sub(a, prod, result);
    free_t81bigint(quotient); TS_FREE(quotient);
    free_t81bigint(prod); TS_FREE(prod);
    return err;
}

TernaryError t81bigint_exp(const T81BigInt *base, unsigned int exponent, T81BigInt **result) {
    if (!base || !result) return TERNARY_ERR_INVALID_INPUT;

    T81BigInt *res = TS_MALLOC(sizeof(T81BigInt));
    if (!res) return TERNARY_ERR_MEMALLOC;

    if (exponent == 0) {
        if (allocate_t81bigint(res, 1) != TERNARY_NO_ERROR) {
            TS_FREE(res);
            return TERNARY_ERR_MEMALLOC;
        }
        res->sign = TERNARY_POSITIVE;
        res->digits[0] = 1;
        *result = res;
        return TERNARY_NO_ERROR;
    }

    if (base->sign == TERNARY_ZERO) {
        if (allocate_t81bigint(res, 1) != TERNARY_NO_ERROR) {
            TS_FREE(res);
            return TERNARY_ERR_MEMALLOC;
        }
        res->sign = TERNARY_ZERO;
        res->digits[0] = 0;
        *result = res;
        return TERNARY_NO_ERROR;
    }

    if (allocate_t81bigint(res, 1) != TERNARY_NO_ERROR) {
        TS_FREE(res);
        return TERNARY_ERR_MEMALLOC;
    }
    res->sign = TERNARY_POSITIVE;
    res->digits[0] = 1;

    T81BigInt *temp_base = NULL;
    if (t81bigint_copy(base, &temp_base) != TERNARY_NO_ERROR) {
        free_t81bigint(res); TS_FREE(res);
        return TERNARY_ERR_MEMALLOC;
    }

    for (unsigned int i = 0; i < exponent; i++) {
        T81BigInt *new_res = NULL;
        TernaryError err = t81bigint_mul(res, temp_base, &new_res);
        if (err != TERNARY_NO_ERROR) {
            free_t81bigint(res); TS_FREE(res);
            free_t81bigint(temp_base); TS_FREE(temp_base);
            return err;
        }
        free_t81bigint(res);
        res = new_res;
    }

    free_t81bigint(temp_base); TS_FREE(temp_base);
    *result = res;
    return TERNARY_NO_ERROR;
}

TernaryError t81bigint_tand(const T81BigInt *a, const T81BigInt *b, T81BigInt **result) {
    if (!a || !b || !result) return TERNARY_ERR_INVALID_INPUT;
    
    size_t max_len = (a->len > b->len) ? a->len : b->len;
    T81BigInt *res = TS_MALLOC(sizeof(T81BigInt));
    if (!res || allocate_t81bigint(res, max_len) != TERNARY_NO_ERROR) {
        TS_FREE(res);
        return TERNARY_ERR_MEMALLOC;
    }

    for (size_t i = 0; i < max_len; i++) {
        int trit_a = (i < a->len) ? (signed char)a->digits[i] * a->sign : 0;
        int trit_b = (i < b->len) ? (signed char)b->digits[i] * b->sign : 0;
        res->digits[i] = (trit_a < trit_b) ? trit_a : trit_b;
    }
    
    res->sign = TERNARY_POSITIVE;
    int all_zero = 1;
    for (size_t i = 0; i < max_len; i++) {
        if (res->digits[i] != 0) {
            all_zero = 0;
            break;
        }
    }
    if (all_zero) res->sign = TERNARY_ZERO;

    *result = res;
    return TERNARY_NO_ERROR;
}

TernaryError t81bigint_tor(const T81BigInt *a, const T81BigInt *b, T81BigInt **result) {
    if (!a || !b || !result) return TERNARY_ERR_INVALID_INPUT;
    
    size_t max_len = (a->len > b->len) ? a->len : b->len;
    T81BigInt *res = TS_MALLOC(sizeof(T81BigInt));
    if (!res || allocate_t81bigint(res, max_len) != TERNARY_NO_ERROR) {
        TS_FREE(res);
        return TERNARY_ERR_MEMALLOC;
    }

    for (size_t i = 0; i < max_len; i++) {
        int trit_a = (i < a->len) ? (signed char)a->digits[i] * a->sign : 0;
        int trit_b = (i < b->len) ? (signed char)b->digits[i] * b->sign : 0;
        res->digits[i] = (trit_a > trit_b) ? trit_a : trit_b;
    }
    
    res->sign = TERNARY_POSITIVE;
    int all_zero = 1;
    for (size_t i = 0; i < max_len; i++) {
        if (res->digits[i] != 0) {
            all_zero = 0;
            break;
        }
    }
    if (all_zero) res->sign = TERNARY_ZERO;

    *result = res;
    return TERNARY_NO_ERROR;
}

T81BigInt *t81bigint_from_int(int num) {
    T81BigInt *result = TS_MALLOC(sizeof(T81BigInt));
    if (!result) return NULL;
    if (num == 0) {
        if (allocate_t81bigint(result, 1) != TERNARY_NO_ERROR) {
            TS_FREE(result);
            return NULL;
        }
        result->sign = TERNARY_ZERO;
        result->digits[0] = 0;
        return result;
    }
    int abs_num = abs(num);
    size_t len = 0;
    int temp = abs_num;
    while (temp > 0) { len++; temp /= 3; }
    if (allocate_t81bigint(result, len) != TERNARY_NO_ERROR) {
        TS_FREE(result);
        return NULL;
    }
    result->sign = num < 0 ? TERNARY_NEGATIVE : TERNARY_POSITIVE;
    for (size_t i = 0; abs_num > 0 && i < len; i++) {
        int rem = abs_num % 3;
        result->digits[i] = (rem == 2) ? -1 : rem;
        abs_num = (rem == 2) ? (abs_num / 3) + 1 : abs_num / 3;
    }
    return result;
}

int t81bigint_to_int(const T81BigInt *num, TernaryError *err) {
    if (!num) {
        if (err) *err = TERNARY_ERR_INVALID_INPUT;
        return 0;
    }
    if (num->sign == TERNARY_ZERO) return 0;
    int result = 0;
    for (size_t i = num->len; i > 0; i--) {
        int digit = (signed char)num->digits[i - 1];
        if (result > (INT_MAX - abs(digit)) / 3) {
            if (err) *err = TERNARY_ERR_INVALID_INPUT;
            return 0;
        }
        result = result * 3 + digit;
    }
    result *= num->sign;
    if (err) *err = TERNARY_NO_ERROR;
    return result;
}

void t81bigint_to_string(const T81BigInt *num, char *buffer) {
    if (!num || num->sign == TERNARY_ZERO) {
        strcpy(buffer, "0");
        return;
    }
    size_t i = 0;
    if (num->sign == TERNARY_NEGATIVE) buffer[i++] = '-';
    size_t start = num->len;
    while (start > 0 && num->digits[start - 1] == 0) start--;
    if (start == 0) {
        strcpy(buffer, "0");
        return;
    }
    for (size_t j = start; j > 0; j--) {
        int digit = (signed char)num->digits[j - 1];
        buffer[i++] = (digit == 1) ? '1' : (digit == -1) ? 'T' : '0';
    }
    buffer[i] = '\0';
}

T81Matrix *create_matrix(int rows, int cols) {
    T81Matrix *m = TS_MALLOC(sizeof(T81Matrix));
    if (!m) return NULL;
    m->rows = rows;
    m->cols = cols;
    m->data = TS_MALLOC(rows * cols * sizeof(T81BigInt));
    if (!m->data) { TS_FREE(m); return NULL; }
    for (int i = 0; i < rows * cols; i++) {
        if (allocate_t81bigint(&m->data[i], 1) != TERNARY_NO_ERROR) {
            for (int j = 0; j < i; j++) free_t81bigint(&m->data[j]);
            TS_FREE(m->data);
            TS_FREE(m);
            return NULL;
        }
        m->data[i].sign = TERNARY_ZERO;
    }
    return m;
}

void free_matrix(T81Matrix *m) {
    if (!m) return;
    if (m->data) {
        for (int i = 0; i < m->rows * m->cols; i++) free_t81bigint(&m->data[i]);
        TS_FREE(m->data);
    }
    TS_FREE(m);
}

TernaryError tmat_add(T81Matrix *a, T81Matrix *b, T81Matrix **result) {
    if (a->rows != b->rows || a->cols != b->cols) return TERNARY_ERR_INVALID_INPUT;
    T81Matrix *res = create_matrix(a->rows, a->cols);
    if (!res) return TERNARY_ERR_MEMALLOC;
    for (int i = 0; i < a->rows * a->cols; i++) {
        TernaryError err = t81bigint_add(&a->data[i], &b->data[i], &res->data[i]);
        if (err != TERNARY_NO_ERROR) { free_matrix(res); return err; }
    }
    *result = res;
    return TERNARY_NO_ERROR;
}

TernaryError tmat_mul(T81Matrix *a, T81Matrix *b, T81Matrix **result) {
    if (a->cols != b->rows) return TERNARY_ERR_INVALID_INPUT;
    T81Matrix *res = create_matrix(a->rows, b->cols);
    if (!res) return TERNARY_ERR_MEMALLOC;
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            int res_index = i * b->cols + j;
            free_t81bigint(&res->data[res_index]);
            if (allocate_t81bigint(&res->data[res_index], 1) != TERNARY_NO_ERROR) {
                free_matrix(res);
                return TERNARY_ERR_MEMALLOC;
            }
            res->data[res_index].sign = TERNARY_ZERO;
            for (int k = 0; k < a->cols; k++) {
                T81BigInt *temp = NULL;
                TernaryError err = t81bigint_mul(&a->data[i * a->cols + k], &b->data[k * b->cols + j], &temp);
                if (err != TERNARY_NO_ERROR) { free_matrix(res); return err; }
                T81BigInt *sum = NULL;
                err = t81bigint_add(&res->data[res_index], temp, &sum);
                free_t81bigint(temp); TS_FREE(temp);
                if (err != TERNARY_NO_ERROR) { free_matrix(res); return err; }
                free_t81bigint(&res->data[res_index]);
                res->data[res_index] = *sum;
                TS_FREE(sum);
            }
        }
    }
    *result = res;
    return TERNARY_NO_ERROR;
}

T81Matrix *tmat_transpose(T81Matrix *m) {
    T81Matrix *t = TS_MALLOC(sizeof(T81Matrix));
    if (!t) return NULL;
    t->rows = m->cols;
    t->cols = m->rows;
    t->data = TS_MALLOC(t->rows * t->cols * sizeof(T81BigInt));
    if (!t->data) { TS_FREE(t); return NULL; }
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            if (allocate_t81bigint(&t->data[j * m->rows + i], 1) != TERNARY_NO_ERROR ||
                t81bigint_copy(&m->data[i * m->cols + j], &t->data[j * m->rows + i]) != TERNARY_NO_ERROR) {
                free_matrix(t);
                return NULL;
            }
        }
    }
    return t;
}

void discrete_opcode_encode(int opcode, char *encoded_buffer) {
    T81BigInt *num = t81bigint_from_int(opcode);
    t81bigint_to_string(num, encoded_buffer);
    int checksum = 0;
    for (int i = 0; encoded_buffer[i] && encoded_buffer[i] != '-'; i++)
        checksum = (checksum + (encoded_buffer[i] == 'T' ? -1 : (encoded_buffer[i] - '0'))) % 9;
    sprintf(encoded_buffer + strlen(encoded_buffer), "%d", checksum);
    free_t81bigint(num);
    TS_FREE(num);
}

int discrete_opcode_validate(const char *encoded_opcode) {
    int len = strlen(encoded_opcode);
    if (len < 2 || !isdigit(encoded_opcode[len - 1])) return 0;
    int computed = 0;
    for (int i = 0; i < len - 1; i++) {
        if (encoded_opcode[i] != 'T' && encoded_opcode[i] != '-' && (encoded_opcode[i] < '0' || encoded_opcode[i] > '2')) return 0;
        computed = (computed + (encoded_opcode[i] == 'T' ? -1 : (encoded_opcode[i] - '0'))) % 9;
    }
    return computed == (encoded_opcode[len - 1] - '0');
}

int discrete_opcode_execute(const char *encoded_opcode, int operand1, int operand2) {
    if (!discrete_opcode_validate(encoded_opcode)) {
        TS_PRINT("Invalid encoded opcode: %s\n", encoded_opcode);
        return 0;
    }
    if (operand1 > INT_MAX / 2 || operand2 > INT_MAX / 2) {
        TS_PRINT("Operands too large: %d, %d\n", operand1, operand2);
        return 0;
    }
    int len = strlen(encoded_opcode);
    char opcode_str[64];
    strncpy(opcode_str, encoded_opcode, len - 1);
    opcode_str[len - 1] = '\0';
    int opcode = 0;
    for (int i = 0; i < len - 1; i++) {
        opcode = opcode * 3 + (opcode_str[i] == 'T' ? -1 : (opcode_str[i] - '0'));
    }
    int result = 0;
    switch (opcode) {
        case TADD: result = operand1 + operand2; break;
        case TSUB: result = operand1 - operand2; break;
        case TMUL: result = operand1 * operand2; break;
        case TMOD: 
            if (operand2 == 0) { TS_PRINT("Modulo by zero\n"); return 0; }
            result = operand1 % operand2;
            if (result < 0) result += abs(operand2);
            break;
        case TAND: {
            T81BigInt *a = t81bigint_from_int(operand1);
            T81BigInt *b = t81bigint_from_int(operand2);
            T81BigInt *res = NULL;
            TernaryError err = t81bigint_tand(a, b, &res);
            if (err == TERNARY_NO_ERROR) {
                result = t81bigint_to_int(res, &err);
            }
            free_t81bigint(a); TS_FREE(a);
            free_t81bigint(b); TS_FREE(b);
            free_t81bigint(res); TS_FREE(res);
            if (err != TERNARY_NO_ERROR) return 0;
            break;
        }
        case TOR: {
            T81BigInt *a = t81bigint_from_int(operand1);
            T81BigInt *b = t81bigint_from_int(operand2);
            T81BigInt *res = NULL;
            TernaryError err = t81bigint_tor(a, b, &res);
            if (err == TERNARY_NO_ERROR) {
                result = t81bigint_to_int(res, &err);
            }
            free_t81bigint(a); TS_FREE(a);
            free_t81bigint(b); TS_FREE(b);
            free_t81bigint(res); TS_FREE(res);
            if (err != TERNARY_NO_ERROR) return 0;
            break;
        }
        case TMAT_ADD: result = (operand1 + operand2) * 2; break;
        case TMAT_MUL: result = (operand1 * operand2) * 2; break;
        case THANOI: result = (1 << operand1) - 1; break;
        case TEXP:
            if (operand2 < 0) { TS_PRINT("Negative exponent not supported\n"); return 0; }
            result = 1;
            for (int i = 0; i < operand2; i++) {
                if (result > INT_MAX / operand1) { TS_PRINT("Exponentiation overflow\n"); return 0; }
                result *= operand1;
            }
            break;
        case TGCD: {
            int a = abs(operand1), b = abs(operand2);
            while (b) { int t = b; b = a % b; a = t; }
            result = a;
            break;
        }
        default: TS_PRINT("Opcode %d not implemented\n", opcode); break;
    }
    return result;
}

T81BigInt *tritjs_eval_expression(const char *expr) {
    if (!expr) return NULL;
    char *plus = strchr(expr, '+');
    char *minus = strchr(expr, '-');
    char *mul = strchr(expr, '*');
    char *div = strchr(expr, '/');
    char *mod = strchr(expr, '%');
    char *tand = strchr(expr, '&');
    char *tor = strchr(expr, '|');

    char *op = NULL;
    TernaryError (*op_func)(const T81BigInt *, const T81BigInt *, T81BigInt **) = NULL;
    if (tand) { op = tand; op_func = t81bigint_tand; }
    if (tor && (!op || tor > op)) { op = tor; op_func = t81bigint_tor; }
    if (plus && (!op || plus > op)) { op = plus; op_func = t81bigint_add; }
    if (minus && (!op || minus > op)) { op = minus; op_func = t81bigint_sub; }
    if (mul && (!op || mul > op)) { op = mul; op_func = t81bigint_mul; }
    if (div && (!op || div > op)) { op = div; op_func = t81bigint_div; }
    if (mod && (!op || mod > op)) { op = mod; op_func = t81bigint_mod; }

    if (!op) {
        T81BigInt *num = TS_MALLOC(sizeof(T81BigInt));
        if (allocate_t81bigint(num, strlen(expr)) != TERNARY_NO_ERROR) {
            TS_FREE(num);
            return NULL;
        }
        num->sign = (expr[0] == '-') ? TERNARY_NEGATIVE : TERNARY_POSITIVE;
        size_t i = (expr[0] == '-') ? 1 : 0, j = 0;
        while (expr[i]) {
            num->digits[j++] = (expr[i] == 'T') ? -1 : (expr[i] - '0');
            i++;
        }
        num->len = j;
        return num;
    }

    char left[64], right[64];
    strncpy(left, expr, op - expr);
    left[op - expr] = '\0';
    strcpy(right, op + 1);
    T81BigInt *a = tritjs_eval_expression(left);
    T81BigInt *b = tritjs_eval_expression(right);
    T81BigInt *result = NULL;
    if (a && b && op_func(a, b, &result) == TERNARY_NO_ERROR) {
        free_t81bigint(a); TS_FREE(a);
        free_t81bigint(b); TS_FREE(b);
        return result;
    }
    free_t81bigint(a); TS_FREE(a);
    free_t81bigint(b); TS_FREE(b);
    free_t81bigint(result); TS_FREE(result);
    return NULL;
}

/* ============================================================
 * Section 4: Command-Line Utility
 */
#ifndef __KERNEL__
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <getopt.h>

static const char *usage_text =
    "Usage: tritsys [OPTION]...\n"
    "Ternary arithmetic and computing utility.\n\n"
    "Options:\n"
    "  -e, --expr EXPR       Evaluate a ternary arithmetic expression (e.g., \"1T+0\")\n"
    "  -n, --hanoi N [PAUSE] Solve Tower of Hanoi for N disks, pausing every PAUSE lines (optional)\n"
    "  -s, --serialize FILE  Serialize a sample 3x3 matrix to FILE\n"
    "  -d, --deserialize FILE Deserialize matrix from FILE and print\n"
    "  -o, --opcode NUM      Encode and validate opcode NUM\n"
    "  -x, --exec-opcode ENC OP1 OP2  Execute opcode ENC on operands OP1 and OP2\n"
    "  -p, --exp BASE EXP    Compute BASE raised to EXP in ternary\n"
    "  -i, --interactive     Enter interactive mode\n"
    "  -h, --help            Display this help and exit\n\n"
    "Examples:\n"
    "  tritsys -e \"1T+0\"      # Outputs: 1T\n"
    "  tritsys -n 3 10         # Prints Hanoi moves, pausing every 10 lines\n"
    "  tritsys -i              # Starts interactive shell\n";

static void print_help(void) {
    printf("%s", usage_text);
}

static void solve_hanoi(int n, int pause_interval) {
    static int line_count = 0;

    if (pause_interval <= 0) pause_interval = INT_MAX;

    void move(int n, char from, char to, char aux) {
        if (n == 1) {
            printf("Move disk 1 from %c to %c\n", from, to);
            line_count++;
            if (line_count % pause_interval == 0) {
                printf("--- Paused at line %d. Press Enter to continue ---\n", line_count);
                getchar();
            }
            return;
        }
        move(n - 1, from, aux, to);
        printf("Move disk %d from %c to %c\n", n, from, to);
        line_count++;
        if (line_count % pause_interval == 0) {
            printf("--- Paused at line %d. Press Enter to continue ---\n", line_count);
            getchar();
        }
        move(n - 1, aux, to, from);
    }
    line_count = 0;
    move(n, 'A', 'C', 'B');
}

static void interactive_mode(void) {
    char *line;
    printf("Ternary System Interactive Mode. Type 'help' for commands, 'exit' to quit.\n");
    while (1) {
        line = readline("tritsys> ");
        if (!line) break;
        if (*line) add_history(line);
        char *token = strtok(line, " \t\n");
        if (!token) { free(line); continue; }
        if (strcmp(token, "help") == 0) {
            print_help();
        } else if (strcmp(token, "expr") == 0) {
            char *expr = strtok(NULL, "\n");
            if (!expr) {
                fprintf(stderr, "tritsys: expr requires an expression\n");
            } else {
                T81BigInt *result = tritjs_eval_expression(expr);
                if (result) {
                    char buffer[256];
                    t81bigint_to_string(result, buffer);
                    printf("%s\n", buffer);
                    free_t81bigint(result);
                    TS_FREE(result);
                }
            }
        } else if (strcmp(token, "hanoi") == 0) {
            char *n_str = strtok(NULL, " \t\n");
            char *pause_str = strtok(NULL, " \t\n");
            if (!n_str || !isdigit(*n_str)) {
                fprintf(stderr, "tritsys: hanoi requires a number for N\n");
            } else {
                int n = atoi(n_str);
                int pause_interval = INT_MAX;
                if (pause_str && isdigit(*pause_str)) {
                    pause_interval = atoi(pause_str);
                }
                solve_hanoi(n, pause_interval);
            }
        } else if (strcmp(token, "exp") == 0) {
            char *base_str = strtok(NULL, " \t\n");
            char *exp_str = strtok(NULL, " \t\n");
            if (!base_str || !exp_str || !isdigit(*exp_str)) {
                fprintf(stderr, "tritsys: exp requires base and exponent\n");
            } else {
                T81BigInt *base = tritjs_eval_expression(base_str);
                T81BigInt *result = NULL;
                if (t81bigint_exp(base, atoi(exp_str), &result) == TERNARY_NO_ERROR) {
                    char buffer[256];
                    t81bigint_to_string(result, buffer);
                    printf("%s\n", buffer);
                    free_t81bigint(result);
                    TS_FREE(result);
                }
                free_t81bigint(base);
                TS_FREE(base);
            }
        } else if (strcmp(token, "exit") == 0) {
            free(line);
            break;
        } else {
            fprintf(stderr, "tritsys: unknown command '%s'\n", token);
        }
        free(line);
    }
}

int main(int argc, char *argv[]) {
    int opt;
    static struct option long_options[] = {
        {"expr", required_argument, 0, 'e'},
        {"hanoi", required_argument, 0, 'n'},
        {"serialize", required_argument, 0, 's'},
        {"deserialize", required_argument, 0, 'd'},
        {"opcode", required_argument, 0, 'o'},
        {"exec-opcode", required_argument, 0, 'x'},
        {"exp", required_argument, 0, 'p'},
        {"interactive", no_argument, 0, 'i'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    if (argc == 1) {
        interactive_mode();
        return 0;
    }

    while ((opt = getopt_long(argc, argv, "e:n:s:d:o:x:p:ih", long_options, NULL)) != -1) {
        switch (opt) {
            case 'e': {
                T81BigInt *result = tritjs_eval_expression(optarg);
                if (!result) {
                    fprintf(stderr, "tritsys: failed to evaluate expression '%s'\n", optarg);
                    return 1;
                }
                char buffer[256];
                t81bigint_to_string(result, buffer);
                printf("%s\n", buffer);
                free_t81bigint(result);
                TS_FREE(result);
                return 0;
            }
            case 'n': {
                if (!isdigit(*optarg)) {
                    fprintf(stderr, "tritsys: hanoi requires a numeric argument for N\n");
                    return 1;
                }
                int n = atoi(optarg);
                int pause_interval = INT_MAX;
                if (optind < argc && isdigit(*argv[optind])) {
                    pause_interval = atoi(argv[optind]);
                    optind++;
                }
                solve_hanoi(n, pause_interval);
                return 0;
            }
            case 's': {
                T81Matrix *m = create_matrix(3, 3);
                if (!m) {
                    fprintf(stderr, "tritsys: memory allocation failed\n");
                    return 1;
                }
                for (int i = 0; i < 9; i++) m->data[i].digits[0] = (i % 3);
                FILE *f = fopen(optarg, "wb");
                if (!f) {
                    fprintf(stderr, "tritsys: cannot open file '%s'\n", optarg);
                    free_matrix(m);
                    return 1;
                }
                fwrite(m, sizeof(T81Matrix), 1, f);
                fwrite(m->data, sizeof(T81BigInt), 9, f);
                fclose(f);
                free_matrix(m);
                printf("Serialized to %s\n", optarg);
                return 0;
            }
            case 'd': {
                FILE *f = fopen(optarg, "rb");
                if (!f) {
                    fprintf(stderr, "tritsys: cannot open file '%s'\n", optarg);
                    return 1;
                }
                T81Matrix *m = TS_MALLOC(sizeof(T81Matrix));
                if (!m || fread(m, sizeof(T81Matrix), 1, f) != 1) {
                    fprintf(stderr, "tritsys: failed to read matrix from '%s'\n", optarg);
                    TS_FREE(m);
                    fclose(f);
                    return 1;
                }
                m->data = TS_MALLOC(m->rows * m->cols * sizeof(T81BigInt));
                if (!m->data || fread(m->data, sizeof(T81BigInt), m->rows * m->cols, f) != m->rows * m->cols) {
                    fprintf(stderr, "tritsys: failed to read matrix data from '%s'\n", optarg);
                    free_matrix(m);
                    fclose(f);
                    return 1;
                }
                fclose(f);
                for (int i = 0; i < m->rows * m->cols; i++) {
                    char buffer[16];
                    t81bigint_to_string(&m->data[i], buffer);
                    printf("%s%s", buffer, (i + 1) % m->cols == 0 ? "\n" : " ");
                }
                free_matrix(m);
                return 0;
            }
            case 'o': {
                if (!isdigit(*optarg)) {
                    fprintf(stderr, "tritsys: opcode requires a numeric argument\n");
                    return 1;
                }
                int opcode = atoi(optarg);
                char encoded[64];
                discrete_opcode_encode(opcode, encoded);
                printf("Opcode %d encoded as: %s\n", opcode, encoded);
                printf("Validation: %s\n", discrete_opcode_validate(encoded) ? "valid" : "invalid");
                return 0;
            }
            case 'x': {
                char *enc = optarg;
                char *op1_str = argv[optind++];
                char *op2_str = argv[optind++];
                if (!op1_str || !op2_str || !isdigit(*op1_str) || !isdigit(*op2_str)) {
                    fprintf(stderr, "tritsys: exec-opcode requires ENC OP1 OP2\n");
                    return 1;
                }
                int op1 = atoi(op1_str), op2 = atoi(op2_str);
                int result = discrete_opcode_execute(enc, op1, op2);
                char buffer[64];
                T81BigInt *res_big = t81bigint_from_int(result);
                t81bigint_to_string(res_big, buffer);
                printf("%s\n", buffer);
                free_t81bigint(res_big);
                TS_FREE(res_big);
                return 0;
            }
            case 'p': {
                char *base_str = optarg;
                char *exp_str = argv[optind++];
                if (!exp_str || !isdigit(*exp_str)) {
                    fprintf(stderr, "tritsys: exp requires BASE EXP\n");
                    return 1;
                }
                T81BigInt *base = tritjs_eval_expression(base_str);
                T81BigInt *result = NULL;
                if (!base || t81bigint_exp(base, atoi(exp_str), &result) != TERNARY_NO_ERROR) {
                    fprintf(stderr, "tritsys: failed to compute exponentiation\n");
                    free_t81bigint(base);
                    TS_FREE(base);
                    return 1;
                }
                char buffer[256];
                t81bigint_to_string(result, buffer);
                printf("%s\n", buffer);
                free_t81bigint(base);
                TS_FREE(base);
                free_t81bigint(result);
                TS_FREE(result);
                return 0;
            }
            case 'i':
                interactive_mode();
                return 0;
            case 'h':
                print_help();
                return 0;
            default:
                fprintf(stderr, "tritsys: invalid option\n");
                fprintf(stderr, "Try 'tritsys --help' for more information.\n");
                return 1;
        }
    }

    if (optind < argc) {
        fprintf(stderr, "tritsys: unexpected arguments\n");
        fprintf(stderr, "Try 'tritsys --help' for more information.\n");
        return 1;
    }

    interactive_mode();
    return 0;
}

#endif /* !__KERNEL__ */
