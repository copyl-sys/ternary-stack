# 🏗️ Copyleft Systems — Ternary Stack Architecture

This document describes the architecture of the **Copyleft Ternary Stack**, a modular, AI-native system combining ternary logic, recursive virtual machines, secure entropy tracing, GPU acceleration, and an autonomous AI runtime. It defines how all the core components work together across OS, language, VM, and introspection layers.

---

## 🌐 System Overview

```
               +-------------------------+
               |   Project Looking Glass |
               |   (3D Ternary Visualizer)|
               +-----------+-------------+
                           |
                   [Ternary State JSON]
                           ↓
+------------------+   +---------------------+   +-----------------------+
|    T81Lang       | → |     HanoiVM         | → |    Axion AI Module    |
| (Source + JIT)   |   |  (T81/T243/T729 VM) |   | (Kernel/Entropy/Logs) |
+------------------+   +---------------------+   +-----------------------+
                           ↓                          ↑
                       [TISC Opcodes]             [Entropy Feedback]
                           ↓                          ↑
                   +---------------------+   +-----------------------+
                   |  GPU/GAIA Interface | ← | Axion-GPU Dispatcher  |
                   | (CUDA + ROCm bridge)|   +-----------------------+
                   +---------------------+
```

---

## 🧱 Layers and Responsibilities

### 1. `T81Lang/`
- High-level language supporting ternary types: `T81BigInt`, `T81Float`, `T81Fraction`
- Strong typing, SIMD optimizations, AI-assisted syntax trees
- Output targets: TISC opcode stream, JIT, LLVM backend (planned)

### 2. `HanoiVM/`
- Recursive ternary virtual machine
- Stack-based architecture supporting `T81`, `T243`, `T729` encoded logic
- Symbolic execution support and stack promotion engine
- Integrated with Axion AI for runtime entropy tracing

### 3. `Axion-AI/`
- Linux kernel module powering:
  - Entropy detection, symbolic anomalies
  - Runtime AI optimization
  - `.cweb` package management
- Logging and telemetry tied to session-aware introspection

### 4. `TISC-Assembler/`
- Low-level ternary instruction set
- Disassembler with symbolic operand decoding
- Opcode analyzer and entropy trace emitter

### 5. `Project-LookingGlass/`
- Java 3D-based window manager
- Visualizes:
  - VM recursion depth
  - Ternary state objects
  - Entropy fluctuations
  - Axion behavioral logs
- Communicates via JSON schema exported from HanoiVM/Axion

### 6. `Axion-GPU Interface`
- Dispatch bridge for CUDA/ROCm-based ternary macro execution
- Will house entropy blob transformers and vectorized symbolic models

---

## 📦 `.cweb` Ecosystem Integration

- `.cweb` is a unified plaintext format for Axion's AI-driven package management system
- Contains:
  - Metadata, dependencies, architecture targets
  - Build options, AI flags, rollback/sandbox config
- Supports modular decomposition and automatic splitting if >50MB
- All modules (VM, Lang, OS) can be packaged, versioned, and deployed through `.cweb`

---

## 🔐 Entropy + Introspection Pipeline

- Axion logs runtime state changes, AI optimization actions, and entropy scores
- Disassembler emits symbolic traces with metadata
- Logs and metrics are visualized via Looking Glass
- Axion adjusts runtime behavior based on entropy models and symbolic feedback

---

## 🧠 Philosophy of the Stack

- Recursive computing is the foundation of emergent AI
- Entropy is a measure of both signal and potential
- AI systems must introspect and optimize from within
- Code and language must reflect ternary logic, not just binary approximation

---

## 🔁 Future Integrations

- AI Hive Networking for Axion swarm learning
- Local blockchain-based metadata for package/auth traceability
- FPGA-based HanoiVM runtime for native ternary acceleration
- Voice/gesture interface layer for Looking Glass

---

Last updated: March 2025
Author: `copyleft systems`

