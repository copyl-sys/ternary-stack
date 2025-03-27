# 🌳 TECHTREE.md — **HanoiVM Capability Tree**

This document outlines the **modular technical evolution** of **HanoiVM**, mapping the recursive and symbolic systems as a layered **technology tree**. Each node represents a capability or subsystem that builds on prior features.

Designed for recursive AI-augmented execution and ternary symbolic logic, **HanoiVM**'s tech tree serves both as a roadmap and as documentation of its architecture.

---

## 🧠 Core Logic Engine (Tier: Recursive Runtime)

```
[ Recursive VM Loop (T81) ]
 ├─ Stack Operand Engine (uint81_t)
 ├─ Instruction Decoder + Opcode Map
 ├─ Recursion Depth Monitor (τ-registers)
 ├─ Promotion Triggers: T81 → T243 → T729
 └─ Axion AI Hook Integration (inline)
```

---

## 🔁 Stack & Operand Systems

```
[ T81 Stack API ]
 ├─ push81 / pop81 / peek81
 ├─ push81u / pop81u (unified operand struct)
 ├─ Operand GCD / ABS / MOD / CMP3
 └─ FFI-Safe Conversions (libt81.cweb)

[ T243 FSM Layer ]
 ├─ Symbolic BigInt: T243BigInt
 ├─ FSM State Logic + Entropy Tags
 └─ AI Macro Extension: OP_T243_ADD, OP_T243_MUL

[ T729 Tensor Layer ]
 ├─ Tensor Creation: rank, shape, data
 ├─ Symbolic Ops: DOT, TRANSPOSE, CONTRACT
 ├─ AI Macros: INTENT, META_EXEC, FFT
 └─ Holomorphic Tensor Ops (T729HoloTensor)
```

---

## 📦 Compiler + Language Stack

```
[ T81Lang Compiler ]
 ├─ Lexer, Parser, AST (t81lang_parser.cweb)
 ├─ Semantic Analysis (Symbol Table)
 ├─ Intermediate Representation (IR)
 ├─ IR-to-HVM Bytecode (emit_hvm.cweb)
 └─ CLI Compiler: t81lang_compiler.cweb

[ TISC Backend ]
 ├─ TISC Language IR (symbolic logic ops)
 ├─ LLVM IR Integration (i81 / custom DAG)
 └─ SIMD / Loop Optimizations (planned)
```

---

## 🤖 AI Integration (Axion)

```
[ Axion AI Kernel ]
 ├─ NLP Introspection: rollback, optimize
 ├─ Entropy Metrics: τ[27] register
 ├─ Telemetry Streaming + Pattern Analysis
 └─ Logging: AI macros, entropy triggers, tier history

[ Symbolic AI Framework ]
 ├─ Pattern Engine (t81_patterns.cweb)
 ├─ FFT Ops with entropy triggers
 └─ T729LogicGraph (symbolic IR for AI macros)

[ Metadata Blockchain (planned) ]
 ├─ Immutable AI Log Chain
 └─ Local + Distributed Verification
```

---

## 🖥️ Visualization & Developer Tooling

```
[ Project Looking Glass ]
 ├─ FrameSceneBuilder (Java 3D renderer)
 ├─ JSON Export: Recursion Frames + Stack
 └─ Axion Telemetry Overlay + Entropy Pulses

[ Disassembler + Debugger ]
 ├─ Disassembler with Symbolic Decoding
 ├─ Opcode Dump with AI Macros and Metadata
 └─ Debug Hooks + Export to JSON/XML

[ Telemetry & Log Viewer ]
 ├─ Event Filter / Timestamp Navigator
 ├─ Symbolic Execution Log Tracker
 └─ Axion NLP Log Summarizer
```

---

## ⚙️ GPU Acceleration & FFI

```
[ GAIA + CUDA GPU Dispatch ]
 ├─ GAIA ROCm Bridge (HIP + Graph API)
 ├─ CUDA Backend for T729 tensor ops
 ├─ FFT Kernels with entropy injection
 └─ Symbolic Debug Traces (GPU logs)

[ FFI Interface ]
 ├─ `libhanoivm_ffi.so` C ABI layer
 ├─ Symbolic operand access (push, pop)
 ├─ Event Hooks for Axion/NLP callbacks
 └─ Language Bindings (Rust, Python, etc.)
```

---

## 📡 Forensics + Network Integration

```
[ RiftCat Ghidra Plugin ]
 ├─ TCP/IP Packet Inspector (Live PCAP)
 ├─ OSI Layer Breakdown: Ethernet → TLS
 └─ Symbolic Traffic Classification (Axion)

[ Structured Export ]
 ├─ Symbolic Reports (JSON/XML/PDF)
 └─ TLS Anomaly Detection via Entropy Delta
```

---

## 🔧 Build System & Automation

```
[ CI/CD Pipeline ]
 ├─ GitHub Actions (`ci.yml`)
 ├─ Build Matrix: CPU, GPU, Docs
 └─ Artifact Upload: .hvm, .so, .pdf

[ Bazel Build System ]
 ├─ Literate Targets for .cweb files
 ├─ Shared Library Build for FFI
 └─ Compiler + Disassembler Binaries
```

---

## 🧪 Test Infrastructure

```
[ Kernel Test Harness ]
 ├─ `hanoivm-test.ko` (debugfs inspection)
 └─ Kernel-mode opcode sanity tests

[ Disassembler Unit Tests ]
 ├─ `disasm_logic_test`
 ├─ `disasm_controlflow_test`
 └─ `disasm_advanced_test`

[ VM Regression Suite ]
 ├─ Ternary operand edge cases
 └─ Recursive function correctness (FIB, FACT)
```

---

## 🧭 Research Extensions

```
[ PCIe Ternary Accelerator (Prototype) ]
 ├─ T81 logic loop in FPGA/verilog
 ├─ Firmware for runtime dispatch
 └─ M.2 Interface for direct memory access

[ WASM Port ]
 └─ Planning phase for web-based symbolic demo
```

---

## 🧠 HanoiVM is...

```
🌀 Recursive — Everything flows through tier-aware recursion
🔺 Symbolic — Data = logic = intent = structure
🧠 Intelligent — Every opcode is eligible for AI optimization
📖 Literate — Every file is a documented `.cweb` source
```

---

## 📘 See Also

- `README.md` — Overview and usage
- `ROADMAP.md` — Phase progress and goals
- `STATUS.md` — Completion percentages and subsystem status
- `MANIFESTO.md` — Philosophy and full file index
- `CONTRIBUTING.md` — Contribution guidelines and project vision
