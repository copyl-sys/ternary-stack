# 🚀 HanoiVM — Recursive Ternary Virtual Machine

**HanoiVM** is a recursive, AI-augmented **ternary virtual machine** built on a symbolic base-81 architecture. It serves as the execution core of the **Axion + T81Lang** ecosystem, enabling stack-tier promotion, symbolic AI opcodes, and entropy-aware transformations across three logic levels:

- 🔹 **T81**: 81-bit operand logic (register-like)
- 🔸 **T243**: Symbolic BigInt + FSM state logic
- 🔺 **T729**: Tensor-based AI macros with semantic dispatch, including our new **Symbolic AI Graph IR (T729LogicGraph)**

Designed for research, language development, and future ternary hardware acceleration, **HanoiVM** is a literate, modular, and fully recursive platform with integrated debugging, telemetry, and cross-language support.

---

## 🔍 Core Features

- **Ternary Operand Architecture**  
  Supports `uint81_t`, `T243BigInt`, and `T729Tensor` data types.

- **Recursive Stack Tiering**  
  Auto-promotes through `T81 → T243 → T729` based on recursion depth and entropy metrics.

- **Symbolic AI Execution**  
  - Implements FSM logic, pattern recognition, and entropy-driven dispatch.
  - Features AI macros such as `TNN_ACCUM`, `T81_MATMUL`, `T729_INTENT`, and `T729_META_EXEC`.
  - Now enhanced with our **Symbolic AI Graph IR (T729LogicGraph)** for advanced optimization and introspection.

- **Tensor Engine & Holomorphic Support**  
  Provides operations like `DOT`, `SLICE`, `TRANSPOSE`, `RESHAPE`, `CLONE`, `PRINT`, and FFT for multidimensional signal processing.

- **Axion Kernel AI**  
  - Offers AI introspection, rollback, and optimization via NLP-style commands (`optimize`, `snapshot`).
  - Integrated telemetry, logging, and entropy weighting.

- **GPU Acceleration via GAIA**  
  - NVIDIA: `cuda_handle_request.cu`
  - AMD: `gaia_handle_request.cweb`

- **Cross-Language FFI Support**  
  - The FFI layer in `hanoivm_ffi.cweb` provides a C ABI interface.
  - Shared library (`libhanoivm_ffi.so`) allows integration with Rust, Python, and C++.

- **3D Visualization via Looking Glass**  
  - Uses `FrameSceneBuilder.cweb` for rendering recursion traces (e.g., with jMonkeyEngine).
  - Includes Axion overlays, ternary geometry, and entropy pulse animations.

- **Literate Codebase**  
  - All modules are written as `.cweb` sources, making the codebase self-documenting and extractable with `cweave`/`ctangle`.

- **Disassembler & Test Infrastructure**  
  - Disassembles `.hvm` bytecode with symbolic introspection.
  - CI-compatible tests and kernel-mode driver support for system-level validation.

---

## 📦 T81Lang Compiler Stack

The T81Lang toolchain is fully integrated with HanoiVM:

- **Lexer & Parser**: Implemented in `t81lang_parser.cweb`
- **Semantic Analyzer**: Handles scope and symbol resolution
- **Intermediate Representation (IR)**: Generates symbolic ops
- **.hvm Emitter**: Converts IR into executable bytecode
- **HVM Interpreter**: Executes bytecode using a register-based runtime
- **CLI Compiler**: Provided via `t81lang_compiler.cweb`

---

## 🔗 FFI & Cross-Language Integration

HanoiVM supports multi-language embedding through a robust FFI layer.

### 🔧 Compile the Shared Library:

```bash
make libhanoivm_ffi.so
```

### 📚 Available APIs:

- `hvm_create()` / `hvm_destroy()`
- `hvm_stack_push()` / `hvm_stack_pop()` / `hvm_stack_peek()`
- `hvm_execute()` for executing bytecode
- `hvm_set_event_callback()` for custom logging or AI hooks

These APIs enable integration with:

- **Rust** (via `bindgen` or `cxx`)
- **Python** (via `ctypes` or `cffi`)
- **C++** (via native linkage)

Refer to `hanoivm_ffi.cweb` for complete documentation.

---

## 🗂️ Repository Overview

```bash
src/
├── hanoivm_vm.cweb               # Enhanced VM Execution Core with logging/telemetry and integration hooks
├── hanoivm_ffi.cweb              # FFI interface (→ libhanoivm_ffi.so)
├── advanced_ops.cweb             # Core AI primitive opcodes and matrix operations
├── advanced_ops_ext.cweb         # T243/T729 extensions: FSM, intent, FFT, and entropy ops
├── t243bigint.cweb               # BigInt math for ternary (T243)
├── t729tensor.cweb               # Tensor operations for T729 tier
├── t729logicgraph.cweb           # Symbolic AI Graph IR for advanced optimization and introspection
├── t81_patterns.cweb             # Symbolic AI pattern recognition and dispatch
├── t81recursion.cweb             # Canonical recursion primitives for ternary execution
├── gaia_handle_request.cweb      # HIP-based GPU backend for symbolic ops
├── cuda_handle_request.cu        # CUDA-based GPU backend for tensor operations
├── axion-ai.cweb                 # Kernel AI optimizer and rollback hooks
├── disassembler.cweb             # `.hvm` disassembler with symbolic introspection
├── recursive_tier_execution.cweb # Tier transition driver (T81 → T729)
├── recursion_exporter.cweb       # Exports symbolic recursion trace to `.t81viz`
├── FrameSceneBuilder.cweb        # 3D recursion visualizer with jMonkeyEngine integration
├── tisc_backend.cweb             # TISC backend compiler for symbolic optimizations
```

---

## ⚙️ Getting Started

### 🔧 Build with Bazel

```bash
bazel build //...
```

### ✅ Run Tests

```bash
bazel test //:disasm_advanced_test
bazel test //:disasm_controlflow_test
bazel test //:disasm_logic_test
```

### 🧠 Kernel Test Harness

```bash
sudo insmod hanoivm-test.ko
cat /sys/kernel/debug/hanoivm-test
```

---

## 🔬 Tier Execution Demo

```bash
bazel run //:recursive_tier_execution -- --max-depth=36
```

---

## 🤖 Axion + GAIA Integration

- **GPU Execution Paths**:
  - NVIDIA: `cuda_handle_request.cu`
  - AMD: `gaia_handle_request.cweb`

- **Ternary AI Macros**:
  - `T729_INTENT` for symbolic AI behavior
  - `T729_META_EXEC` for conditional, entropy-weighted execution
  - `T729HoloTensor` for FFT and multidimensional signal composition

- **Signal Control**:
  - Axion AI tracks recursive entropy, triggering promotion/demotion
  - NLP commands (`rollback`, `optimize`, `snapshot`) available for runtime adjustments

---

## 🔁 Pattern + Symbolic Opcode Summary

| Opcode                | Tier   | Function                              |
|-----------------------|--------|---------------------------------------|
| `T81_MATMUL`          | T81    | Matrix multiply over base-81          |
| `T243_STATE_ADV`      | T243   | FSM state vector logic                |
| `T729_INTENT`         | T729   | Dispatch symbolic AI intent           |
| `T729_HOLO_FFT`       | T729   | FFT over holomorphic ternary tensor   |
| `T729_META_EXEC`      | T729   | Meta-instruction for conditional entropy|

---

## 📈 Project Status

✅ Recursive execution engine  
✅ Literate `.cweb` modular design  
✅ Full symbolic tier stack (T81 → T243 → T729)  
✅ Pattern dispatch and entropy signal handling  
✅ Axion AI integration with rollback and NLP  
✅ GPU offload (HIP + CUDA) for symbolic macros  
✅ FFI support: `libhanoivm_ffi.so` (Rust/C++/Python)  
✅ Verbose `.hvm` disassembler and type introspection  
✅ Kernel-level testing (`debugfs`)  
✅ `.t81viz` recursion trace export  
✅ 3D visualizer: `FrameSceneBuilder.cweb` + `PulseControl`  
🔜 Live REPL for `.t81` to `.hvm`  
🔜 LLVM IR export for hybrid backend  
🔜 Axion live log streaming in visualization mode  

---

## 🔗 Related Projects

- [**Axion AI**](https://github.com/copyl-sys) — AI optimizer and rollback kernel  
- **T81Lang** — Ternary language for symbolic logic + AI macros  
- [**Alexis Linux**](https://github.com/copyl-sys) — AI-first OS with ternary kernel base  
- **Project Looking Glass** — 3D GUI for recursion visualization and stack tiering  

---

## 📜 License and Documentation

**MIT License** — see `LICENSE` for full terms.

---

- **`.cwebpkg.md`**: Documentation related to the `.cweb` package system.
- **`AI_METADATA.md`**: Details on AI-related metadata used within the project.
- **`AXION_BLACKBOX.md`**: Information about the Axion black-box system.
- **`AXION_PACKAGE_FORMAT.md`**: Specifications for the Axion package format.
- **`Author.md`**: Information about the author(s) of the project.
- **`AxionCWEB.md`**: Documentation on integrating Axion with `.cweb`.
- **`CHANGELOG.md`**: Chronological list of changes and updates made to the project.
- **`CONTRIBUTING.md`**: Guidelines and instructions for contributing to the project.
- **`CWEB_STYLE_GUIDE.md`**: Style guide for writing `.cweb` files within the project.
- **`FILESYSTEM.md`**: Documentation on the project's filesystem structure and organization.
- **`GLOSSARY.md`**: Definitions of terms and concepts used throughout the project.
- **`INTEGRATION.md`**: Guidelines and notes on integrating HanoiVM with other systems or components.
- **`LLVM_GUIDE.md`**: Instructions and information on using LLVM within the project.
- **`MANIFESTO.md`**: Declaration of the project's philosophy, goals, and structure.
- **`README.md`**: Overview of the project, including usage instructions and features.
- **`ROADMAP.md`**: Planned future developments and milestones for the project.
- **`STATUS.md`**: Current status and progress of various components within the project.
- **`TECHTREE.md`**: Technical tree outlining the capabilities and subsystems of HanoiVM.


> 🧠 “Recursion is not just a structure — it’s the soul of ternary.”
