# 🚀 HanoiVM — Recursive Ternary Virtual Machine | 

Goal A) Alexis Linux; (hybrid 'binary/ternary' linux via kernel module axion-io.ko);

Goal B) Lilly Shea (ternary-linux; no module needed) // Note; I do not call it linux after this point.
      Thank you for an education Linus; that is all. 

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

Here’s a list of all the data types supported across the different base types, reflecting the ternary logic systems and symbolic AI operations:

---

### **T81 Base Type (Base-81 Logic)**
1. **T81BigInt**: Supports large integers in the Base-81 system, used for arbitrary-precision arithmetic.
2. **T81Float**: Floating-point values represented in Base-81 format.
3. **T81Fraction**: Rational numbers, with a numerator and denominator in Base-81.
4. **T81Matrix**: A matrix data type for multidimensional arrays in Base-81.
5. **T81Vector**: A vector data type, representing ordered sequences in Base-81.
6. **T81Quaternion**: A quaternion representation for 3D rotations or transformations.
7. **T81Polynomial**: Polynomial expressions in Base-81, supporting operations like addition, multiplication, and factorization.
8. **T81Tensor**: Higher-dimensional arrays that generalize matrices to more dimensions, used for complex symbolic operations.
9. **T81Graph**: Graph data structure, representing nodes and edges in Base-81 logic, typically used for symbolic reasoning.
10. **T81Opcode**: Custom instruction set used within the HanoiVM, representing specific ternary operations.

---

### **T243 Base Type (Expanded Ternary Logic)**
1. **T243MarkovMatrix**: Matrix type for representing transition probabilities or state changes in T243 logic.
2. **T243StateVector**: A vector representing a state in a finite state machine, encoded in T243 logic.
3. **T243Symbol**: Symbolic representation, using an ID and UTF-8 string for interaction with T243 states.
4. **T243Circuit**: A digital circuit representation, including logic gates and their states, used for symbolic processing in T243.
5. **T243MorphicTag**: A type used for symbolic operation resolution, applying context and base operation information.
6. **T243SymbolicVector**: A more advanced representation that integrates symbolic processing with ternary logic.

---

### **T729 Base Type (Advanced Ternary Logic)**
1. **T729HoloTensor**: Ternary tensor type for symbolic operations like symbolic Fourier Transform (FFT) and advanced AI functions.
2. **T729MindMap**: A data structure for symbolic reasoning, representing relationships and connections between concepts or ideas in T729 logic.
3. **T729EntropyBlob**: Represents entropy-based data for measuring the randomness and stability of a process, used in AI-driven systems.
4. **T729LogicGraph**: A graph structure that models symbolic AI and logic operations in the T729 space, allowing complex logical deductions.
5. **T729Intent**: Represents an AI intent in symbolic logic, used for optimization or heuristic-based symbolic problem solving.

---

### **Symbolic AI Data Types (Across All Base Types)**
1. **T729Tensor**: A more general and advanced tensor type that allows for symbolic and machine learning operations.
2. **T243SymbolicState**: A symbolic state type used for AI decision-making and system transitions within the T243 space.
3. **T729MarkovChain**: A type for modeling probabilistic state transitions in T729, leveraging symbolic AI operations.
4. **T243AIStateVector**: A vector type for holding AI state information in the T243 system, often used for feedback loops and optimization tasks.

---

### **Cross-Base Data Types**
1. **T81T243Transition**: A cross-base type for handling transitions between T81 and T243 states, especially in hybrid computation scenarios.
2. **T243T729SymbolicLink**: A type that connects T243 and T729 logic, allowing operations to span both ternary logic systems.
3. **T81T729Interaction**: Data type designed for interaction between T81 and T729 logic, useful for symbolic AI and advanced tensor-based operations.

---

This summary captures the various data types across the three main logic systems (T81, T243, and T729) used in the HanoiVM project, including AI-specific types designed for symbolic computation, entropy-driven logic, and tensor operations.
