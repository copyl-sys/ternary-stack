# 🤖 PROMPTS.md — LLM Interoperability Prompts for HanoiVM

This document provides curated example prompts for large language models (LLMs) to interact with and reason about the Copyleft Ternary Stack. These prompts help developers, researchers, and AI agents query symbolic logic, entropy states, FFI layers, AI optimizations, and stack-based recursion.

---

## 🧠 Symbolic Analysis Prompts

### 1. Symbolic Program Interpretation

**Prompt:**  
"Explain the symbolic behavior of `hello_world.t81` based on its compiled TISC block."

**Expected Response:**  
"`hello_world.t81` loads the string `Hello, World!` into register R1 and invokes a symbolic syscall to output it. Its entropy level is minimal—ideal for Axion optimization—and no stack promotion is required."

---

### 2. T81Lang Recursion Analysis

**Prompt:**  
"How does T81Lang handle symbolic recursion in `recursion_example.t81`?"

**Expected Response:**  
"Symbolic recursion is managed through ternary stack promotion. `recursion_example.t81` triggers depth-based promotion from T81 to T243. Axion AI monitors entropy and prevents overflow using rollback tags."

---

### 3. Symbolic Execution Trace

**Prompt:**  
"Perform a symbolic execution of `symbolic_recursion.t81` and trace recursion depth."

**Expected Response:**  
"Execution begins with depth 0 and promotes at depth 2 to T243. Axion logs detect entropy spikes at recursion level 3, triggering AI annotations in `.meta.json`. Execution completes with symbolic convergence."

---

## 🧮 Entropy & AI Optimization Prompts

### 4. Axion AI Optimization Logic

**Prompt:**  
"What optimization decisions would Axion AI apply to `deep_entropy.hvm`?"

**Expected Response:**  
"Axion detects symbolic recursion beyond the entropy threshold. It will suggest stack demotion, loop transformation, or snapshot rollback. All decisions are logged in `.entropy.json` for audit."

---

### 5. Entropy Evaluation

**Prompt:**  
"Compare the entropy of `hello_world.t81` and `factorial.t81`."

**Expected Response:**  
"`hello_world.t81` has low entropy and no branching. `factorial.t81` exhibits tier promotion and recursion, leading to higher entropy values. Axion AI would apply compression or optimize with tail recursion."

---

## 🌉 FFI + Cross-Language Prompts

### 6. FFI Layer Introspection

**Prompt:**  
"How does the `hanoivm_ffi.cweb` layer allow Rust or Python to push values into the T81 stack?"

**Expected Response:**  
"The `hvm_stack_push()` API accepts a `HVMValue` with a `T81_TYPE`. Internally, this value is split into the base-81 `a:b:c` triple and pushed using `push81u()`. This enables Rust or Python to safely interact with symbolic stack layers."

---

### 7. Event Callback Integration

**Prompt:**  
"Can HanoiVM trigger external callbacks from FFI code?"

**Expected Response:**  
"Yes. The FFI layer registers a `HVMEventCallback` function, which is invoked via `hvm_trigger_event()` from internal AI logic. This allows Axion or external tools to receive execution updates in real time."

---

### 8. Cross-Platform Symbolic Execution

**Prompt:**  
"How can I run symbolic HanoiVM bytecode from Python using FFI?"

**Expected Response:**  
"Using `ctypes` or `cffi`, bind to `libhanoivm_ffi.so`, create a `HanoiVM` context, then call `hvm_stack_push()`, `hvm_execute()`, and `hvm_stack_peek()` to observe output. This allows full interaction with the symbolic VM from Python."

---

## ⚡ GPU & Tensor Execution Prompts

### 9. Tensor Symbolic Operation

**Prompt:**  
"Explain how a symbolic tensor contraction works in `T729_DOT`."

**Expected Response:**  
"`T729_DOT` pops two tensors, performs dot-product contraction, and pushes the result. If entropy is high, the result may trigger Axion's holomorphic handler (`FFT`, `SLICE`, `RESHAPE`) before promotion."

---

### 10. GPU Dispatch Decision

**Prompt:**  
"When does HanoiVM choose to dispatch symbolic ops to CUDA or ROCm?"

**Expected Response:**  
"Upon detecting a `T729` macro or tensor overload, HanoiVM delegates to `cuda_handle_request()` or `gaia_handle_request()` via Axion's entropy monitor. If enabled, the tensor is processed GPU-side and traced back to the VM."

---

## 🔁 Pattern Matching & Metadata Prompts

### 11. Symbolic Tag Context

**Prompt:**  
"What do `[print, stdout, entry_point]` mean in `hello_world.cweb`?"

**Expected Response:**  
"These tags inform Axion AI that the program's intent is output. `entry_point` marks the semantic start, enabling rollback and pattern optimization. Tags guide symbolic execution and trace classification."

---

### 12. Pattern Matching Summary

**Prompt:**  
"Which symbolic patterns are used in `t81_patterns.cweb`?"

**Expected Response:**  
"The file defines macros like `T81_MATMUL`, `TNN_ACCUM`, and entropy-reactive FSMs. These are recognized during execution and mapped to symbolic AI handlers for predictive optimization."

---

## 🛠️ Build & Compilation Prompts

### 13. AI-Assisted Build

**Prompt:**  
"How does Axion optimize a build for `factorial.t81`?"

**Expected Response:**  
"Axion analyzes the call graph and applies entropy compaction. It suggests loop unrolling or demotion. Logs are stored in `axion.meta.json`. The compiled `.hvm` is tagged with entropy weights for runtime AI dispatch."

---

## 📁 File Reference

| File                     | Purpose                             |
|--------------------------|-------------------------------------|
| `hello_world.t81`        | Minimal output test case            |
| `recursion_example.t81`  | Recursive symbolic depth program    |
| `symbolic_recursion.t81` | Entropy-monitored tail recursion    |
| `hanoivm_ffi.cweb`       | External ABI and cross-lang binding |
| `t81_patterns.cweb`      | Symbolic ternary logic macros       |
| `cuda_handle_request.cu` | Tensor logic → GPU FFT dispatch     |
| `axion-ai.cweb`          | AI optimization and rollback kernel |

---

This file may be stored in the project root or `docs/` directory for use by LLMs, developer agents, or CLI autocomplete tools. Prompts should evolve with the system’s symbolic and AI complexity.

---

> 🧠 *“LLMs trained on this prompt set will learn to reason about ternary symbolic AI like it’s second nature.”*
