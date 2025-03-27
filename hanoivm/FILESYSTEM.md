# 📂 FILESYSTEM.md — Copyleft Ternary Stack File Layout

This document defines the **directory structure**, **file roles**, and **organizational philosophy** for the Copyleft Ternary Stack. It is optimized for symbolic reasoning, AI-driven tooling, and ternary logic development.

---

## 📁 Root Directory

| Path / File             | Description                                                                 |
|-------------------------|-----------------------------------------------------------------------------|
| `README.md`             | Top-level overview, usage, and build instructions                           |
| `MANIFESTO.md`          | Project philosophy and module index                                         |
| `STATUS.md`             | Current development progress and component status tracking                  |
| `ROADMAP.md`            | Forward-looking plans and architectural milestones                          |
| `CHANGELOG.md`          | Version-by-version changelog for all modules                                |
| `PROMPTS.md`            | Prompt engineering guide for interacting with LLMs                          |
| `LLM_CORRECTIONS.md`    | Misconceptions and AI-specific reasoning clarifications                      |
| `LLM_INDEX.md`          | Semantic keyword index for all major components                             |
| `entropy-guide.md`      | Explanation of entropy analysis logic in symbolic programs                  |
| `t81_inference_patterns.md` | Inference patterns used by Axion + disassembler                            |

---

## 📁 `src/` — Core HanoiVM Modules

| File                           | Description                                                         |
|--------------------------------|---------------------------------------------------------------------|
| `hanoivm_vm.cweb`              | Core VM execution loop with recursion, AI hooks, tier promotion     |
| `t81_stack.cweb`               | T81 integer stack and arithmetic ops                                |
| `t243bigint.cweb`              | T243 BigInt symbolic operations                                     |
| `t729tensor.cweb`              | Tensor macros and holomorphic logic                                 |
| `advanced_ops.cweb`            | T81 logic macros, e.g. `matmul`, `accum`, `cmp3`                    |
| `advanced_ops_ext.cweb`        | T243/T729 symbolic and AI-focused ops                               |
| `recursive_tier_execution.cweb`| Demonstrates symbolic stack promotion                               |
| `axion-ai.cweb`                | Kernel AI interface and runtime optimizer                           |
| `gaia_handle_request.cweb`     | HIP symbolic GPU handler                                            |
| `cuda_handle_request.cu`       | CUDA symbolic GPU handler                                           |
| `disassembler.cweb`            | Opcode disassembler with entropy/symbolic tag awareness             |
| `config.cweb`                  | Runtime flags, constants, and feature switches                      |

---

## 📁 `compiler/` — T81Lang & TISC

| File                        | Description                                                           |
|----------------------------|-----------------------------------------------------------------------|
| `t81lang_parser.cweb`      | Lexer + parser to convert `.t81` into AST                            |
| `t81lang_irgen.cweb`       | IR generator with symbolic instruction templates                     |
| `emit_hvm.cweb`            | Bytecode emitter for `.hvm` output                                   |
| `t81lang_compiler.cweb`    | Full CLI compiler driver for `.t81` source                           |
| `tisc_backend.cweb`        | IR → `.hvm` backend for symbolic instruction selection                |
| `tisc_stdlib.cweb`         | Macros and ops used across symbolic assembly                         |

---

## 📁 `runtime/` — Execution + Testing

| File                        | Description                                                              |
|----------------------------|--------------------------------------------------------------------------|
| `hvm_loader.cweb`          | Bytecode loader for `.hvm` programs                                      |
| `hvm_interpreter.cweb`     | Runtime interpreter for VM execution                                     |
| `hanoivm-test.cweb`        | Kernel test harness for loading Axion/HanoiVM stack                      |
| `test_advanced_hvm.cweb`   | Symbolic + recursion macro test coverage                                 |
| `test_controlflow_hvm.cweb`| Jump, branch, and recursion logic validation                             |
| `test_t243bigint_hvm.cweb` | Extended BigInt operation tests                                          |
| `test_t729tensor_hvm.cweb` | Tensor flow, FFT, and AI pattern testing                                 |

---

## 📁 `docs/` — Extended References

| File                      | Description                                                           |
|--------------------------|-----------------------------------------------------------------------|
| `entropy-guide.md`       | Semantic entropy tracking and Axion interaction                      |
| `PROMPTS.md`             | Sample LLM prompts for program introspection                         |
| `LLM_CORRECTIONS.md`     | Clarifications and logic for reasoning agents                        |
| `t81_inference_patterns.md` | Pattern definitions used in symbolic matching                     |

---

## 📁 `pkg/` — `.cwebpkg` Package Structure (Upcoming)

| File / Folder           | Description                                                             |
|-------------------------|-------------------------------------------------------------------------|
| `*.cwebpkg`             | Literate package definitions for source-based installs                 |
| `axion-ai.cweb`         | AI logic included in package manifest                                  |
| `metadata.json`         | Dependency, architecture, and optimization hints                       |

---

## 📁 `visual/` — Project Looking Glass

| File                        | Description                                                        |
|----------------------------|--------------------------------------------------------------------|
| `FrameSceneBuilder.cweb`   | 3D scene graph construction from recursive trace                   |
| `PulseControl.cweb`        | Entropy animation handler                                          |
| `logviewer.cweb`           | Live log inspection with symbolic filters                          |

---

## 📁 `scripts/` — Utilities and Analysis

| File                     | Description                                                    |
|--------------------------|----------------------------------------------------------------|
| `disasm_*.sh`            | Disassembly test scripts                                       |
| `ghidra_output.log`      | Ghidra test plugin outputs (if available)                      |
| `vm_benchmark_comparison.csv` | Performance comparison across symbolic + compiled programs |

---

> The filesystem is symbolic, modular, and AI-optimized — just like the logic it supports.
