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
- 🖼️ **3D Visualization via Looking Glass**:
  - `FrameSceneBuilder.cweb` renders recursion traces in jMonkeyEngine
  - Axion overlays, ternary geometry, and entropy pulse animation
- 📄 **Literate Codebase (`.cweb`)**:
  - Every module is self-documenting and extractable via `cweave`/`ctangle`
- 🧪 **Disassembler + Test Infrastructure**:
  - Disassembles `.hvm` with symbolic introspection
  - CI-compatible tests + kernel-mode driver for system-level validation


---

## 📦 New: T81Lang Compiler Stack

The T81Lang toolchain is now fully integrated with HanoiVM:

- ✅ **Lexer + Parser** → AST via `t81lang_parser.cweb`
- ✅ **Semantic Analyzer** with scope/symbol resolution
- ✅ **Intermediate Representation (IR)** with symbolic ops
- ✅ **.hvm Emitter** for virtual machine execution
- ✅ **HVM Interpreter** with register-based runtime
- ✅ **CLI Compiler** via `t81lang_compiler.cweb`
---

## 🗂️ Repository Overview

```bash
src/
├── hanoivm_vm.cweb               # Main interpreter engine
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

tests/
├── hanoivm-test.cweb             # Kernel-mode debugfs test harness
├── test_advanced_hvm.cweb        # Test AI macros, recursion, control flow
├── t729tensor_to_string.cweb     # Tensor stringification for debug/logs

docs/
├── ROADMAP.md
├── CHANGELOG.md
├── t243_t729.md                  # Documentation for FSM, Intent, FFT

scripts/
├── disasm_*.sh                   # Bytecode disassembler tests

bazel/
├── BUILD                         # Bazel config for modular builds

README.md                         # You are here
```

---

## ⚙️ Getting Started

### 🔧 Build

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

### 🔬 Tier Execution Demo

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
✅ Verbose `.hvm` disassembler and type introspection  
✅ Kernel-level testing (`debugfs`)  
✅ `.t81viz` recursion trace export  
✅ 3D visualizer: `FrameSceneBuilder.cweb` + `PulseControl`  
🔜 Live REPL for `.t81` to `.hvm`  
🔜 LLVM IR export for hybrid backend  
🔜 Mouse-hover tooltips + optimization timeline overlay  
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


Here’s an **overview** of all the `.cweb` documents provided so far. Each `.cweb` file is part of our  larger ternary logic and system architecture, and they serve various roles in your project. Here’s a breakdown:

### 1. **`axion-gaia-interface.cweb`**
   - **Purpose**: Defines the GPU dispatch interface for ternary logic, bridging the **HanoiVM** ternary virtual machine and the **Axion Kernel Module** with GPU backends (GAIA/ROCm and CUDA).
   - **Key Features**:
     - Dispatches ternary macros.
     - Supports symbolic processing and intent-based computation.
     - Includes stubs for future backend integration.
   
### 2. **`axion-ai.cweb`**
   - **Purpose**: This file is a fully implemented **AI-powered kernel module** for **Axion**, enabling AI-driven resource management and anomaly detection.
   - **Key Features**:
     - Supports **ternary binary execution** (TBIN).
     - Implements **self-healing**, rollback mechanisms, and ternary-aware package management.
     - Integrates with natural language commands and telemetry logging.
     - Includes a **ternary instruction set** and simulated GPU usage.

### 3. **`config.cweb`**
   - **Purpose**: Centralizes configuration for the **HanoiVM** project and **Axion AI** kernel module.
   - **Key Features**:
     - Includes settings for **hardware acceleration** (PCIe, GPU).
     - Manages **AI optimization**, **logging**, and **resource management**.
     - Provides **environment detection** and **global ternary logic modes**.

### 4. **`disassembler.cweb`**
   - **Purpose**: Handles the disassembly of ternary bytecode in **HanoiVM**.
   - **Key Features**:
     - Decodes **T81 operands** and extended operand types like **BIGINT**, **FLOAT**, and **FRACTION**.
     - Translates opcodes, provides verbose output, and can dump data in **hex**.
     - Supports **JSON output** and session-aware disassembly integration.
     - Includes **entropy warnings** and symbolic operand decoding.

### 5. **`hanoivm_vm.cweb`**
   - **Purpose**: The core execution engine for **HanoiVM**, which handles recursion, stack promotion, and interaction with **Axion AI** hooks.
   - **Key Features**:
     - Interprets **.hvm bytecode** using the defined **Opcode** enum.
     - Integrates with **Axion AI** for runtime safety and optimization.
     - Manages the stack and recursion logic.
     - **Refactorable for synergy** with other modules like `config.cweb`.

### 6. **`hvm_promotion.cweb`** / **`t81_stack.cweb`**
   - **Purpose**: Manages the **stack promotion** and **ternary stack** operations within **HanoiVM**.
   - **Key Features**:
     - Handles **recursion engine** data.
     - Implements **JSON execution logging** for **postmortem analysis**.
     - Integrates **Axion entropy tracing** for better performance and analysis within `evaluate_opcode()`.

### 7. **`advanced_ops_ext.cweb`**
   - **Purpose**: Introduces advanced ternary data types and operations, specifically focusing on symbolic execution within **HanoiVM**.
   - **Key Features**:
     - Implements data types like **T243MarkovMatrix**, **T243Symbol**, **T729EntropyBlob**, **T243Circuit**, **T243MorphicTag**, and **T729MindMap**.
     - Supports complex ternary logic, symbolic execution, and higher-order ternary computation.

### 8. **`t81_patterns.cweb`**
   - **Purpose**: Defines reusable **T81-based ternary logic templates** and **computational macros**.
   - **Key Features**:
     - Includes standard ternary patterns for general use across **HanoiVM** and **Axion AI**.
     - Provides optimized ternary operations that can be reused in different contexts for efficiency.

### 9. **`t81_stack.cweb`** (Additional Reference)
   - **Purpose**: Implements and manages stack operations in ternary logic, supporting operations like **push**, **pop**, and **stack manipulation**.
   - **Key Features**:
     - Focused on stack management within **HanoiVM** for ternary data structures.
     - Supports **recursive functions** and stack-based optimizations.

---

### **High-Level Module Interaction**

- **`axion-ai.cweb`** and **`hanoivm_vm.cweb`** are central to the AI-driven and ternary execution aspects of your system. 
  - They enable AI-driven optimization, real-time resource management, and ternary logic execution (through the **HanoiVM** engine).
  
- **`config.cweb`** ties these modules together, allowing centralized configuration for both hardware and logic.
  
- **`disassembler.cweb`** provides visibility into **HanoiVM** bytecode execution, allowing you to inspect and debug ternary code at a low level.

- **`advanced_ops_ext.cweb`** and **`t81_patterns.cweb`** are higher-level utility modules that introduce additional computational power and reusable ternary logic templates for use in **HanoiVM**.

---

This modular setup allows for a robust and flexible ternary computing ecosystem, focusing on optimization, symbolic computation, and AI-driven resource management across the various components.
