# 📘 GLOSSARY.md — Copyleft Ternary Stack Glossary

A comprehensive glossary of symbolic terms, ternary data types, and project-specific acronyms used across the HanoiVM + Axion AI + T81Lang ecosystem.

---

## 🧠 Core Concepts

### **Ternary Logic**
A logical system based on three states: -1, 0, +1 (or in symbolic base-81: 0–80). Powers recursive evaluation, symbolic mutation, and AI macro resolution.

### **Symbolic Execution**
Execution driven not by concrete values but by abstract patterns and symbolic operands.

### **Entropy (Symbolic)**
Refers to the unpredictability or variability in symbolic instruction paths. Tracked by Axion AI.

### **Recursion Tier**
A logic layer within HanoiVM: T81 → T243 → T729, promoted based on entropy depth or operand complexity.

---

## 🧮 Ternary Data Types

### `uint81_t`
A 81-bit symbolic unsigned ternary integer. Implemented via struct: `a`, `b`, `c`.

### `T243BigInt`
243-trit BigInt with FSM extensions. Used for stateful symbolic processing.

### `T729Tensor`
Symbolic tensor macro representing AI intent, FFT patterns, and vectorized operations.

### `T243MarkovMatrix`, `T729EntropyBlob`
Advanced symbolic containers for FSM state prediction and entropy clustering.

---

## 🧠 Axion AI Terms

### **Axion Signal**
The entropy signature sent to Axion kernel layer per instruction dispatch.

### **Rollback**
AI-induced backtracking of symbolic execution to a previous low-entropy state.

### **Snapshot**
A captured state of symbolic stack and tier memory used for debug or rollback.

---

## 📄 File Types

### `.t81`
T81Lang source code (symbolic ternary syntax)

### `.hvm`
Compiled HanoiVM bytecode

### `.entropy.json`
Logged entropy trace for each instruction/session

### `.cweb`
Literate code + metadata packaging format

---

## 🔤 Symbol Tags

### `@symbolic`, `@entropy`, `@recursive`
Hints used by Axion to classify program structure and trigger specific optimization behaviors.

---

> This glossary evolves recursively with the stack — update alongside `.cweb` modules and Axion behaviors.
