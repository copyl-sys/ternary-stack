# 🌀 **HanoiVM Manifesto — Recursive Symbolic Virtual Machine**

This document declares the philosophy, structure, and intent behind **HanoiVM**: a recursive ternary virtual machine driven by symbolic logic, AI introspection, and tiered execution across the `T81`, `T243`, and `T729` logic levels.

---

## 📜 Philosophy

**HanoiVM** is not just a virtual machine.  
It is a computational model built around recursion, symbolism, and AI co-development.

It treats:
- **Recursion as architecture**, not just control flow.
- **Symbolic data as active instructions**, not passive memory.
- **Ternary logic as expressive reasoning**, not numeric encoding.

These principles result in a new kind of runtime:  
One where execution **adapts** based on entropy, intent, and structure.

---

## 🔺 Tiered Symbolic Architecture

HanoiVM operates across three recursive logic levels:

| Tier   | Description                                        |
|--------|----------------------------------------------------|
| `T81`  | Base-81 compact operands (`uint81_t`)              |
| `T243` | Symbolic FSM, BigInt, and state-machine logic      |
| `T729` | Tensor AI macros, symbolic recursion, and FFT ops  |

Each tier supports **promotion/demotion** based on recursion depth and Axion AI entropy feedback.

---

## 🤖 AI Integration

At the core of HanoiVM is **Axion AI**, responsible for:

- NLP-driven optimization (`rollback`, `optimize`, `snapshot`)
- Symbolic macro execution and entropy path selection
- Autonomous tier promotion via `τ[27]` (reserved ternary register)

Axion operates **in-line** with VM execution, ensuring every symbolic operation benefits from intelligent refinement.

---

## 🧠 T81Lang: The Compiler Stack

**T81Lang** is the high-level language for HanoiVM:

- Literate syntax for recursive symbolic programming (`.t81`)
- Complete pipeline: Lexer → Parser → IR → `.hvm` bytecode
- `t81lang_compiler.cweb` orchestrates compilation and Axion-aware optimization
- Compatible with GPU dispatch, entropy tracing, and recursion visualizers

---

## 💾 GPU + FFI Synergy

HanoiVM supports:

- **GPU symbolic tensor execution** via:
  - `cuda_handle_request.cu` (NVIDIA)
  - `gaia_handle_request.cweb` (AMD ROCm)
- **Cross-language FFI**:
  - `libhanoivm_ffi.so` exposes VM state and execution primitives
  - Bindings for Rust, Python, and C++ underway

This enables external AI/ML pipelines, REPLs, and language tooling to embed the VM.

---

## 🌌 Looking Glass + Recursion Visualization

`FrameSceneBuilder.cweb` + `recursive_exporter.cweb` allow:

- Full recursion trace exports in `.t81viz` JSON format
- Visual rendering via jMonkeyEngine and entropy overlays
- Symbolic state tracking and Axion telemetry mapping

A fully introspectable symbolic system — as beautiful as it is recursive.

---

## ⚙️ Modular `.cweb` Literate Infrastructure

All HanoiVM source files are written in **literate `.cweb` format**.

This provides:
- Full documentation next to code
- Extractable `.h` headers and `.c` source via `cweave`/`ctangle`
- Maintainability, readability, and introspectability at scale

---

## 🗂️ File Index (Condensed)

| File                          | Description                                           |
|-------------------------------|-------------------------------------------------------|
| `README.md`                  | Project overview and usage guide                      |
| `LICENSE`                    | MIT License                                           |
| `MANIFESTO.md`               | Philosophy and modular file map (this document)       |
| `ROADMAP.md`                 | Development phases and vision milestones              |
| `STATUS.md`                  | Subsystem health and completion percentages           |
| `CHANGELOG.md`               | Release history and features                          |
| `build-all.cweb`             | Unified build script                                  |
| `hanoivm_vm.cweb`            | Execution core, recursion loop, AI integration        |
| `t81_stack.cweb`             | Base-81 operand stack operations                      |
| `libt81.cweb`                | T81BigInt, Float, Fraction, Tensor, Graph, etc.       |
| `libt243.cweb`               | FSM / BigInt operations (T243)                        |
| `libt729.cweb`               | Symbolic tensor engine (T729)                         |
| `t81_patterns.cweb`          | Symbolic pattern recognition macros                   |
| `advanced_ops_ext.cweb`      | FFT, intent dispatch, entropy-weighted macros         |
| `recursive_tier_execution.cweb` | Tier promotion controller                         |
| `axion-ai.cweb`              | Kernel AI (rollback, optimization, NLP)               |
| `axion-gaia-interface.cweb`  | GPU symbolic bridge (GAIA backend)                    |
| `cuda_handle_request.cu`     | CUDA GPU execution backend                            |
| `hanoivm_ffi.cweb`           | FFI ABI and symbolic external interface               |
| `FrameSceneBuilder.cweb`     | 3D recursion visualizer module                        |
| `t81lang_compiler.cweb`      | Compiler frontend pipeline for `.t81` → `.hvm`        |
| `tisc_backend.cweb`          | IR emitter for `.tisc` → symbolic `.hvm`              |
| `gaia_graph_pipeline.cweb`   | GPU symbolic graph executor                           |
| `logviewer.cweb`             | Axion telemetry and symbolic log tracker              |
| `disassembler.cweb`          | Symbolic `.hvm` decoder and introspection engine      |

_And many more. Refer to `README.md` for a full list and module-level summaries._

---

## ⚠️ Use Ethically

HanoiVM explores symbolic execution, AI hooks, and entropy pathways. These capabilities are **powerful**—and like all power, demand responsibility.

- Do not use HanoiVM for coercive surveillance or unethical AI.
- Be transparent in how recursion, optimization, or symbolic reasoning are applied.
- Help improve the tools, clarify the ideas, and extend them into open, collaborative systems.

---

## 🧠 Final Words

HanoiVM exists to **rethink** what a virtual machine can be:

- Recursive, not linear  
- Symbolic, not opaque  
- Intelligent, not static  
- Literate, not undocumented

It is a platform to **build the future of computation** —  
in full view of the past,  
with both machine and mind as collaborators.

> _"In recursion, we do not loop — we unfold."_
