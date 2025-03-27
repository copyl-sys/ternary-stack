# 🗺️ HanoiVM — Project Roadmap | Copyleft Systems

**HanoiVM** is a recursive, AI-augmented ternary virtual machine supporting the execution of symbolic logic across the `T81`, `T243`, and `T729` logic layers. It anchors the **T81Lang**, **Axion AI**, and **Alexis Linux** ecosystems, focusing on symbolic computation, entropy-aware logic, and AI-accelerated programming.

---

## ✅ Phase 0: Bootstrapping

- [x] Repository setup & CI
- [x] Recursive stack framework & opcode dispatch
- [x] Base assembler, disassembler, and interpreter
- [x] `.cweb` literate programming infrastructure

---

## ✅ Phase 1: Core Virtual Machine (T81)

- [x] T81 operand & stack architecture
- [x] Arithmetic & control opcodes implementation (`ADD81`, `CMP3`, `JMP`, etc.)
- [x] Virtual CPU context & recursive promotion logic
- [x] Initial symbolic opcode evaluation (`evaluate_opcode()`)

---

## ✅ Phase 2: Recursive Expansion (T243/T729)

- [x] `T243BigInt` and `T729Tensor` data types & APIs
- [x] Advanced tensor primitives (`reshape`, `transpose`, `contract`)
- [x] FSM and symbolic AI opcode extensions (`OP_T729_INTENT`, `OP_T729_HOLO_FFT`)
- [x] Recursive symbolic operations with entropy integration

---

## ✅ Phase 3: Compiler & Language Toolchain

- [x] Complete `T81Lang` grammar & compiler frontend (Lexer, Parser, Semantic Analyzer)
- [x] Intermediate Representation (IR) generation and `.hvm` emission
- [x] TISC backend with symbolic optimizations
- [x] Standard library (`tisc_stdlib.cweb`) and REPL integration

---

## ✅ Phase 4: Axion AI Integration

- [x] Kernel AI module (`axion-ai.cweb`) with NLP-based optimization & rollback
- [x] Entropy feedback via reserved ternary registers (`τ[27]`)
- [x] Symbolic pattern analysis and feedback (`t81_patterns.cweb`)
- [x] Comprehensive logging & metadata tracking with entropy-based dispatch
- [x] Session-aware entropy hooks in `evaluate_opcode()` and `disassembler.cweb`

---

## ✅ Phase 5: Developer Experience & Tooling

- [x] Robust `.cweb` literate programming model
- [x] Full documentation (`README.md`, `MANIFESTO.md`, `STATUS.md`, etc.)
- [x] Symbolic introspection tools (disassembler, debugger)
- [x] Recursion visualization engine (`FrameSceneBuilder.cweb`)
- [x] Log viewer (`logviewer.cweb`) for telemetry analysis
- [x] Stack-tier promotion visualizer and exporter (JSON integration)

---

## ✅ Phase 6: FFI & Cross-Language Integration

- [x] `hanoivm_ffi.cweb` exposing VM context and symbolic stack to external languages
- [x] Shared library build (`libhanoivm_ffi.so`) for Rust, C++, Python, and CLI bindings
- [x] Unified T81 operand API via FFI (`push`, `pop`, `peek`)
- [x] Event callback system for Axion-AI-compatible event streaming
- [ ] Language-specific binding crates (`hanoivm-py`, `hanoivm-rs`)  
  *Estimated Timeline: Q2 2025*
- [ ] Examples: Rust CLI REPL, Python disassembler frontend, WASM proof-of-concept

---

## 🔄 Phase 7: Advanced Logic & Visualization (In Progress)

- [x] GPU acceleration backends: CUDA (`cuda_handle_request.cu`), ROCm (`gaia_handle_request.cweb`)
- [x] FFT-based symbolic tensor operations (`T729HoloTensor`)
- [x] PulseControl entropy visualization animations
- [x] GPU Graph Pipeline Integration (`gaia_graph_pipeline.cweb`) with conversion functions
- [ ] GPU Graph Execution: `hipGraphLaunch`, `cuGraphExec` pipelines  
- [x] Symbolic AI Graph IR (`T729LogicGraph`)  
- [x] Enhanced Execution Core (`hanoivm_vm.cweb`)  
- [x] Integration of entropy-aware tracing and symbolic AI dispatch in `evaluate_opcode()`
- [ ] Metadata blockchain for immutable Axion logs and audit trails
- [ ] Project Looking Glass:  
  - [ ] Interactive HUD + 3D VM inspection tooling
  - [ ] Real-time optimization and execution timeline
  - [ ] Live Axion telemetry streaming

---

## 🔄 Phase 8: LLVM Integration & Optimization (Active)

- [x] LLVM target registration (`t81-unknown-none`)
- [x] LLVM IR integration & custom data types (`i81`, `v81`, `tensor81`)
- [x] Instruction Selection DAG patterns and backend (`T81AsmPrinter`)
- [x] Basic LLVM pipeline integration
- [ ] Advanced IR → TISC opcode mapping  
  *Prototype IR matcher implemented*
- [ ] Optimization passes: SIMD, loop unrolling, entropy optimization  
- [ ] Full backend/frontend LLVM synergy  
  *Final goal: ternary-aware SSA pipeline with Axion-driven JIT hooks*

---

## 🔄 Phase 9: Packaging, Distribution & Automation

- [x] `.cweb` package architecture with modular literate builds
- [x] Axion-driven modularization for package splitting (`max 50MB`)
- [x] Release bundles (`Release-v0.9-Public-Alpha.zip`)
- [ ] `.cwebpkg` manifests with export profiles for binaries + source
- [ ] GitHub CI/CD pipeline with automated tests and release jobs
- [ ] Live demo hosting + documentation portal

---

## 🔧 Dedicated Testing & Quality Assurance

- [ ] Extensive unit + system test suite
- [ ] Telemetry-based regression testing
- [ ] Symbolic integrity validation across promotion/demotion boundaries
- [ ] AI fuzzing and entropy convergence tests

---

## 👥 Community & Contribution Guidelines

- [ ] Contributor guide & code of conduct
- [ ] Community discussions + support portal
- [ ] Monthly public roadmap sync & changelog digest

---

## 🔒 Security Enhancements

- [ ] Metadata blockchain for Axion log immutability
- [ ] Secure sandboxing for VM guest code
- [ ] Verified `.cweb` build signatures with rollback detection

---

## 🧩 Supported Data Types

HanoiVM currently supports execution and introspection of the following symbolic and AI-accelerated types:

### T81 Tier:
- `T81BigInt`, `T81Float`, `T81Fraction`
- `T81Matrix`, `T81Vector`, `T81Quaternion`
- `T81Polynomial`, `T81Tensor`
- `T81Graph`, `T81Opcode`

### T243 Tier:
- `T243BigInt`, `T243Circuit`, `T243MarkovMatrix`, `T243MorphicTag`

### T729 Tier:
- `T729Tensor`, `T729MindMap`, `T729EntropyBlob`, `T729LogicGraph`

---

## 🔗 Ecosystem Integration

- [Alexis Linux](https://github.com/copyl-sys) — AI-native OS base
- [T81Lang](https://github.com/copyl-sys) — Ternary symbolic programming language
- [Axion AI](https://github.com/copyl-sys) — Kernel optimization & symbolic AI
- [Project Looking Glass](https://github.com/copyl-sys) — 3D symbolic recursion visualizer

---

### 🌀 v0.9 Summary (March 2025)

- ✅ Full symbolic execution stack across T81/T243/T729
- ✅ Axion AI kernel integration with entropy feedback
- ✅ GPU symbolic tensor and AI logic IR support
- ✅ T81Lang compiler, REPL, and TISC backend integration
- ✅ Logging, telemetry, introspection, and debugger tools
- ✅ FFI and cross-language embedding (`libhanoivm_ffi.so`)
- ✅ Modular `.cweb` ecosystem with Axion-driven package handling
- 🔜 Next: LLVM IR ↔ symbolic opcode mapping, Looking Glass visualization layer

---

> 🧠 *"Recursion is not merely structure; it's the soul of ternary logic."*
