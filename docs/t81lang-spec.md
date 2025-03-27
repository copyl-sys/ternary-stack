# 📘 T81Lang Language Specification

`T81Lang` is a high-level, strongly-typed programming language designed for ternary computing environments, especially those using the `HanoiVM` runtime and targeting `TISC` (Ternary Instruction Set Computer) backends. It emphasizes immutability, symbolic logic, entropy-aware computation, and seamless integration with the `.cweb` package system.

---

## 🔤 Syntax Philosophy

T81Lang syntax is inspired by C, Rust, and mathematical notation. It is:
- Ternary-native (base-81 and base-243 types)
- AI-optimizable (clear scopes, symbol references, entropy hints)
- Introspectable (self-describing AST and metadata)
- Symbolically annotated (e.g., `@entropy`, `@tag`)

---

## 🧾 Data Types

### 🔹 Primitive Types
- `T81Int` → Fixed-size base-81 integer (81ⁿ range)
- `T81BigInt` → Arbitrary-precision base-81 integer
- `T81Float` → Ternary-floating point (based on balanced ternary exponent)
- `T81Fraction` → Rational ternary representation (numerator/denominator)

### 🔸 Compound & Symbolic Types
- `Vector<T>` → Ternary SIMD vector type
- `Matrix<T>` → Multi-dimensional tensor/matrix
- `Symbol<T>` → Tagged symbolic operand (used in recursion, entropy tracing)
- `EntropyBlob` → Runtime ternary state capsule (for Axion or AI processing)

---

## 📐 Type Semantics

- All types are **immutable by default** (unless declared `mut`)
- Ternary operations propagate uncertainty via entropy weighting
- Symbolic types may embed debug tags or AI annotations like `@entropy` and `@tag`

---

## 🧠 Language Features

### ✅ Supported (via `t81_compile.py`)
- `let`, `mut`, `fn`, `return`
- Arithmetic expressions (`+`, `-`, `*`, `/`)
- Symbolic metadata annotations:
  - `@entropy(weight)`
  - `@tag("label")`

### 🧬 Planned
- `if`, `else`, `loop`, `match`, `impl`
- `symbolic` blocks for entropy-sensitive execution
- `inline ai` hints for Axion-guided optimizations
- `ternary match` for base-3 control patterns

---

## ⚙️ Execution Model

- **Compiled via**: `t81_compile.py` (see `/t81lang/src/`)
- **Output Artifacts**:
  - `.ast.json` — Full AST of parsed program
  - `.tisc` — TISC instruction stream
  - `.entropy.json` — Entropy log (symbol-level)
  - `.cweb` — AI-annotated package metadata

### 🔄 Compilation Pipeline
```bash
python t81lang/src/t81_compile.py \
    --input t81lang/examples/test.t81 \
    --emit-cweb \
    --out out/
```

---

## 📦 Package & Module System

T81Lang modules are packaged using `.cweb` format, auto-generated if desired.
Each module includes:
- `mod.t81` → Entry point source
- `types/` → Custom or extended types
- `ai/` → Optional Axion optimization hints
- `tests/` → Self-verifying programs

### 🧠 Symbol Metadata in `.cweb`
```json
"@symbols": [
  { "symbol": "⍺", "entropy": 0.82, "tag": "checksum" },
  { "symbol": "β", "entropy": 0.42, "tag": "probe" }
]
```

---

## 🔁 Example
```t81lang
fn main() -> T81Int {
    let ⍺: T81Int = 27t + 54t @entropy(0.82) @tag("checksum");
    let β: Symbol<T81Float> = 9t @entropy(0.42) @tag("probe");
    return ⍺;
}
```

---

## 🛣 Future Directions

- Symbolic compilation for ternary neural networks (TNNs)
- Macro support for recursion expansion
- AI-driven type inference
- Ternary-safe concurrency (`parallel for`, lockless queues)
- Direct AST → LLVM → AxionJIT backend

---

Last updated: March 2025  
Maintained by: `copyleft systems`  
Mode: `./night_shift.sh -sync -copyleftsystems`

