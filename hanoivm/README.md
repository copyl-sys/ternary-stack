# 🚀 HanoiVM — Recursive Ternary Virtual Machine

**HanoiVM** is a recursive, AI-augmented **ternary virtual machine** built on a symbolic base-81 architecture. It is the execution core of the **Axion + T81Lang** ecosystem, enabling stack-tier promotion, symbolic AI opcodes, and entropy-aware transformations across three levels of logic:

- 🔹 `T81`: 81-bit operand logic (register-like)
- 🔸 `T243`: Symbolic BigInt + FSM state logic
- 🔺 `T729`: Tensor-based AI macros with semantic dispatch

Designed for research, language development, and future ternary hardware acceleration, **HanoiVM** is literate, modular, and fully recursive.

---

## 🔍 Core Features

- 🔢 **Ternary Operand Architecture**:
  - Supports `uint81_t`, `T243BigInt`, and `T729Tensor` data types
- 🌀 **Recursive Stack Tiering**:
  - Auto-promotes through `T81 → T243 → T729` based on depth/entropy
- 🧠 **Symbolic AI Execution**:
  - Includes FSM logic, pattern recognition, entropy-driven dispatch
  - AI macros: `TNN_ACCUM`, `T81_MATMUL`, `T729Intent`, `T729MetaOpcode`
- 🧬 **Tensor Engine + Holomorphic Support**:
  - `DOT`, `SLICE`, `TRANSPOSE`, `RESHAPE`, `CLONE`, `PRINT`, `FFT`
- ⚙️ **Axion Kernel AI**:
  - AI introspection + rollback via NLP-style commands (`optimize`, `snapshot`)
  - Integrated Axion telemetry, logs, entropy weighting
- ⚡ **GPU Acceleration via GAIA**:
  - AMD: `gaia_handle_request.cweb` (HIP)
  - NVIDIA: `cuda_handle_request.cu` (CUDA)
- 🧩 **Cross-Language FFI Support**:
  - `hanoivm_ffi.cweb` provides a C ABI interface
  - Shared library (`libhanoivm_ffi.so`) allows Rust, Python, C++ integration
- 🖼️ **3D Visualization via Looking Glass**:
  - `FrameSceneBuilder.cweb` renders recursion traces in jMonkeyEngine
  - Axion overlays, ternary geometry, and entropy pulse animation
- 📄 **Literate Codebase (`.cweb`)**:
  - Every module is self-documenting and extractable via `cweave`/`ctangle`
- 🧪 **Disassembler + Test Infrastructure**:
  - Disassembles `.hvm` with symbolic introspection
  - CI-compatible tests + kernel-mode driver for system-level validation

---

## 📦 T81Lang Compiler Stack

The T81Lang toolchain is now fully integrated with HanoiVM:

- ✅ **Lexer + Parser** → AST via `t81lang_parser.cweb`
- ✅ **Semantic Analyzer** with scope/symbol resolution
- ✅ **Intermediate Representation (IR)** with symbolic ops
- ✅ **.hvm Emitter** for virtual machine execution
- ✅ **HVM Interpreter** with register-based runtime
- ✅ **CLI Compiler** via `t81lang_compiler.cweb`

---

## 🔗 FFI & Cross-Language Integration

HanoiVM now supports **multi-language embedding** using the C-compatible FFI layer.

### 🔧 Compile the Shared Library:

```bash
make libhanoivm_ffi.so
```

### 📚 Available APIs:

- `hvm_create()` / `hvm_destroy()`
- `hvm_stack_push()` / `hvm_stack_pop()` / `hvm_stack_peek()`
- `hvm_execute()` for virtual machine execution
- `hvm_set_event_callback()` for custom logging or AI hooks

### 🧩 Use In:

- **Rust** via `bindgen` or `cxx`
- **Python** via `ctypes` or `cffi`
- **C++** via native linkage

See `hanoivm_ffi.cweb` for full documentation.

---

## 🗂️ Repository Overview

```bash
src/
├── hanoivm_vm.cweb               # Main interpreter engine
├── hanoivm_ffi.cweb              # FFI interface (→ libhanoivm_ffi.so)
├── advanced_ops.cweb             # TNN, matrix, AI primitive opcodes
├── advanced_ops_ext.cweb         # T243/T729 extensions: FSM, intent, FFT
├── t243bigint.cweb               # BigInt math in ternary (T243)
├── t729tensor.cweb               # Tensor logic for T729 tier
├── t81_patterns.cweb             # Symbolic AI patterns & dispatch
├── t81recursion.cweb             # Canonical ternary recursion patterns
├── gaia_handle_request.cweb      # HIP symbolic GPU backend
├── cuda_handle_request.cu        # CUDA symbolic tensor support
├── axion-ai.cweb                 # Kernel AI optimizer and rollback hooks
├── disassembler.cweb             # Human-readable `.hvm` introspector
├── recursive_tier_execution.cweb # Tier transition driver (T81 → T729)
├── recursion_exporter.cweb       # Export symbolic trace to `.t81viz`
├── FrameSceneBuilder.cweb        # 3D recursion visualizer with jMonkeyEngine
├── tisc_backend.cweb             # TISC backend compiler
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
  - `T729Intent` for symbolic AI behavior
  - `T729MetaOpcode` for entropy-weighted logic switching
  - `T729HoloTensor` for FFT and multi-dimensional signal composition

- **Signal Control**:
  - Axion tracks recursive entropy, triggers promotion/demotion
  - `rollback`, `optimize`, `snapshot` available via NLP hooks

---

## 🔁 Pattern + Symbolic Opcode Summary

| Opcode                | Tier   | Function                              |
|-----------------------|--------|---------------------------------------|
| `T81_MATMUL`          | T81    | Matrix multiply over base-81          |
| `T243_STATE_ADV`      | T243   | FSM state vector logic                |
| `T729_INTENT`         | T729   | Dispatch symbolic AI intent           |
| `T729_HOLO_FFT`       | T729   | FFT over holomorphic ternary tensor   |
| `T729_META_EXEC`      | T729   | Meta-instruction, conditional entropy |

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

## 📜 License

**MIT License** — see `LICENSE` for full terms.

---

> 🧠 “Recursion is not just a structure — it’s the soul of ternary.”
