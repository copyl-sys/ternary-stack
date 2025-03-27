# 🗺️ Copyleft Systems — Project Roadmap

This roadmap outlines the current status, direction, and integration plan for the **Copyleft Ternary Stack**, encompassing AI-native computing, recursive ternary logic, secure introspection, and a self-evolving OS.

---

## ✅ Current Status Overview

| Component               | Status       | Description |
|------------------------|--------------|-------------|
| `hanoivm/`             | ✅ Stable Base | T81/T243/T729 ternary VM with Axion hooks and symbolic recursion support |
| `axion-ai/`            | ⏳ In Progress | AI-powered kernel module, entropy tracking, rollback, `.cweb` integration |
| `t81lang/`             | 🧠 Planned     | High-level ternary language (compiler, JIT, SIMD-aware standard library) |
| `tisc-assembler/`      | ⏳ Partial     | Opcode translation and disassembly for TISC; symbolic operand decoding |
| `project-lookingglass/`| 🧠 Conceptual  | Java 3D-based AI visualizer for ternary states, entropy feedback |
| `alexis-linux/`        | ⏳ In Progress | AI-native OS base with Axion, NeuraDE, and kernel-level intelligence |
| `docs/`                | ✅ Scaffolding | High-level system architecture, .cweb specs, and conceptual diagrams underway |

---

## 🔁 Short-Term Goals (Q2 2025)

- [ ] Finalize `docs/architecture.md` (full system interlink overview)
- [ ] Define `.cweb` spec and generate `cweb-parser` tool
- [ ] Refactor `t81lang/` into compiler + VM backend
- [ ] Enable JSON tracing in `disassembler.cweb`
- [ ] Implement GPU backend: `cuda_handle_request.cu`
- [ ] Add `.gitignore` and `LICENSE` to all modules

---

## 🚧 Mid-Term Goals (Q3–Q4 2025)

- [ ] Build `T81Lang` parser and AST structure
- [ ] Link `Axion` telemetry with `Looking Glass` renderer
- [ ] Implement `.cweb` auto-splitting for >50MB packages
- [ ] Develop `Axion Log Viewer` with searchable filters
- [ ] Create test suites under `tests/` for all core modules
- [ ] Build a `make`/`build.sh` system that compiles HanoiVM stack end-to-end

---

## 🚀 Long-Term Vision (2026+)

- [ ] LLVM backend for `T81Lang` → `TISC`
- [ ] Full ternary hardware emulation → FPGA → M.2 card
- [ ] Axion AI clustering and hive optimization modes
- [ ] Metadata blockchain for `.cweb` package integrity
- [ ] Live rollback engine using entropy models and session tracing
- [ ] Secure sandboxed AI shell (`AxionShell`) with language introspection

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

