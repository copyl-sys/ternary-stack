#ifndef TTYPES_H
#define TTYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Ternary Values
typedef enum {
    TERNARY_FALSE = '0',
    TERNARY_TRUE = '1',
    TERNARY_UNKNOWN = 'T'
} TernaryValue;

/// Ternary Expression Types
typedef enum {
    VAR, CONST, MUL, ADD, NOT
} ExprType;

/// Ternary Expression Structure
typedef struct TernaryExpr {
    ExprType type;
    char value;  // For constants & variables (e.g., 'x', '1', 'T')
    struct TernaryExpr* left;
    struct TernaryExpr* right;
} TernaryExpr;

/// Creates a new constant or variable expression
TernaryExpr* new_expr(ExprType type, char value, TernaryExpr* left, TernaryExpr* right);

/// Parses a ternary algebraic expression
TernaryExpr* parse_ternary_expr(const char* expr);

/// Symbolic Differentiation
TernaryExpr* differentiate(TernaryExpr* expr, char variable);

/// Evaluates a ternary expression with variable substitutions
char evaluate(TernaryExpr* expr, const char* vars, const char* vals);

/// Ternary Logic Operations (Kleene's strong logic)
char ternary_and(char x, char y);
char ternary_or(char x, char y);
char ternary_not(char x);

/// Utility Functions
void free_expr(TernaryExpr* expr);
void print_expr(TernaryExpr* expr);

#endif // TTYPES_H
