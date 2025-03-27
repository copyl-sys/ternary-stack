# 🗺️ Copyleft Systems — Project Roadmap

This roadmap outlines the current status, direction, and integration plan for the **Copyleft Ternary Stack**, encompassing AI-native computing, recursive ternary logic, secure entropy tracing, GPU acceleration, and an autonomous AI runtime.

---

## ✅ Current Status Overview

| Component               | Status       | Description |
|------------------------|--------------|-------------|
| `hanoivm/`             | ✅ Stable Base | T81/T243/T729 ternary VM with Axion hooks and symbolic recursion support |
| `axion-ai/`            | ⏳ In Progress | AI-powered kernel module, entropy tracking, rollback, `.cweb` integration |
| `t81lang/`             | ✅ Compiler Scaffolding | Lexer, data type system, and symbolic logic already defined in documentation and PDFs; partial backend and AST mapping underway |
| `tisc-assembler/`      | ⏳ Partial     | Opcode translation and disassembly for TISC; symbolic operand decoding |
| `project-lookingglass/`| 🧠 Conceptual  | Java 3D-based AI visualizer for ternary states, entropy feedback |
| `alexis-linux/`        | ⏳ In Progress | AI-native OS base with Axion, NeuraDE, and kernel-level intelligence |
| `docs/`                | ✅ Complete    | Full architectural specifications for every major component + formalized PDF documents |

---

## 🔁 Short-Term Goals (Q2 2025)

- [x] Finalize `docs/architecture.md` (full system interlink overview)
- [x] Define `.cweb` spec and generate `cweb-format.md`
- [x] Generate `entropy-model.md`, `symbolic-logic.md`, `lookingglass-schema.md`
- [x] Document build strategy and test plan
- [x] Formalize T81Lang design and operational behavior (`T81Lang.pdf`, `TRRNARY - T81DataTypes.pdf`, etc.)
- [ ] Implement Axion `.cweb` parser CLI tool
- [ ] Expand `tests/` with symbolic execution and entropy trace validation

---

## 🚧 Mid-Term Goals (Q3–Q4 2025)

- [ ] Finalize `T81Lang` parser and symbolic compiler frontend
- [ ] Implement entropy-aware `t81lang → TISC` backend
- [ ] Connect `Axion` logs with `Looking Glass` renderer (live IPC or JSON replay)
- [ ] Auto-generate `.cweb` metadata from logs + AI inferences
- [ ] Create CLI tool: `axion-split` for modular `.cweb` generation
- [ ] Build CUDA backend `cuda_handle_request.cu`
- [ ] Begin `entropy-visualizer` plugin for Looking Glass

---

## 🚀 Long-Term Vision (2026+)

- [ ] LLVM backend for `T81Lang` → `TISC`
- [ ] Full ternary hardware emulation → FPGA → M.2 accelerator card
- [ ] Axion AI clustering and hive optimization modes
- [ ] Blockchain-based `.cweb` metadata with distributed verification
- [ ] Live rollback engine using entropy models and symbolic state replay
- [ ] Secure sandboxed AxionShell interface for AI-native development

---

## 🧠 Philosophy Snapshot

This system is built to:
- Reclaim full software stack sovereignty
- Treat entropy as a first-class computational element
- Use AI to monitor, optimize, and refine itself
- Establish a new ternary-first architecture

> "This is not just an OS. It is a recursive machine of knowing."

---

Last updated: March 2025
Author: `copyleft systems`
Mode: `./night_shift.sh -sync -copyleftsystems`

