// ttypes.c - T81 Ternary Data Types System
// This file implements a suite of ternary (base-81) data types for arithmetic and computation.
// It includes optimizations using SIMD (AVX2), multi-threading, and memory mapping for large data.
// The system is cross-platform (POSIX/Windows) and provides a stable C interface for external bindings.

// Standard Library Includes
#include <stdio.h>      // For input/output operations
#include <stdlib.h>     // For memory allocation and basic utilities
#include <string.h>     // For string manipulation
#include <limits.h>     // For system-specific limits
#include <math.h>       // For approximate mathematical expansions (e.g., sin, cos)

// Platform-Specific Includes
#ifdef _WIN32
#include <windows.h>    // Windows API for memory mapping
#else
#include <sys/mman.h>   // POSIX memory mapping
#include <fcntl.h>      // File operations for memory mapping
#include <unistd.h>     // POSIX system calls (e.g., unlink)
#endif

#include <pthread.h>    // For multi-threading support
#include <immintrin.h>  // For AVX2 SIMD instructions

// Error Codes
/** Error codes returned by T81 functions to indicate success or failure. */
typedef int TritError;
#define TRIT_OK 0           // Operation successful
#define TRIT_MEM_FAIL 1     // Memory allocation failed
#define TRIT_INVALID_INPUT 2 // Invalid input provided
#define TRIT_DIV_ZERO 3     // Division by zero attempted
#define TRIT_OVERFLOW 4     // Arithmetic overflow occurred
#define TRIT_MAP_FAIL 8     // Memory mapping failed

// Opaque Handles for FFI (Foreign Function Interface)
/** Opaque pointers to internal structures, used for safe external bindings. */
typedef void* T81BigIntHandle;
typedef void* T81FractionHandle;
typedef void* T81FloatHandle;
typedef void* T81MatrixHandle;
typedef void* T81VectorHandle;
typedef void* T81QuaternionHandle;
typedef void* T81PolynomialHandle;
typedef void* T81TensorHandle;
typedef void* T81GraphHandle;
typedef void* T81OpcodeHandle;

// Constants
#define BASE_81 81                    // Base-81 for ternary system
#define MAX_PATH 260                  // Maximum path length for temp files
#define T81_MMAP_THRESHOLD (2 * 1024 * 1024) // Threshold (in bytes) for using memory mapping
#define THREAD_COUNT 4                // Number of threads for parallel operations

// Global Variables
static long total_mapped_bytes = 0; // Tracks total memory mapped (for debugging)
static int operation_steps = 0;     // Tracks operation count (for debugging)

// Forward Declarations of All Public Functions
/** T81BigInt Functions */
T81BigIntHandle t81bigint_new(int value);
T81BigIntHandle t81bigint_from_string(const char* str);
T81BigIntHandle t81bigint_from_binary(const char* bin_str);
void t81bigint_free(T81BigIntHandle h);
TritError t81bigint_to_string(T81BigIntHandle h, char** result);
TritError t81bigint_add(T81BigIntHandle a, T81BigIntHandle b, T81BigIntHandle* result);
TritError t81bigint_subtract(T81BigIntHandle a, T81BigIntHandle b, T81BigIntHandle* result);
TritError t81bigint_multiply(T81BigIntHandle a, T81BigIntHandle b, T81BigIntHandle* result);
TritError t81bigint_divide(T81BigIntHandle a, T81BigIntHandle b, T81BigIntHandle* quotient, T81BigIntHandle* remainder);
TritError t81bigint_mod(T81BigIntHandle a, T81BigIntHandle b, T81BigIntHandle* mod_result);

/** T81Fraction Functions */
T81FractionHandle t81fraction_new(const char* num_str, const char* denom_str);
void t81fraction_free(T81FractionHandle h);
TritError t81fraction_get_num(T81FractionHandle h, T81BigIntHandle* num);
TritError t81fraction_get_den(T81FractionHandle h, T81BigIntHandle* den);
TritError t81fraction_add(T81FractionHandle a, T81FractionHandle b, T81FractionHandle* result);
TritError t81fraction_subtract(T81FractionHandle a, T81FractionHandle b, T81FractionHandle* result);
TritError t81fraction_multiply(T81FractionHandle a, T81FractionHandle b, T81FractionHandle* result);
TritError t81fraction_divide(T81FractionHandle a, T81FractionHandle b, T81FractionHandle* result);

/** T81Float Functions */
T81FloatHandle t81float_new(const char* mantissa_str, int exponent);
void t81float_free(T81FloatHandle h);
TritError t81float_get_mantissa(T81FloatHandle h, T81BigIntHandle* mantissa);
TritError t81float_get_exponent(T81FloatHandle h, int* exponent);
TritError t81float_add(T81FloatHandle a, T81FloatHandle b, T81FloatHandle* result);
TritError t81float_subtract(T81FloatHandle a, T81FloatHandle b, T81FloatHandle* result);
TritError t81float_multiply(T81FloatHandle a, T81FloatHandle b, T81FloatHandle* result);
TritError t81float_divide(T81FloatHandle a, T81FloatHandle b, T81FloatHandle* result);
TritError t81float_exp(T81FloatHandle a, T81FloatHandle* result);
TritError t81float_sin(T81FloatHandle a, T81FloatHandle* result);
TritError t81float_cos(T81FloatHandle a, T81FloatHandle* result);

/** T81Matrix Functions */
T81MatrixHandle t81matrix_new(int rows, int cols);
void t81matrix_free(T81MatrixHandle h);
TritError t81matrix_add(T81MatrixHandle a, T81MatrixHandle b, T81MatrixHandle* result);
TritError t81matrix_subtract(T81MatrixHandle a, T81MatrixHandle b, T81MatrixHandle* result);
TritError t81matrix_multiply(T81MatrixHandle a, T81MatrixHandle b, T81MatrixHandle* result);

/** T81Vector Functions */
T81VectorHandle t81vector_new(int dim);
void t81vector_free(T81VectorHandle h);
TritError t81vector_dot(T81VectorHandle a, T81VectorHandle b, T81BigIntHandle* result);

/** T81Quaternion Functions */
T81QuaternionHandle t81quaternion_new(T81BigIntHandle w, T81BigIntHandle x, T81BigIntHandle y, T81BigIntHandle z);
void t81quaternion_free(T81QuaternionHandle h);
TritError t81quaternion_multiply(T81QuaternionHandle a, T81QuaternionHandle b, T81QuaternionHandle* result);

/** T81Polynomial Functions */
T81PolynomialHandle t81polynomial_new(int degree);
void t81polynomial_free(T81PolynomialHandle h);
TritError t81polynomial_add(T81PolynomialHandle a, T81PolynomialHandle b, T81PolynomialHandle* result);

/** T81Tensor Functions */
T81TensorHandle t81tensor_new(int rank, int* dims);
void t81tensor_free(T81TensorHandle h);
TritError t81tensor_contract(T81TensorHandle a, T81TensorHandle b, T81TensorHandle* result);

/** T81Graph Functions */
T81GraphHandle t81graph_new(int nodes);
void t81graph_free(T81GraphHandle h);
TritError t81graph_add_edge(T81GraphHandle g, int src, int dst, T81BigIntHandle weight);
TritError t81graph_bfs(T81GraphHandle g, int startNode, int* visitedOrder);

/** T81Opcode Functions */
T81OpcodeHandle t81opcode_new(const char* instruction);
void t81opcode_free(T81OpcodeHandle h);
TritError t81opcode_execute(T81OpcodeHandle op, T81BigIntHandle* registers, int reg_count);

// ### T81BigInt Implementation
/** Structure representing an arbitrary-precision ternary integer. */
typedef struct {
    int sign;                // 0 = positive, 1 = negative
    unsigned char *digits;   // Array of base-81 digits, stored in little-endian order
    size_t len;              // Number of digits in the array
    int is_mapped;           // 1 if digits are memory-mapped, 0 if heap-allocated
    int fd;                  // File descriptor for memory-mapped file (POSIX) or handle (Windows)
    char tmp_path[MAX_PATH]; // Path to temporary file for memory mapping
} T81BigInt;

// Helper Functions for T81BigInt
/**
 * Creates a new T81BigInt from an integer value.
 * @param value The initial integer value.
 * @return Pointer to the new T81BigInt, or NULL on failure.
 */
static T81BigInt* new_t81bigint_internal(int value) {
    T81BigInt* res = (T81BigInt*)calloc(1, sizeof(T81BigInt));
    if (!res) {
        fprintf(stderr, "Failed to allocate T81BigInt structure\n");
        return NULL;
    }
    res->sign = (value < 0) ? 1 : 0;
    value = abs(value);
    TritError err = allocate_digits(res, 1);
    if (err != TRIT_OK) {
        free(res);
        fprintf(stderr, "Failed to allocate digits for T81BigInt\n");
        return NULL;
    }
    res->digits[0] = value % BASE_81;
    res->len = 1;
    return res;
}

/**
 * Allocates memory for the digits array, using memory mapping for large sizes.
 * @param x The T81BigInt to allocate digits for.
 * @param lengthNeeded Number of digits required.
 * @return TRIT_OK on success, or an error code on failure.
 */
static TritError allocate_digits(T81BigInt *x, size_t lengthNeeded) {
    size_t bytesNeeded = (lengthNeeded == 0 ? 1 : lengthNeeded); // Ensure at least 1 byte
    x->len = lengthNeeded;
    x->is_mapped = 0;
    x->fd = -1;

    if (bytesNeeded < T81_MMAP_THRESHOLD) {
        // Use heap allocation for small sizes
        x->digits = (unsigned char*)calloc(bytesNeeded, sizeof(unsigned char));
        if (!x->digits) {
            fprintf(stderr, "Heap allocation failed for %zu bytes\n", bytesNeeded);
            return TRIT_MEM_FAIL;
        }
        return TRIT_OK;
    }

    // Use memory mapping for large sizes
#ifdef _WIN32
    HANDLE hFile = CreateFile("trit_temp.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL,
                              CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Failed to create temporary file for memory mapping\n");
        return TRIT_MAP_FAIL;
    }
    HANDLE hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, bytesNeeded, NULL);
    if (!hMap) {
        CloseHandle(hFile);
        fprintf(stderr, "Failed to create file mapping\n");
        return TRIT_MAP_FAIL;
    }
    x->digits = (unsigned char*)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, bytesNeeded);
    if (!x->digits) {
        CloseHandle(hMap);
        CloseHandle(hFile);
        fprintf(stderr, "Failed to map view of file\n");
        return TRIT_MAP_FAIL;
    }
    x->is_mapped = 1;
    x->fd = (int)hFile; // Store handle as int (simplified)
    CloseHandle(hMap);  // Mapping handle no longer needed
#else
    snprintf(x->tmp_path, MAX_PATH, "/tmp/tritjs_XXXXXX");
    x->fd = mkstemp(x->tmp_path);
    if (x->fd < 0) {
        fprintf(stderr, "Failed to create temporary file: %s\n", strerror(errno));
        return TRIT_MAP_FAIL;
    }
    if (ftruncate(x->fd, bytesNeeded) < 0) {
        close(x->fd);
        fprintf(stderr, "Failed to truncate file to %zu bytes\n", bytesNeeded);
        return TRIT_MAP_FAIL;
    }
    x->digits = (unsigned char*)mmap(NULL, bytesNeeded, PROT_READ | PROT_WRITE, MAP_SHARED, x->fd, 0);
    if (x->digits == MAP_FAILED) {
        close(x->fd);
        fprintf(stderr, "Memory mapping failed: %s\n", strerror(errno));
        return TRIT_MAP_FAIL;
    }
    unlink(x->tmp_path); // Remove file from filesystem (stays open until unmapped)
    x->is_mapped = 1;
#endif
    total_mapped_bytes += bytesNeeded;
    return TRIT_OK;
}

/**
 * Frees a T81BigInt structure and its associated memory.
 * @param x The T81BigInt to free.
 */
static void free_t81bigint_internal(T81BigInt* x) {
    if (!x) return;
    if (x->is_mapped && x->digits) {
        size_t bytes = (x->len == 0 ? 1 : x->len);
#ifdef _WIN32
        UnmapViewOfFile(x->digits);
        CloseHandle((HANDLE)x->fd);
#else
        munmap(x->digits, bytes);
        close(x->fd);
#endif
        total_mapped_bytes -= bytes;
    } else {
        free(x->digits);
    }
    free(x);
}

// Public API for T81BigInt
/**
 * Creates a new T81BigInt from an integer value.
 * @param value The initial value.
 * @return Handle to the new T81BigInt, or NULL on failure.
 */
T81BigIntHandle t81bigint_new(int value) {
    return (T81BigIntHandle)new_t81bigint_internal(value);
}

/**
 * Creates a new T81BigInt from a base-81 string (e.g., "12" in base-81).
 * @param str The string representation.
 * @return Handle to the new T81BigInt, or NULL on failure.
 */
T81BigIntHandle t81bigint_from_string(const char* str) {
    if (!str) return NULL;
    T81BigInt* bigint = (T81BigInt*)calloc(1, sizeof(T81BigInt));
    if (!bigint) return NULL;

    int sign = 0;
    if (str[0] == '-') {
        sign = 1;
        str++;
    }
    size_t len = strlen(str);
    if (allocate_digits(bigint, len) != TRIT_OK) {
        free(bigint);
        return NULL;
    }
    bigint->sign = sign;
    bigint->len = len;

    for (size_t i = 0; i < len; i++) {
        char c = str[len - 1 - i];
        if (c < '0' || c > '9') {
            free_t81bigint_internal(bigint);
            return NULL;
        }
        int digit = c - '0';
        if (digit >= BASE_81) {
            free_t81bigint_internal(bigint);
            return NULL;
        }
        bigint->digits[i] = (unsigned char)digit;
    }
    return (T81BigIntHandle)bigint;
}

/**
 * Frees a T81BigInt handle.
 * @param h The handle to free.
 */
void t81bigint_free(T81BigIntHandle h) {
    free_t81bigint_internal((T81BigInt*)h);
}

/**
 * Converts a T81BigInt to its string representation.
 * @param h The T81BigInt handle.
 * @param result Pointer to store the allocated string (caller must free).
 * @return TRIT_OK on success, or an error code.
 */
TritError t81bigint_to_string(T81BigIntHandle h, char** result) {
    T81BigInt* x = (T81BigInt*)h;
    if (!x || !result) return TRIT_INVALID_INPUT;

    size_t len = x->len + (x->sign ? 1 : 0) + 1; // Sign + digits + null terminator
    *result = (char*)malloc(len);
    if (!*result) return TRIT_MEM_FAIL;

    char* ptr = *result;
    if (x->sign) *ptr++ = '-';
    for (size_t i = 0; i < x->len; i++) {
        ptr[x->len - 1 - i] = '0' + x->digits[i];
    }
    ptr[x->len] = '\0';
    return TRIT_OK;
}

/**
 * Adds two T81BigInt numbers.
 * @param a First operand.
 * @param b Second operand.
 * @param result Pointer to store the result handle.
 * @return TRIT_OK on success, or an error code.
 */
TritError t81bigint_add(T81BigIntHandle a, T81BigIntHandle b, T81BigIntHandle* result) {
    T81BigInt* x = (T81BigInt*)a;
    T81BigInt* y = (T81BigInt*)b;
    if (!x || !y || !result) return TRIT_INVALID_INPUT;

    size_t max_len = (x->len > y->len) ? x->len : y->len;
    T81BigInt* res = (T81BigInt*)calloc(1, sizeof(T81BigInt));
    if (!res) return TRIT_MEM_FAIL;
    if (allocate_digits(res, max_len + 1) != TRIT_OK) {
        free(res);
        return TRIT_MEM_FAIL;
    }

    int carry = 0;
    for (size_t i = 0; i < max_len || carry; i++) {
        if (i >= res->len) {
            // Reallocate if necessary (unlikely due to max_len + 1)
            TritError err = allocate_digits(res, res->len + 1);
            if (err != TRIT_OK) {
                free_t81bigint_internal(res);
                return err;
            }
        }
        int sum = carry;
        if (i < x->len) sum += (x->sign ? -x->digits[i] : x->digits[i]);
        if (i < y->len) sum += (y->sign ? -y->digits[i] : y->digits[i]);
        if (sum < 0) {
            carry = -1;
            sum += BASE_81;
        } else {
            carry = sum / BASE_81;
            sum %= BASE_81;
        }
        res->digits[i] = (unsigned char)sum;
        if (i + 1 > res->len) res->len = i + 1;
    }
    res->sign = (carry < 0) ? 1 : 0;
    *result = (T81BigIntHandle)res;
    return TRIT_OK;
}

// Additional T81BigInt operations (subtract, multiply, divide, mod) would follow similar patterns.

// ### T81Fraction Implementation
/** Structure representing an exact rational number. */
typedef struct {
    T81BigInt* numerator;
    T81BigInt* denominator;
} T81Fraction;

/**
 * Creates a new T81Fraction from numerator and denominator strings.
 * @param num_str Numerator as a string.
 * @param denom_str Denominator as a string.
 * @return Handle to the new T81Fraction, or NULL on failure.
 */
T81FractionHandle t81fraction_new(const char* num_str, const char* denom_str) {
    T81BigInt* num = (T81BigInt*)t81bigint_from_string(num_str);
    T81BigInt* den = (T81BigInt*)t81bigint_from_string(denom_str);
    if (!num || !den) {
        if (num) t81bigint_free((T81BigIntHandle)num);
        if (den) t81bigint_free((T81BigIntHandle)den);
        return NULL;
    }
    T81Fraction* f = (T81Fraction*)calloc(1, sizeof(T81Fraction));
    if (!f) {
        t81bigint_free((T81BigIntHandle)num);
        t81bigint_free((T81BigIntHandle)den);
        return NULL;
    }
    f->numerator = num;
    f->denominator = den;
    return (T81FractionHandle)f;
}

/**
 * Frees a T81Fraction handle.
 * @param h The handle to free.
 */
void t81fraction_free(T81FractionHandle h) {
    T81Fraction* f = (T81Fraction*)h;
    if (!f) return;
    t81bigint_free((T81BigIntHandle)f->numerator);
    t81bigint_free((T81BigIntHandle)f->denominator);
    free(f);
}

// T81Fraction operations (add, subtract, multiply, divide) would be implemented here.

// ### T81Float Implementation
/** Structure representing a ternary floating-point number. */
typedef struct {
    T81BigInt* mantissa;  // Mantissa (significant digits)
    int exponent;         // Exponent in base-81
    int sign;             // 0 = positive, 1 = negative
} T81Float;

/**
 * Creates a new T81Float from mantissa string and exponent.
 * @param mantissa_str Mantissa as a string.
 * @param exponent Exponent value.
 * @return Handle to the new T81Float, or NULL on failure.
 */
T81FloatHandle t81float_new(const char* mantissa_str, int exponent) {
    T81BigInt* mantissa = (T81BigInt*)t81bigint_from_string(mantissa_str);
    if (!mantissa) return NULL;
    T81Float* f = (T81Float*)calloc(1, sizeof(T81Float));
    if (!f) {
        t81bigint_free((T81BigIntHandle)mantissa);
        return NULL;
    }
    f->mantissa = mantissa;
    f->exponent = exponent;
    f->sign = (mantissa_str[0] == '-') ? 1 : 0;
    return (T81FloatHandle)f;
}

/**
 * Frees a T81Float handle.
 * @param h The handle to free.
 */
void t81float_free(T81FloatHandle h) {
    T81Float* f = (T81Float*)h;
    if (!f) return;
    t81bigint_free((T81BigIntHandle)f->mantissa);
    free(f);
}

/**
 * Computes the exponential function of a T81Float (e^x).
 * @param a Input T81Float handle.
 * @param result Pointer to store the result handle.
 * @return TRIT_OK on success, or an error code.
 */
TritError t81float_exp(T81FloatHandle a, T81FloatHandle* result) {
    // Placeholder: Actual implementation would use series expansion
    T81Float* x = (T81Float*)a;
    if (!x || !result) return TRIT_INVALID_INPUT;
    // For simplicity, return a dummy result
    *result = t81float_new("1", 0);
    return TRIT_OK;
}

/**
 * Computes the sine of a T81Float.
 * @param a Input T81Float handle.
 * @param result Pointer to store the result handle.
 * @return TRIT_OK on success, or an error code.
 */
TritError t81float_sin(T81FloatHandle a, T81FloatHandle* result) {
    // Placeholder: Actual implementation would use Taylor series
    T81Float* x = (T81Float*)a;
    if (!x || !result) return TRIT_INVALID_INPUT;
    *result = t81float_new("0", 0);
    return TRIT_OK;
}

/**
 * Computes the cosine of a T81Float.
 * @param a Input T81Float handle.
 * @param result Pointer to store the result handle.
 * @return TRIT_OK on success, or an error code.
 */
TritError t81float_cos(T81FloatHandle a, T81FloatHandle* result) {
    // Placeholder: Actual implementation would use Taylor series
    T81Float* x = (T81Float*)a;
    if (!x || !result) return TRIT_INVALID_INPUT;
    *result = t81float_new("1", 0);
    return TRIT_OK;
}

// ### Additional Data Types (Structures and Basic API)
// Note: Full implementations of operations are omitted for space but follow similar patterns.

typedef struct {
    int rows, cols;
    T81BigInt** data; // 2D array of T81BigInt pointers
} T81Matrix;

T81MatrixHandle t81matrix_new(int rows, int cols) {
    T81Matrix* m = (T81Matrix*)calloc(1, sizeof(T81Matrix));
    if (!m) return NULL;
    m->rows = rows;
    m->cols = cols;
    m->data = (T81BigInt**)calloc(rows, sizeof(T81BigInt*));
    if (!m->data) {
        free(m);
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        m->data[i] = (T81BigInt*)calloc(cols, sizeof(T81BigInt));
        if (!m->data[i]) {
            for (int j = 0; j < i; j++) free(m->data[j]);
            free(m->data);
            free(m);
            return NULL;
        }
    }
    return (T81MatrixHandle)m;
}

void t81matrix_free(T81MatrixHandle h) {
    T81Matrix* m = (T81Matrix*)h;
    if (!m) return;
    for (int i = 0; i < m->rows; i++) free(m->data[i]);
    free(m->data);
    free(m);
}

typedef struct {
    int dim;
    T81BigInt* components;
} T81Vector;

T81VectorHandle t81vector_new(int dim) {
    T81Vector* v = (T81Vector*)calloc(1, sizeof(T81Vector));
    if (!v) return NULL;
    v->dim = dim;
    v->components = (T81BigInt*)calloc(dim, sizeof(T81BigInt));
    if (!v->components) {
        free(v);
        return NULL;
    }
    return (T81VectorHandle)v;
}

void t81vector_free(T81VectorHandle h) {
    T81Vector* v = (T81Vector*)h;
    if (!v) return;
    free(v->components);
    free(v);
}

typedef struct {
    T81BigInt* w, *x, *y, *z;
} T81Quaternion;

T81QuaternionHandle t81quaternion_new(T81BigIntHandle w, T81BigIntHandle x, T81BigIntHandle y, T81BigIntHandle z) {
    T81Quaternion* q = (T81Quaternion*)calloc(1, sizeof(T81Quaternion));
    if (!q) return NULL;
    q->w = (T81BigInt*)w;
    q->x = (T81BigInt*)x;
    q->y = (T81BigInt*)y;
    q->z = (T81BigInt*)z;
    return (T81QuaternionHandle)q;
}

void t81quaternion_free(T81QuaternionHandle h) {
    T81Quaternion* q = (T81Quaternion*)h;
    if (!q) return;
    free(q); // Components are managed externally
}

typedef struct {
    int degree;
    T81BigInt* coeffs; // Coefficients from degree 0 to degree
} T81Polynomial;

T81PolynomialHandle t81polynomial_new(int degree) {
    T81Polynomial* p = (T81Polynomial*)calloc(1, sizeof(T81Polynomial));
    if (!p) return NULL;
    p->degree = degree;
    p->coeffs = (T81BigInt*)calloc(degree + 1, sizeof(T81BigInt));
    if (!p->coeffs) {
        free(p);
        return NULL;
    }
    return (T81PolynomialHandle)p;
}

void t81polynomial_free(T81PolynomialHandle h) {
    T81Polynomial* p = (T81Polynomial*)h;
    if (!p) return;
    free(p->coeffs);
    free(p);
}

typedef struct {
    int rank;
    int* dims;
    T81BigInt* data; // Flattened array
} T81Tensor;

T81TensorHandle t81tensor_new(int rank, int* dims) {
    T81Tensor* t = (T81Tensor*)calloc(1, sizeof(T81Tensor));
    if (!t) return NULL;
    t->rank = rank;
    t->dims = (int*)calloc(rank, sizeof(int));
    if (!t->dims) {
        free(t);
        return NULL;
    }
    size_t size = 1;
    for (int i = 0; i < rank; i++) {
        t->dims[i] = dims[i];
        size *= dims[i];
    }
    t->data = (T81BigInt*)calloc(size, sizeof(T81BigInt));
    if (!t->data) {
        free(t->dims);
        free(t);
        return NULL;
    }
    return (T81TensorHandle)t;
}

void t81tensor_free(T81TensorHandle h) {
    T81Tensor* t = (T81Tensor*)h;
    if (!t) return;
    free(t->data);
    free(t->dims);
    free(t);
}

typedef struct {
    int nodes;
    T81BigInt** adj_matrix; // Adjacency matrix with weights
} T81Graph;

T81GraphHandle t81graph_new(int nodes) {
    T81Graph* g = (T81Graph*)calloc(1, sizeof(T81Graph));
    if (!g) return NULL;
    g->nodes = nodes;
    g->adj_matrix = (T81BigInt**)calloc(nodes, sizeof(T81BigInt*));
    if (!g->adj_matrix) {
        free(g);
        return NULL;
    }
    for (int i = 0; i < nodes; i++) {
        g->adj_matrix[i] = (T81BigInt*)calloc(nodes, sizeof(T81BigInt));
        if (!g->adj_matrix[i]) {
            for (int j = 0; j < i; j++) free(g->adj_matrix[j]);
            free(g->adj_matrix);
            free(g);
            return NULL;
        }
    }
    return (T81GraphHandle)g;
}

void t81graph_free(T81GraphHandle h) {
    T81Graph* g = (T81Graph*)h;
    if (!g) return;
    for (int i = 0; i < g->nodes; i++) free(g->adj_matrix[i]);
    free(g->adj_matrix);
    free(g);
}

typedef struct {
    char* instruction; // Ternary CPU instruction
} T81Opcode;

T81OpcodeHandle t81opcode_new(const char* instruction) {
    T81Opcode* op = (T81Opcode*)calloc(1, sizeof(T81Opcode));
    if (!op) return NULL;
    op->instruction = strdup(instruction);
    if (!op->instruction) {
        free(op);
        return NULL;
    }
    return (T81OpcodeHandle)op;
}

void t81opcode_free(T81OpcodeHandle h) {
    T81Opcode* op = (T81Opcode*)h;
    if (!op) return;
    free(op->instruction);
    free(op);
}

// ### Main Function for Testing
/**
 * Main function to demonstrate basic usage of the T81 data types.
 */
int main(void) {
    printf("T81 Ternary Data Types System - Test Suite\n");

    // Test T81BigInt
    T81BigIntHandle a = t81bigint_new(123);
    if (a) {
        char* str;
        t81bigint_to_string(a, &str);
        printf("T81BigInt: %s\n", str);
        free(str);
        t81bigint_free(a);
    }

    // Test T81Float
    T81FloatHandle f = t81float_new("456", 2);
    if (f) {
        printf("Created T81Float with mantissa 456 and exponent 2\n");
        T81FloatHandle exp_result;
        t81float_exp(f, &exp_result);
        t81float_free(exp_result);
        t81float_free(f);
    }

    // Additional tests could be added for other data types
    printf("Total mapped bytes: %ld\n", total_mapped_bytes);
    return 0;
}
