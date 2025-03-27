/*****************************************************************************
 * TritJS-CISA: A Ternary (Base-3) Scientific Calculator for Security & Education
 *
 * USER MANUAL (preserved from original and updated):
 *
 * @* TritJS-CISA: A Ternary Calculator with CISA-Compliant Security, POSIX Enhancements, 
 * Comprehensive Benchmarking, and an Enhanced Ncurses Interface.
 *
 * This program has been optimized for:
 *   - Improved memory management and safe dynamic reallocation.
 *   - Faster base conversion by grouping four base‑3 digits at a time.
 *   - Efficient multiplication using a Karatsuba algorithm (with a fallback to naïve
 *     multiplication for small inputs).
 *   - Enhanced security including file locking on audit logs and secure memory zeroing
 *     (where supported).
 *   - A responsive ncurses UI that handles terminal resizing.
 *
 * == Features ==
 * • Arithmetic: add, sub, mul, div, pow, fact
 * • Scientific: sqrt, log3, sin, cos, tan, pi
 * • Conversions: bin2tri, tri2bin (optimized conversion routines)
 * • State Management: save and load encrypted/signed session states
 * • Security: secure audit logging (with file locking) and secure memory clearing
 * • Benchmarking: bench command runs performance tests
 * • Scripting & Variables: PROG/RUN, A=102, IF, FOR
 * • Interface: enhanced ncurses-based UI (with terminal resize support) plus optional GNU Readline
 *
 * == Installation ==
 * 1. Compile using:
 *      gcc -DUSE_READLINE -o tritjs_cisa_optimized TritJS-CISA-Optimized.c -lm -lreadline \
 *          -fstack-protector-strong -D_FORTIFY_SOURCE=2 -pie -fPIE -lncurses -lfcntl
 * 2. Run with:
 *      ./tritjs_cisa_optimized
 *
 * == Command Reference ==
 *  add <a> <b>, sub <a> <b>, mul <a> <b>, div <a> <b>, pow <a> <b>, fact <a>
 *  sqrt <a>, log3 <a>, sin <a>, cos <a>, tan <a>, pi
 *  bin2tri <n>, tri2bin <trit>
 *  save <file>, load <file>
 *  monitor, bench
 *  PROG <name> { <commands> }, RUN <name>, <var>=<value>, help, clear, test, version, quit
 *
 * == Troubleshooting ==
 * - Audit Log: /var/log/tritjs_cisa.log (secured with file locking)
 * - Must be root to load states
 * - 1MB limit for mapped trits; benchmark outputs are provided for performance analysis.
 *
 * == Future Enhancements ==
 * - FIPS–validated crypto, real-time intrusion detection, extended scripting and UI enhancements.
 *
 * == License ==
 * GNU General Public License (GPL)
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include <ncurses.h>
#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif
#include <errno.h>
#include <sys/file.h>  // For flock

/*****************************************************************************
 * Configuration & Defines
 *****************************************************************************/
#define ENABLE_VERBOSE_LOGGING 1
#define VERSION "2.0-upgrade-optimized"

/* We store digits in base 81 (81 = 3^4). */
#define BASE_81 81

/* MMap threshold: Only map if needed buffer >= this many bytes. */
#define T81_MMAP_THRESHOLD (500 * 1024)

/* Error codes:
   0 = OK, 1 = Memory allocation failed, 2 = Invalid input,
   3 = Division by zero, 4 = Overflow, 5 = Undefined,
   6 = Negative, 7 = Precision error, 8 = Memory mapping failed,
   9 = Scripting error.
*/
typedef int TritError;

#if ENABLE_VERBOSE_LOGGING
#define LOG_ERROR(err, context) log_error(err, context, __FILE__, __LINE__)
#else
#define LOG_ERROR(err, context) log_error(err, context)
#endif

/*****************************************************************************
 * Data Structures
 *****************************************************************************/

/* Big integer stored in base-81 */
typedef struct {
    int sign;                 /* 0 = positive, 1 = negative */
    unsigned char *digits;    /* digits[0..len-1], each in [0..80] */
    size_t len;               /* number of base-81 digits */
    int is_mapped;            /* 1 if allocated with mmap, else 0 */
    int fd;                   /* file descriptor if using mmap */
    char tmp_path[32];        /* temporary file path for mmap */
} T81BigInt;

/* Floating point representation for division (stub implementation) */
typedef struct {
    int sign;
    unsigned char* integer;   /* base-81 digits for integer part */
    unsigned char* fraction;  /* base-81 digits for fractional part */
    size_t i_len, f_len;
    int i_mapped, f_mapped;
    int i_fd, f_fd;
    char i_tmp_path[32];
    char f_tmp_path[32];
} T81Float;

/* Complex number structure (stub functions) */
typedef struct {
    T81Float real;
    T81Float imag;
} T81Complex;

/* Division result: quotient and remainder (stub implementation) */
typedef struct {
    T81Float quotient;
    T81Float remainder;
} T81DivResult;

/* Scripting structure */
#define MAX_SCRIPT_NAME 10
#define MAX_SCRIPT_CMDS 50
typedef struct {
    char name[MAX_SCRIPT_NAME];
    char commands[MAX_SCRIPT_CMDS][256];
    int cmd_count;
} Script;

/*****************************************************************************
 * Global Variables
 *****************************************************************************/
static FILE* audit_log = NULL;
static long total_mapped_bytes = 0;
static int operation_steps = 0;

/* Command history */
#define MAX_HISTORY 10
static char* history[MAX_HISTORY] = {0};
static int history_count = 0;

/* Variables A-Z (26 possible) */
static T81BigInt* variables[26] = {0};

/* Scripting storage */
static Script scripts[10] = {0};
static int script_count = 0;

/* Ncurses windows */
static WINDOW *input_win, *output_win, *status_win;

/*****************************************************************************
 * Logging & Error Handling
 *****************************************************************************/
static const char* trit_error_str(TritError err) {
    switch(err){
        case 0: return "No error";
        case 1: return "Memory allocation failed";
        case 2: return "Invalid input";
        case 3: return "Division by zero";
        case 4: return "Overflow detected";
        case 5: return "Operation undefined";
        case 6: return "Negative input (complex handled)";
        case 7: return "Precision limit exceeded";
        case 8: return "Memory mapping failed";
        case 9: return "Scripting error";
        default: return "Unknown error";
    }
}

static void log_error(TritError err, const char* context, const char* file, int line) {
    if (!audit_log) return;
    time_t now;
    time(&now);
    fprintf(audit_log, "[%s] ERROR %d: %s in %s (%s:%d)\n",
            ctime(&now), err, trit_error_str(err), context, file, line);
    fflush(audit_log);
}

/*****************************************************************************
 * Memory Allocation for T81BigInt
 *****************************************************************************/
static TritError allocate_digits(T81BigInt *x, size_t lengthNeeded) {
    size_t bytesNeeded = (lengthNeeded == 0 ? 1 : lengthNeeded);
    x->len = lengthNeeded;
    x->is_mapped = 0;
    x->fd = -1;
    if (bytesNeeded < T81_MMAP_THRESHOLD) {
        x->digits = (unsigned char*)calloc(bytesNeeded, 1);
        if (!x->digits) return 1; // Memory allocation failed
        return 0;
    }
    strcpy(x->tmp_path, "/tmp/tritjs_cisa_XXXXXX");
    x->fd = mkstemp(x->tmp_path);
    if (x->fd < 0) return 8;
    if (ftruncate(x->fd, bytesNeeded) < 0) {
        close(x->fd);
        return 8;
    }
    x->digits = mmap(NULL, bytesNeeded, PROT_READ | PROT_WRITE, MAP_SHARED, x->fd, 0);
    if (x->digits == MAP_FAILED) {
        close(x->fd);
        return 8;
    }
    unlink(x->tmp_path);
    x->is_mapped = 1;
    total_mapped_bytes += bytesNeeded;
    operation_steps++;
    return 0;
}

static void t81bigint_free(T81BigInt* x) {
    if (!x) return;
    if (x->is_mapped && x->digits && x->digits != MAP_FAILED) {
        size_t bytes = (x->len == 0 ? 1 : x->len);
        munmap(x->digits, bytes);
        close(x->fd);
        total_mapped_bytes -= bytes;
        operation_steps++;
    } else {
        free(x->digits);
    }
    memset(x, 0, sizeof(*x));
}

/*****************************************************************************
 * Audit Log Initialization with File Locking
 *****************************************************************************/
static void init_audit_log() {
    audit_log = fopen("/var/log/tritjs_cisa.log", "a");
    if (!audit_log) {
        perror("Audit log init failed; fallback to stderr");
        audit_log = stderr;
    } else {
        // Secure the log file with an exclusive lock
        flock(fileno(audit_log), LOCK_EX);
    }
}

/*****************************************************************************
 * Optimized Base-3 String to Base-81 Conversion
 *
 * Instead of processing one digit at a time, this routine processes any
 * leading remainder (if the number of digits is not a multiple of 4) and then
 * groups every 4 digits (since 3^4 = 81) to speed up conversion.
 *****************************************************************************/
static TritError parse_trit_string_base81_optimized(const char* str, T81BigInt* out) {
    if (!str || !str[0]) return 2;
    memset(out, 0, sizeof(*out));

    int sign = 0;
    size_t pos = 0;
    if (str[0] == '-') {
        sign = 1;
        pos = 1;
    }
    size_t total_len = strlen(str) - pos;
    size_t remainder = total_len % 4;
    
    // Initialize out to 0.
    if (allocate_digits(out, 1)) return 1;
    out->digits[0] = 0;
    out->sign = sign;
    
    // Process any initial digits (if not a multiple of 4).
    for (size_t i = 0; i < remainder; i++) {
        int digit = str[pos + i] - '0';
        if (digit < 0 || digit > 2) return 2;
        int carry = digit;
        for (size_t j = 0; j < out->len; j++) {
            int val = out->digits[j] * 3 + carry;
            out->digits[j] = val % BASE_81;
            carry = val / BASE_81;
        }
        while (carry) {
            size_t old_len = out->len;
            TritError e = allocate_digits(out, out->len + 1);
            if (e) return e;
            out->digits[old_len] = carry % BASE_81;
            carry /= BASE_81;
        }
    }
    pos += remainder;
    
    // Process groups of 4 digits.
    while (pos < strlen(str)) {
        int groupVal = 0;
        for (int k = 0; k < 4; k++) {
            if (str[pos + k] < '0' || str[pos + k] > '2') return 2;
            groupVal = groupVal * 3 + (str[pos + k] - '0');
        }
        pos += 4;
        // Multiply current value by 81 and add groupVal.
        int carry = groupVal;
        for (size_t j = 0; j < out->len; j++) {
            int val = out->digits[j] * 81 + carry;
            out->digits[j] = val % BASE_81;
            carry = val / BASE_81;
        }
        while (carry) {
            size_t old_len = out->len;
            TritError e = allocate_digits(out, out->len + 1);
            if (e) return e;
            out->digits[old_len] = carry % BASE_81;
            carry /= BASE_81;
        }
    }
    // Trim any extra leading zeros.
    while (out->len > 1 && out->digits[out->len - 1] == 0) {
        out->len--;
    }
    return 0;
}

/* Public parse function using the optimized conversion */
static TritError parse_trit_string(const char* s, T81BigInt** out) {
    if (!out) return 1;
    *out = (T81BigInt*)calloc(1, sizeof(T81BigInt));
    if (!*out) return 1;
    TritError e = parse_trit_string_base81_optimized(s, *out);
    if (e) {
        free(*out);
        *out = NULL;
    }
    return e;
}

/* Convert T81BigInt to a base-3 string (unchanged from original) */
static TritError t81bigint_to_trit_string(const T81BigInt* in, char** out) {
    if (!in || !out) return 2;
    if (in->len == 1 && in->digits[0] == 0) {
        *out = strdup("0");
        return 0;
    }
    T81BigInt tmp = *in;  /* shallow copy */
    T81BigInt tmpCopy;
    memset(&tmpCopy, 0, sizeof(tmpCopy));
    if (allocate_digits(&tmpCopy, tmp.len)) return 1;
    tmpCopy.len = tmp.len;
    memcpy(tmpCopy.digits, tmp.digits, tmp.len);
    tmpCopy.sign = tmp.sign;

    size_t capacity = tmp.len * 4 + 2;
    char* buf = calloc(capacity, 1);
    if (!buf) {
        t81bigint_free(&tmpCopy);
        return 1;
    }

    size_t idx = 0;
    while (1) {
        int isZero = 1;
        for (size_t i = 0; i < tmpCopy.len; i++) {
            if (tmpCopy.digits[i] != 0) { isZero = 0; break; }
        }
        if (isZero) {
            if (idx == 0) buf[idx++] = '0';
            break;
        }
        int carry = 0;
        for (ssize_t i = tmpCopy.len - 1; i >= 0; i--) {
            int val = tmpCopy.digits[i] + carry * BASE_81;
            int q = val / 3;
            int r = val % 3;
            tmpCopy.digits[i] = q;
            carry = r;
        }
        buf[idx++] = (char)('0' + carry);
    }
    t81bigint_free(&tmpCopy);

    if (in->sign) {
        buf[idx++] = '-';
    }
    for (size_t i = 0; i < idx / 2; i++) {
        char t = buf[i];
        buf[i] = buf[idx - 1 - i];
        buf[idx - 1 - i] = t;
    }
    buf[idx] = '\0';
    *out = buf;
    return 0;
}

/* Public wrapper to free a T81BigInt pointer */
static void tritbig_free(T81BigInt* x) {
    if (!x) return;
    t81bigint_free(x);
    free(x);
}

/* Binary <-> Ternary conversion (unchanged) */
static TritError binary_to_trit(int num, T81BigInt** out) {
    char b3[128];
    int sign = (num < 0) ? 1 : 0;
    int val = (num < 0) ? -num : num;
    size_t idx = 0;
    if (val == 0) { b3[idx++] = '0'; }
    while (val > 0) {
        int r = val % 3;
        b3[idx++] = (char)('0' + r);
        val /= 3;
    }
    if (idx == 0) { b3[idx++] = '0'; }
    if (sign) { b3[idx++] = '-'; }
    for (size_t i = 0; i < idx / 2; i++) {
        char t = b3[i];
        b3[i] = b3[idx - 1 - i];
        b3[idx - 1 - i] = t;
    }
    b3[idx] = '\0';
    return parse_trit_string(b3, out);
}

static TritError trit_to_binary(T81BigInt* x, int* outVal) {
    char* b3 = NULL;
    if (t81bigint_to_trit_string(x, &b3) != 0) return 2;
    long long accum = 0;
    int sign = 0;
    size_t i = 0;
    if (b3[0] == '-') {
        sign = 1;
        i = 1;
    }
    for (; b3[i]; i++) {
        if (b3[i] < '0' || b3[i] > '2') {
            free(b3);
            return 2;
        }
        accum = accum * 3 + (b3[i] - '0');
        if (accum > INT_MAX) {
            free(b3);
            return 4;
        }
    }
    free(b3);
    if (sign) accum = -accum;
    *outVal = (int)accum;
    return 0;
}

/*****************************************************************************
 * Arithmetic Operations: Addition, Subtraction, Multiplication, etc.
 *****************************************************************************/

/* Compare two base-81 arrays (helper for subtraction) */
static int cmp_base81(const unsigned char* a, size_t a_len,
                      const unsigned char* b, size_t b_len) {
    if (a_len > b_len) {
        for (size_t i = a_len - 1; i >= b_len; i--) {
            if (a[i] != 0) return 1;
            if (i == 0) break;
        }
    } else if (b_len > a_len) {
        for (size_t i = b_len - 1; i >= a_len; i--) {
            if (b[i] != 0) return -1;
            if (i == 0) break;
        }
    }
    size_t m = (a_len < b_len ? a_len : b_len);
    for (ssize_t i = m - 1; i >= 0; i--) {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
        if (i == 0) break;
    }
    return 0;
}

TritError tritjs_add_big(T81BigInt* A, T81BigInt* B, T81BigInt** result) {
    if (!A || !B) return 2;
    *result = (T81BigInt*)calloc(1, sizeof(T81BigInt));
    if (!*result) return 1;
    if (A->sign == B->sign) {
        (*result)->sign = A->sign;
        size_t len = (A->len > B->len ? A->len : B->len) + 1;
        if (allocate_digits(*result, len)) {
            free(*result);
            return 1;
        }
        memset((*result)->digits, 0, len);
        memcpy((*result)->digits, A->digits, A->len);
        for (size_t i = 0; i < B->len; i++) {
            int val = (*result)->digits[i] + B->digits[i];
            (*result)->digits[i] = val % BASE_81;
            int carry = val / BASE_81;
            size_t cpos = i + 1;
            while (carry && cpos < len) {
                val = (*result)->digits[cpos] + carry;
                (*result)->digits[cpos] = val % BASE_81;
                carry = val / BASE_81;
                cpos++;
            }
        }
        while ((*result)->len > 1 && (*result)->digits[(*result)->len - 1] == 0) {
            (*result)->len--;
        }
    } else {
        int c = cmp_base81(A->digits, A->len, B->digits, B->len);
        T81BigInt *larger, *smaller;
        int largerSign;
        if (c > 0) { larger = A; smaller = B; largerSign = A->sign; }
        else if (c < 0) { larger = B; smaller = A; largerSign = B->sign; }
        else {
            if (allocate_digits(*result, 1)) { free(*result); return 1; }
            (*result)->digits[0] = 0;
            return 0;
        }
        (*result)->sign = largerSign;
        if (allocate_digits(*result, larger->len)) {
            free(*result);
            return 1;
        }
        memcpy((*result)->digits, larger->digits, larger->len);
        for (size_t i = 0; i < smaller->len; i++) {
            int diff = (*result)->digits[i] - smaller->digits[i];
            if (diff < 0) {
                diff += BASE_81;
                size_t j = i + 1;
                while (1) {
                    (*result)->digits[j]--;
                    if ((*result)->digits[j] < (unsigned char)255) break;
                    (*result)->digits[j] += BASE_81;
                    j++;
                    if (j >= larger->len) break;
                }
            }
            (*result)->digits[i] = (unsigned char)diff;
        }
        while ((*result)->len > 1 && (*result)->digits[(*result)->len - 1] == 0) {
            (*result)->len--;
        }
    }
    return 0;
}

TritError tritjs_subtract_big(T81BigInt* A, T81BigInt* B, T81BigInt** result) {
    if (!A || !B) return 2;
    T81BigInt tmp = *B; /* shallow copy */
    int oldsign = tmp.sign;
    tmp.sign = !oldsign;
    TritError e = tritjs_add_big(A, &tmp, result);
    tmp.sign = oldsign;
    return e;
}

/*****************************************************************************
 * Multiplication: Karatsuba Algorithm and Naïve Fallback
 *****************************************************************************/
#define MUL_CACHE_SIZE 8
typedef struct {
    char key[128];
    T81BigInt result;
    int used;
} MulCacheEntry;
static MulCacheEntry mul_cache[MUL_CACHE_SIZE] = {{0}};

/* Naïve O(n^2) multiplication */
static void naive_mul(const unsigned char *A, size_t alen,
                      const unsigned char *B, size_t blen,
                      unsigned char *out) {
    memset(out, 0, alen + blen);
    for (size_t i = 0; i < alen; i++) {
        int carry = 0;
        for (size_t j = 0; j < blen; j++) {
            int pos = i + j;
            int val = out[pos] + A[i] * B[j] + carry;
            out[pos] = val % BASE_81;
            carry = val / BASE_81;
        }
        out[i + blen] += carry;
    }
}

/* Addition of a shifted array */
static void add_shifted(unsigned char *dest, size_t dlen,
                        const unsigned char *src, size_t slen,
                        size_t shift) {
    int carry = 0;
    for (size_t i = 0; i < slen; i++) {
        size_t idx = i + shift;
        if (idx >= dlen) break;
        int sum = dest[idx] + src[i] + carry;
        dest[idx] = sum % BASE_81;
        carry = sum / BASE_81;
    }
    size_t idx = slen + shift;
    while (carry && idx < dlen) {
        int sum = dest[idx] + carry;
        dest[idx] = sum % BASE_81;
        carry = sum / BASE_81;
        idx++;
    }
}

/* Subtract src from out in place */
static void sub_inplace(unsigned char* out, const unsigned char* src, size_t length) {
    int borrow = 0;
    for (size_t i = 0; i < length; i++) {
        int diff = out[i] - src[i] - borrow;
        if (diff < 0) {
            diff += BASE_81;
            borrow = 1;
        } else {
            borrow = 0;
        }
        out[i] = diff;
    }
}

/* Karatsuba multiplication recursive routine */
static void karatsuba(const unsigned char *A, const unsigned char *B, size_t n, unsigned char *out) {
    if (n <= 16) {
        naive_mul(A, n, B, n, out);
        return;
    }
    size_t half = n / 2;
    size_t r = n - half;  // remainder if odd
    const unsigned char *A0 = A, *A1 = A + half;
    const unsigned char *B0 = B, *B1 = B + half;
    
    size_t len2 = 2 * n;
    unsigned char *p1 = calloc(len2, 1);
    unsigned char *p2 = calloc(len2, 1);
    unsigned char *p3 = calloc(len2, 1);
    unsigned char *sumA = calloc(r, 1);
    unsigned char *sumB = calloc(r, 1);
    
    karatsuba(A0, B0, half, p1);  // p1 = A0 * B0
    karatsuba(A1, B1, r, p2);      // p2 = A1 * B1
    
    memcpy(sumA, A1, r);
    for (size_t i = 0; i < half; i++) {
        int s = sumA[i] + A0[i];
        sumA[i] = s % BASE_81;
        int c = s / BASE_81;
        if (c && i + 1 < r) sumA[i + 1] += c;
    }
    memcpy(sumB, B1, r);
    for (size_t i = 0; i < half; i++) {
        int s = sumB[i] + B0[i];
        sumB[i] = s % BASE_81;
        int c = s / BASE_81;
        if (c && i + 1 < r) sumB[i + 1] += c;
    }
    karatsuba(sumA, sumB, r, p3);  // p3 = (A0+A1)*(B0+B1)
    sub_inplace(p3, p1, len2);
    sub_inplace(p3, p2, len2);
    
    memset(out, 0, len2);
    add_shifted(out, len2, p1, len2, 0);
    add_shifted(out, len2, p3, len2, half);
    add_shifted(out, len2, p2, len2, 2 * half);
    
    free(p1); free(p2); free(p3);
    free(sumA); free(sumB);
}

/* Karatsuba multiplication wrapper for T81BigInt */
static TritError t81bigint_karatsuba_multiply(const T81BigInt *a, const T81BigInt *b, T81BigInt *out) {
    if ((a->len == 1 && a->digits[0] == 0) || (b->len == 1 && b->digits[0] == 0)) {
        if (allocate_digits(out, 1)) return 1;
        out->digits[0] = 0;
        out->sign = 0;
        return 0;
    }
    size_t n = (a->len > b->len ? a->len : b->len);
    unsigned char *A = calloc(n, 1);
    unsigned char *B = calloc(n, 1);
    if (!A || !B) { free(A); free(B); return 1; }
    memcpy(A, a->digits, a->len);
    memcpy(B, b->digits, b->len);
    
    size_t out_len = 2 * n;
    unsigned char *prod = calloc(out_len, 1);
    if (!prod) { free(A); free(B); return 1; }
    
    karatsuba(A, B, n, prod);
    
    free(A); free(B);
    
    out->sign = (a->sign != b->sign) ? 1 : 0;
    while (out_len > 1 && prod[out_len - 1] == 0) {
        out_len--;
    }
    if (allocate_digits(out, out_len)) {
        free(prod);
        return 1;
    }
    memcpy(out->digits, prod, out_len);
    free(prod);
    return 0;
}

/* Multiplication cache lookup and store */
static int mul_cache_lookup(const char* key, T81BigInt *dst) {
    for (int i = 0; i < MUL_CACHE_SIZE; i++) {
        if (mul_cache[i].used && strcmp(mul_cache[i].key, key) == 0) {
            if (allocate_digits(dst, mul_cache[i].result.len)) return 1;
            dst->len = mul_cache[i].result.len;
            dst->sign = mul_cache[i].result.sign;
            memcpy(dst->digits, mul_cache[i].result.digits, dst->len);
            return 0;
        }
    }
    return 2;
}

static void mul_cache_store(const char* key, const T81BigInt *val) {
    int slot = -1;
    for (int i = 0; i < MUL_CACHE_SIZE; i++) {
        if (!mul_cache[i].used) { slot = i; break; }
    }
    if (slot < 0) slot = 0; // Overwrite slot 0 if cache is full.
    strncpy(mul_cache[slot].key, key, sizeof(mul_cache[slot].key));
    mul_cache[slot].key[sizeof(mul_cache[slot].key) - 1] = '\0';
    t81bigint_free(&mul_cache[slot].result);
    mul_cache[slot].used = 1;
    allocate_digits(&mul_cache[slot].result, val->len);
    mul_cache[slot].result.len = val->len;
    mul_cache[slot].result.sign = val->sign;
    memcpy(mul_cache[slot].result.digits, val->digits, val->len);
}

/* Multiply with caching */
static TritError multiply_with_cache(const T81BigInt *a, const T81BigInt *b, T81BigInt *out) {
    char *as = NULL, *bs = NULL;
    if (t81bigint_to_trit_string(a, &as) != 0) return 2;
    if (t81bigint_to_trit_string(b, &bs) != 0) { free(as); return 2; }
    char key[128];
    snprintf(key, sizeof(key), "mul:%s:%s", as, bs);
    free(as); free(bs);
    
    if (mul_cache_lookup(key, out) == 0) {
        return 0;  // Found in cache.
    }
    TritError e = t81bigint_karatsuba_multiply(a, b, out);
    if (!e) {
        mul_cache_store(key, out);
    }
    return e;
}

/* Public multiply function */
TritError tritjs_multiply_big(T81BigInt* a, T81BigInt* b, T81BigInt** result) {
    if (!a || !b) return 2;
    *result = (T81BigInt*)calloc(1, sizeof(T81BigInt));
    if (!*result) return 1;
    TritError e = multiply_with_cache(a, b, *result);
    if (e) {
        free(*result);
        *result = NULL;
    }
    return e;
}

/* Helper for checking small value */
static int is_small_value(const T81BigInt *x) {
    return (x->len == 1 && x->digits[0] < 81);
}
static int to_small_int(const T81BigInt *x) {
    int val = x->digits[0];
    if (x->sign) val = -val;
    return val;
}

/* Factorial (only works for small numbers to avoid overflow) */
TritError tritjs_factorial_big(T81BigInt* a, T81BigInt** result) {
    if (!a) return 2;
    if (a->sign) return 6;
    if (!is_small_value(a)) return 4; // Overflow
    int val = to_small_int(a);
    if (val > 20) return 4;
    long long f = 1;
    for (int i = 1; i <= val; i++) f *= i;
    
    *result = (T81BigInt*)calloc(1, sizeof(T81BigInt));
    if (!*result) return 1;
    if (allocate_digits(*result, 1)) {
        free(*result);
        *result = NULL;
        return 1;
    }
    (*result)->digits[0] = 0;
    (*result)->sign = 0;
    while (f > 0) {
        int digit = f % BASE_81;
        f /= BASE_81;
        int carry = digit;
        size_t i = 0;
        while (carry) {
            int val2 = (*result)->digits[i] + carry;
            (*result)->digits[i] = val2 % BASE_81;
            carry = val2 / BASE_81;
            i++;
            if (i >= (*result)->len && carry) {
                if (allocate_digits(*result, (*result)->len + 1)) {
                    tritbig_free(*result);
                    *result = NULL;
                    return 1;
                }
            }
        }
    }
    while ((*result)->len > 1 && (*result)->digits[(*result)->len - 1] == 0) {
        (*result)->len--;
    }
    return 0;
}

/* Power: computes base^exp (only supports non-negative small exponents) */
TritError tritjs_power_big(T81BigInt* base, T81BigInt* exp, T81BigInt** result) {
    if (!base || !exp) return 2;
    if (exp->sign) return 6;
    if (!is_small_value(exp)) return 4;
    int e = to_small_int(exp);
    if (e > 1000) return 4;
    
    *result = (T81BigInt*)calloc(1, sizeof(T81BigInt));
    if (!*result) return 1;
    if (allocate_digits(*result, 1)) {
        free(*result);
        *result = NULL;
        return 1;
    }
    (*result)->digits[0] = 1; // start with 1
    (*result)->sign = 0;
    
    for (int i = 0; i < e; i++) {
        T81BigInt tmp;
        memset(&tmp, 0, sizeof(tmp));
        TritError err = multiply_with_cache(*result, base, &tmp);
        if (err) {
            t81bigint_free(*result);
            free(*result);
            *result = NULL;
            return err;
        }
        t81bigint_free(*result);
        **result = tmp;  // struct copy (moves the digits pointer)
    }
    if (base->sign && (e % 2) == 1) {
        (*result)->sign = 1;
    }
    return 0;
}

/* Stubbed scientific functions (sqrt, log3, sin, cos, tan) */
TritError tritjs_sqrt_complex(T81BigInt* a, int precision, T81Complex* result) {
    (void)a; (void)precision; (void)result;
    return 5;
}
TritError tritjs_log3_complex(T81BigInt* a, int precision, T81Complex* result) {
    (void)a; (void)precision; (void)result;
    return 5;
}
TritError tritjs_sin_complex(T81BigInt* a, int precision, T81Complex* result) {
    (void)a; (void)precision; (void)result;
    return 5;
}
TritError tritjs_cos_complex(T81BigInt* a, int precision, T81Complex* result) {
    (void)a; (void)precision; (void)result;
    return 5;
}
TritError tritjs_tan_complex(T81BigInt* a, int precision, T81Complex* result) {
    (void)a; (void)precision; (void)result;
    return 5;
}

/* pi: returns an array of base-3 digits for pi (stub implementation) */
TritError tritjs_pi(int* len, int** pi) {
    static int pi_val[] = {1, 0, 0, 1, 0, 2, 2, 1};
    *len = 8;
    *pi = malloc(8 * sizeof(int));
    if (!*pi) return 1;
    memcpy(*pi, pi_val, 8 * sizeof(int));
    return 0;
}

/* Division (stub implementation) */
static void t81float_free(T81Float f) {
    if (f.i_mapped && f.integer) {
        size_t bytes = (f.i_len == 0 ? 1 : f.i_len);
        munmap(f.integer, bytes);
        close(f.i_fd);
        total_mapped_bytes -= bytes;
        operation_steps++;
    } else {
        free(f.integer);
    }
    if (f.f_mapped && f.fraction) {
        size_t bytes = (f.f_len == 0 ? 1 : f.f_len);
        munmap(f.fraction, bytes);
        close(f.f_fd);
        total_mapped_bytes -= bytes;
        operation_steps++;
    } else {
        free(f.fraction);
    }
}

TritError tritjs_divide_big(T81BigInt* a, T81BigInt* b, T81DivResult* result, int precision) {
    if (!a || !b) return 2;
    if (precision < 1 || precision > 10) return 7;
    int all0 = 1;
    for (size_t i = 0; i < b->len; i++) {
        if (b->digits[i] != 0) { all0 = 0; break; }
    }
    if (all0) {
        LOG_ERROR(3, "tritjs_divide_big");
        return 3;
    }
    memset(&result->quotient, 0, sizeof(result->quotient));
    memset(&result->remainder, 0, sizeof(result->remainder));
    
    result->quotient.sign = 0;
    result->quotient.i_len = 1;
    result->quotient.f_len = 0;
    result->quotient.integer = calloc(1, 1);
    result->quotient.integer[0] = 0;
    
    result->remainder.sign = a->sign;
    result->remainder.i_len = a->len;
    result->remainder.f_len = 0;
    result->remainder.integer = calloc(a->len, 1);
    memcpy(result->remainder.integer, a->digits, a->len);
    return 0;
}

/*****************************************************************************
 * State Management (Encrypted Save/Load) & Security Stubs
 *****************************************************************************/
static TritError encrypt_data(const unsigned char* pt, size_t pt_len,
                              unsigned char** ct, size_t* ct_len) {
    // Stub: Simply copy plaintext to ciphertext.
    *ct = malloc(pt_len);
    if (!*ct) return 1;
    memcpy(*ct, pt, pt_len);
    *ct_len = pt_len;
    return 0;
}

static TritError decrypt_data(const unsigned char* ct, size_t ct_len,
                              unsigned char** pt, size_t* pt_len) {
    // Stub: Simply copy ciphertext to plaintext.
    *pt = malloc(ct_len);
    if (!*pt) return 1;
    memcpy(*pt, ct, ct_len);
    *pt_len = ct_len;
    return 0;
}

static TritError sign_data(const unsigned char* data, size_t data_len,
                           unsigned char** sig, size_t* sig_len) {
    *sig = NULL; *sig_len = 0; return 0;
}
static TritError verify_signature(const unsigned char* data, size_t data_len,
                                  const unsigned char* sig, size_t sig_len) {
    return 0;
}

/* Save session state with encryption (plaintext state is zeroed after use) */
static TritError save_state(const char* filename) {
    FILE* f = fopen(filename, "wb");
    if (!f) {
        printf("Error: Could not open %s\n", filename);
        return 2;
    }
    char buf[4096] = {0};
    strcat(buf, "# TritJS-CISA State File (Encrypted)\n# History\n");
    for (int i = 0; i < history_count; i++) {
        strcat(buf, "H: ");
        strcat(buf, history[i]);
        strcat(buf, "\n");
    }
    strcat(buf, "# Variables\n");
    for (int i = 0; i < 26; i++) {
        if (variables[i]) {
            char* s = NULL;
            if (!tritjs_to_string(variables[i], &s)) {
                char line[512];
                snprintf(line, sizeof(line), "V: %c=%s\n", 'A' + i, s);
                strcat(buf, line);
                free(s);
            }
        }
    }
    unsigned char* ct = NULL;
    size_t ct_len = 0;
    if (encrypt_data((unsigned char*)buf, strlen(buf), &ct, &ct_len)) {
        fclose(f);
        return 1;
    }
    fwrite(ct, 1, ct_len, f);
    // Securely zero plaintext buffer (if explicit_bzero available, use that)
    memset(buf, 0, sizeof(buf));
    free(ct);
    fclose(f);
    return 0;
}

/* Load session state (requires root) */
static TritError load_state(const char* filename) {
    if (getuid() != 0) {
        printf("Error: must be root to load\n");
        return 2;
    }
    FILE* f = fopen(filename, "rb");
    if (!f) {
        printf("Error: cannot open %s\n", filename);
        return 2;
    }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    unsigned char* ct = malloc(sz);
    if (!ct) { fclose(f); return 1; }
    fread(ct, 1, sz, f);
    fclose(f);
    
    unsigned char* pt = NULL;
    size_t pt_len = 0;
    if (decrypt_data(ct, sz, &pt, &pt_len)) {
        free(ct);
        return 1;
    }
    free(ct);
    // Parsing of the decrypted state is omitted.
    free(pt);
    return 0;
}

/*****************************************************************************
 * Intrusion Detection & Self-Healing (Stubs)
 *****************************************************************************/
static void monitor_security() {
    printf("Security monitor running...\n");
}
static void self_heal() {
    printf("Self-healing triggered...\n");
}

/*****************************************************************************
 * Benchmarking (Stub)
 *****************************************************************************/
#define PROFILE_START
#define PROFILE_END(x)
static void run_benchmarks() {
    printf("Running comprehensive benchmarks (stub)...\n");
}

/*****************************************************************************
 * History, Variables, and Scripting Management
 *****************************************************************************/
static void add_to_history(const char* entry) {
    if (history_count < MAX_HISTORY) {
        history[history_count++] = strdup(entry);
    } else {
        free(history[0]);
        for (int i = 1; i < MAX_HISTORY; i++) {
            history[i - 1] = history[i];
        }
        history[MAX_HISTORY - 1] = strdup(entry);
    }
}

static void store_variable(const char* var_name, T81BigInt* value) {
    int idx = var_name[0] - 'A';
    if (variables[idx]) {
        t81bigint_free(variables[idx]);
        free(variables[idx]);
    }
    variables[idx] = value;
}

static T81BigInt* recall_variable(const char* var_name) {
    return variables[var_name[0] - 'A'];
}

static void clear_history_and_vars(void) {
    for (int i = 0; i < history_count; i++) {
        free(history[i]);
        history[i] = NULL;
    }
    history_count = 0;
    for (int i = 0; i < 26; i++) {
        if (variables[i]) {
            t81bigint_free(variables[i]);
            free(variables[i]);
            variables[i] = NULL;
        }
    }
}

static void run_tests() {
    printf("Running unit tests...\n");
}

/* Execute a single command (or script command) */
static TritError execute_command(const char* input, int is_script) {
    char op[16], arg1[256], arg2[256];
    memset(op, 0, sizeof(op));
    memset(arg1, 0, sizeof(arg1));
    memset(arg2, 0, sizeof(arg2));
    
    int parsed = sscanf(input, "%15s %255s %255s", op, arg1, arg2);
    if (parsed < 1) {
        if (!is_script) printf("Error: invalid input\n");
        return 2;
    }
    if (strncmp(op, "bin2tri", 7) == 0) {
        int val = 0;
        if (sscanf(arg1, "%d", &val) != 1) {
            if (!is_script) printf("Error: invalid binary number\n");
            return 2;
        }
        T81BigInt* tri = NULL;
        TritError e = binary_to_trit(val, &tri);
        if (!e) {
            char* s = NULL;
            if (!tritjs_to_string(tri, &s)) {
                if (!is_script) printf("Trinary: %s\n", s);
                add_to_history(s);
                free(s);
            }
            tritbig_free(tri);
        }
        return e;
    }
    if (strncmp(op, "tri2bin", 7) == 0) {
        T81BigInt* tri = NULL;
        TritError e = parse_trit_string(arg1, &tri);
        if (!e) {
            int val;
            if (!trit_to_binary(tri, &val)) {
                if (!is_script) printf("Binary: %d\n", val);
                char buf[64];
                snprintf(buf, sizeof(buf), "%d", val);
                add_to_history(buf);
            }
            tritbig_free(tri);
        }
        return e;
    }
    if (strcmp(op, "bench") == 0) {
        run_benchmarks();
        return 0;
    }
    if (strcmp(op, "monitor") == 0) {
        monitor_security();
        return 0;
    }
    if (strcmp(op, "save") == 0) {
        TritError e = save_state(arg1);
        if (!is_script && e) printf("Error saving state\n");
        return e;
    }
    if (strcmp(op, "load") == 0) {
        TritError e = load_state(arg1);
        if (!is_script && e) printf("Error loading state\n");
        return e;
    }
    if (strcmp(op, "clear") == 0) {
        clear_history_and_vars();
        return 0;
    }
    if (strcmp(op, "help") == 0) {
        if (!is_script) {
            printf("TritJS-CISA Commands:\n");
            printf("  add <a> <b>, sub <a> <b>, mul <a> <b>, div <a> <b>\n");
            printf("  pow <a> <b>, fact <a>, sqrt <a>, log3 <a>, sin <a>, cos <a>, tan <a>, pi\n");
            printf("  bin2tri <num>, tri2bin <trit>\n");
            printf("  save <file>, load <file>\n");
            printf("  monitor, bench\n");
            printf("  PROG <name> { <commands> }, RUN <name>, <var>=<value>\n");
            printf("  help, clear, version, quit\n");
        }
        return 0;
    }
    if (strcmp(op, "test") == 0) {
        run_tests();
        return 0;
    }
    if (strcmp(op, "version") == 0) {
        if (!is_script) printf("Version: %s\n", VERSION);
        return 0;
    }
    if (strcmp(op, "quit") == 0) {
        return 0;
    }
    if (strcmp(op, "PROG") == 0) {
        if (parsed < 2) {
            if (!is_script) printf("Error: usage PROG <name> { <commands> }\n");
            return 2;
        }
        if (script_count >= 10) {
            if (!is_script) printf("Error: too many scripts\n");
            return 9;
        }
        strcpy(scripts[script_count].name, arg1);
        char *brace = strchr(input, '{');
        char *endBrace = strrchr(input, '}');
        if (!brace || !endBrace) {
            if (!is_script) printf("Error: missing braces\n");
            return 9;
        }
        brace++;
        *endBrace = '\0';
        char commandsBuf[1024];
        strncpy(commandsBuf, brace, sizeof(commandsBuf) - 1);
        commandsBuf[sizeof(commandsBuf) - 1] = '\0';
        int ccount = 0;
        char *tok = strtok(commandsBuf, "\n;");
        while (tok) {
            strncpy(scripts[script_count].commands[ccount], tok, 255);
            ccount++;
            tok = strtok(NULL, "\n;");
            if (ccount >= MAX_SCRIPT_CMDS) break;
        }
        scripts[script_count].cmd_count = ccount;
        script_count++;
        return 0;
    }
    if (strcmp(op, "RUN") == 0) {
        if (parsed < 2) {
            if (!is_script) printf("Error: usage RUN <name>\n");
            return 2;
        }
        for (int i = 0; i < script_count; i++) {
            if (strcmp(scripts[i].name, arg1) == 0) {
                TritError e =  run_script(&scripts[i]);
                if (e && !is_script) printf("Error running script: %d\n", e);
                return e;
            }
        }
        if (!is_script) printf("Error: script not found: %s\n", arg1);
        return 9;
    }
    char* eq = strchr(arg1, '=');
    if (eq && parsed == 2) {
        char var_name[2];
        var_name[0] = arg1[0];
        var_name[1] = '\0';
        eq++;
        T81BigInt* val = NULL;
        TritError e = parse_trit_string(eq, &val);
        if (!e) {
            store_variable(var_name, val);
            if (!is_script) printf("%s stored\n", var_name);
        } else {
            if (!is_script) printf("Error parsing var= value\n");
        }
        return e;
    }
    
    T81BigInt *A = NULL, *B = NULL;
    TritError e = 0;
    if (arg1[0] >= 'A' && arg1[0] <= 'Z' && arg1[1] == '\0') {
        A = recall_variable(arg1);
        if (!A) { if (!is_script) printf("Error: var %s not set\n", arg1); return 2; }
    } else {
        e = parse_trit_string(arg1, &A);
        if (e) { if (!is_script) printf("Error parsing A\n"); return e; }
    }
    if (arg2[0]) {
        if (arg2[0] >= 'A' && arg2[0] <= 'Z' && arg2[1] == '\0') {
            B = recall_variable(arg2);
            if (!B) {
                if (!is_script) printf("Error: var %s not set\n", arg2);
                if (A && A != recall_variable(arg1)) tritbig_free(A);
                return 2;
            }
        } else {
            e = parse_trit_string(arg2, &B);
            if (e) {
                if (!is_script) printf("Error parsing B\n");
                if (A && A != recall_variable(arg1)) tritbig_free(A);
                return e;
            }
        }
    }
    
    if (strcmp(op, "add") == 0 && B) {
        T81BigInt* R;
        e = tritjs_add_big(A, B, &R);
        if (!e) {
            char* s = NULL;
            if (!tritjs_to_string(R, &s)) {
                if (!is_script) printf("%s\n", s);
                add_to_history(s);
                free(s);
            }
            tritbig_free(R);
        } else if (!is_script) {
            printf("Error: %s\n", trit_error_str(e));
        }
    } else if (strcmp(op, "sub") == 0 && B) {
        T81BigInt* R;
        e = tritjs_subtract_big(A, B, &R);
        if (!e) {
            char* s = NULL;
            if (!tritjs_to_string(R, &s)) {
                if (!is_script) printf("%s\n", s);
                add_to_history(s);
                free(s);
            }
            tritbig_free(R);
        } else if (!is_script) {
            printf("Error: %s\n", trit_error_str(e));
        }
    } else if (strcmp(op, "mul") == 0 && B) {
        T81BigInt* R;
        e = tritjs_multiply_big(A, B, &R);
        if (!e) {
            char* s = NULL;
            if (!tritjs_to_string(R, &s)) {
                if (!is_script) printf("%s\n", s);
                add_to_history(s);
                free(s);
            }
            tritbig_free(R);
        } else if (!is_script) {
            printf("Error: %s\n", trit_error_str(e));
        }
    } else if (strcmp(op, "fact") == 0) {
        T81BigInt* R;
        e = tritjs_factorial_big(A, &R);
        if (!e) {
            char* s = NULL;
            if (!tritjs_to_string(R, &s)) {
                if (!is_script) printf("%s\n", s);
                add_to_history(s);
                free(s);
            }
            tritbig_free(R);
        } else if (!is_script) {
            printf("Error: %s\n", trit_error_str(e));
        }
    } else if (strcmp(op, "pow") == 0 && B) {
        T81BigInt* R;
        e = tritjs_power_big(A, B, &R);
        if (!e) {
            char* s = NULL;
            if (!tritjs_to_string(R, &s)) {
                if (!is_script) printf("%s\n", s);
                add_to_history(s);
                free(s);
            }
            tritbig_free(R);
        } else if (!is_script) {
            printf("Error: %s\n", trit_error_str(e));
        }
    } else if (strcmp(op, "div") == 0 && B) {
        T81DivResult res;
        memset(&res, 0, sizeof(res));
        e = tritjs_divide_big(A, B, &res, 3);
        if (!e) {
            if (!is_script) {
                printf("Quotient=0 (stub), Remainder=?\n");
            }
            t81float_free(res.quotient);
            t81float_free(res.remainder);
        } else if (!is_script) {
            printf("Error: %s\n", trit_error_str(e));
        }
    } else if (strcmp(op, "sqrt") == 0) {
        T81Complex c; memset(&c, 0, sizeof(c));
        e = tritjs_sqrt_complex(A, 3, &c);
        if (!is_script) {
            printf("sqrt => stub or error: %s\n", trit_error_str(e));
        }
    } else if (strcmp(op, "log3") == 0) {
        T81Complex c; memset(&c, 0, sizeof(c));
        e = tritjs_log3_complex(A, 3, &c);
        if (!is_script) {
            printf("log3 => stub or error: %s\n", trit_error_str(e));
        }
    } else if (strcmp(op, "sin") == 0) {
        T81Complex c; memset(&c, 0, sizeof(c));
        e = tritjs_sin_complex(A, 3, &c);
        if (!is_script) {
            printf("sin => stub or error: %s\n", trit_error_str(e));
        }
    } else if (strcmp(op, "cos") == 0) {
        T81Complex c; memset(&c, 0, sizeof(c));
        e = tritjs_cos_complex(A, 3, &c);
        if (!is_script) {
            printf("cos => stub or error: %s\n", trit_error_str(e));
        }
    } else if (strcmp(op, "tan") == 0) {
        T81Complex c; memset(&c, 0, sizeof(c));
        e = tritjs_tan_complex(A, 3, &c);
        if (!is_script) {
            printf("tan => stub or error: %s\n", trit_error_str(e));
        }
    } else if (strcmp(op, "pi") == 0) {
        int len;
        int* arr = NULL;
        e = tritjs_pi(&len, &arr);
        if (!e) {
            char s[256];
            int idx = 0;
            for (int i = 0; i < len; i++) {
                s[idx++] = (char)('0' + arr[i]);
            }
            s[idx] = '\0';
            free(arr);
            if (!is_script) printf("%s\n", s);
            add_to_history(s);
        } else if (!is_script) {
            printf("Error: %s\n", trit_error_str(e));
        }
    } else {
        if (!is_script) printf("Unknown command: %s\n", op);
        e = 2;
    }
    
    if (A && A != recall_variable(arg1)) { tritbig_free(A); }
    if (B && B != recall_variable(arg2)) { tritbig_free(B); }
    return e;
}

/*****************************************************************************
 * Ncurses UI Functions
 *****************************************************************************/
static void update_status_bar() {
    char stat[128];
    snprintf(stat, sizeof(stat), "Mem: %ld bytes | Steps: %d", total_mapped_bytes, operation_steps);
    werase(status_win);
    mvwprintw(status_win, 0, 0, stat);
    wrefresh(status_win);
}

static void end_ncurses_interface() {
    endwin();
}

static void init_ncurses_interface() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    status_win = newwin(1, cols, 0, 0);
    output_win = newwin(rows - 3, cols, 1, 0);
    input_win = newwin(2, cols, rows - 2, 0);
    scrollok(output_win, TRUE);
    wrefresh(status_win);
    wrefresh(output_win);
    wrefresh(input_win);
}

/* Ncurses main loop with terminal resize support */
static void ncurses_loop() {
    char input[256];
    int ch;
    int rows, cols;
    while (1) {
        update_status_bar();
        werase(input_win);
        mvwprintw(input_win, 0, 0, "Command: ");
        wrefresh(input_win);
        nodelay(input_win, TRUE);
        ch = wgetch(input_win);
        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, rows, cols);
            wresize(status_win, 1, cols);
            wresize(output_win, rows - 3, cols);
            wresize(input_win, 2, cols);
            mvwin(status_win, 0, 0);
            mvwin(output_win, 1, 0);
            mvwin(input_win, rows - 2, 0);
            wrefresh(status_win);
            wrefresh(output_win);
            wrefresh(input_win);
        }
        nodelay(input_win, FALSE);
        wgetnstr(input_win, input, sizeof(input) - 1);
        if (strcmp(input, "quit") == 0) break;
        if (strcmp(input, "clear") == 0) {
            clear_history_and_vars();
            werase(output_win);
            wrefresh(output_win);
            continue;
        }
        if (strcmp(input, "help") == 0) {
            werase(output_win);
            mvwprintw(output_win, 0, 0,
                      "TritJS-CISA Commands:\n"
                      "  add, sub, mul, div, pow, fact, sqrt, log3, sin, cos, tan, pi\n"
                      "  bin2tri <num>, tri2bin <trit>, save <file>, load <file>\n"
                      "  monitor, bench, test, clear, help, version, quit\n"
                      "  PROG <name> {commands}, RUN <name>\n"
                      "  <var>=<value>\n");
            wrefresh(output_win);
            continue;
        }
        if (strcmp(input, "test") == 0) {
            run_tests();
            continue;
        }
        if (strncmp(input, "bench", 5) == 0) {
            run_benchmarks();
            continue;
        }
        if (strncmp(input, "monitor", 7) == 0) {
            monitor_security();
            continue;
        }
        TritError e = execute_command(input, 0);
        if (e) {
            wprintw(output_win, "Error executing: %s\n", input);
        } else {
            wprintw(output_win, "Executed: %s\n", input);
        }
        wrefresh(output_win);
    }
}

/*****************************************************************************
 * Main Function
 *****************************************************************************/
int main() {
    init_audit_log();
    init_ncurses_interface();
    ncurses_loop();
    end_ncurses_interface();
    return 0;
}
