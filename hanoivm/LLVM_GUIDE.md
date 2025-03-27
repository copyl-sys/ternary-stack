# 🧠 LLVM_GUIDE.md — Axion + T81Lang + LLVM Backend Integration

This document provides a deep technical guide for integrating the HanoiVM + T81Lang + TISC symbolic pipeline with the LLVM backend.

---

## ✅ Target Triples

- Custom registered target: `t81-unknown-none`
- Defines ternary architecture layer (virtualized)

```cpp
target triple = "t81-unknown-none"
```

---

## 🔣 Custom Data Types

### `i81`
- Represents base-81, ternary integer
- Maps to `uint81_t` in HanoiVM

```llvm
%i = type i81
```

### `v81`
- 81-element symbolic vector for T729 logic

---

## 🔧 DataLayout String
```llvm
dataLayout = "e-p:81:81-i81:81:81-n81:81-S81"
```
- Ensures proper alignment, size, and symbol width for `i81`

---

## 🧱 ISel + Backend Passes

### Instruction Selection
- Files:
  - `T81ISelLowering.cpp`
  - `T81ISelDAGToDAG.cpp`

### Machine Lowering
- Files:
  - `T81MCInstLower.cpp`
  - `T81AsmPrinter.cpp`

---

## 🧩 Backend Pipeline
```bash
clang -target t81-unknown-none -S input.t81.c -o output.ll
llc -march=t81 -filetype=obj output.ll -o output.o
hvm_linker output.o -o program.hvm
```

---

## 🧠 TISC Backend
LLVM IR → TISC → `.hvm`
- Intermediate symbolic ops passed through `tisc_ir.cweb`
- Lowered to `.hvm` bytecode via `tisc_backend.cweb`

---

## 🧪 Testing & Validation
- Uses `lit` + `FileCheck`
- Tests for `i81` patterns, symbolic macros, and recursion expansion

---

## 🔮 Future Goals
- SIMD support for vectorized ternary ops (`v81`)
- Graph IR for Axion optimization introspection
- Symbolic IR→TISC inference engine (AI-assisted)

---

> Recursion in LLVM is not just a call — it's a pattern in symbolic space.
