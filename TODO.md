# ✅ TODO — Copyleft Ternary Stack (Q2 2025)

This document tracks active development items across the unified AI-native ternary computing stack.

---

## 🔧 Core Compiler & Language

- [x] Build `t81_compile.py` to parse `.t81` → `.tisc`, `.ast.json`, `.entropy.json`, `.cweb`
- [x] Add CLI flags and file output control
- [x] Integrate entropy tracking and symbolic tagging into AST
- [ ] Add support for function arguments and multiple functions
- [ ] Extend parser with `if`, `loop`, and `match` support
- [ ] Implement type-checking engine for `T81Lang`
- [ ] Split compiler logic into modules (`lexer.py`, `parser.py`, etc.)
- [ ] JIT backend stub for runtime execution inside HanoiVM

---

## 🧠 Axion AI

- [x] Enable entropy trace logging via `.cweb` `@symbols`
- [ ] Sync `.entropy.json` with Axion symbolic model
- [ ] Build Axion-driven `.cweb` validator + log viewer CLI
- [ ] Sandbox rollback state comparison
- [ ] Auto-refine build flags based on entropy profile

---

## 🖼️ Project Looking Glass (Java 3D)

- [ ] Ingest `.entropy.json` for real-time visual feedback
- [ ] Render ternary symbol maps from `.cweb` `@symbols`
- [ ] Add timeline mode for recursive tracing

---

## 🧪 Testing

- [x] Create `examples/test.t81` for regression testing
- [x] Validate `.cweb` output structure
- [x] Confirm symbolic metadata appears in entropy logs
- [ ] Add CI tests for `t81_compile.py`
- [ ] Integration test: `test.t81` → `.cweb` → Axion build
- [ ] Regression diff tool for `.tisc` and `.ast.json`

---

## 📚 Documentation

- [x] Update `t81lang-spec.md` for compiler + AST + metadata
- [x] Update `cweb-format.md` with `@symbols`, entropy metadata
- [x] Update `test-strategy.md` for new test paths and integration
- [x] Update top-level `README.md` to reflect active compiler
- [x] Add `TODO.md` to track live efforts

---

## 🔮 Future (Q3+)

- [ ] LLVM backend targeting TISC
- [ ] Axion HiveNet for shared AI optimization logs
- [ ] Disassembler UI for entropy-aware `.tisc` review
- [ ] T81Lang to support `macro` and `symbolic` execution blocks
- [ ] Package auto-splitting and AI chunking via Axion

---

_Last updated: March 2025_  
_Maintained by: `copyleft systems`_  
_Mode: `./night_shift.sh -sync -copyleftsystems`_
