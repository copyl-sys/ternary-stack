# 🌐 Copyleft Systems — Unified Ternary Computing Stack

Welcome to the master repository for the **Copyleft Ternary Stack**, an experimental, AI-native computing ecosystem that spans kernel-level AI, a ternary virtual machine, a domain-specific ternary language, and GPU/3D acceleration. This project aims to reclaim control of the full software stack—from entropy models to AI runtime.

---

## 📁 Project Structure

| Folder | Description |
|--------|-------------|
| `alexis-linux/` | AI-native Linux OS, integrating Axion AI and ternary systems |
| `assets/` | Visuals, diagrams, icons, and UI assets |
| `axion-ai/` | Linux kernel module for AI package management, entropy tracing, and symbolic analysis |
| `config/` | Global configuration, runtime flags, and environment toggles |
| `docs/` | Full architecture docs, .cweb spec, AI design, and language references |
| `examples/` | Sample programs demonstrating T81Lang, HanoiVM ops, and ternary recursion |
| `hanoivm/` | Recursive ternary virtual machine runtime for T81, T243, and T729 execution |
| `init_/` | Compressed initial setup files or bootloader stages (to be unpacked) |
| `project-lookingglass/` | Java 3D-based visualizer for AI introspection and ternary state rendering |
| `src/` | Shared source (to be split by module as needed) |
| `t81lang/` | High-level language for base-81 ternary computing; JIT and compiler work in progress |
| `tests/` | Unit and integration testing for modules across the stack |
| `tisc-assembler/` | Ternary Instruction Set (TISC) disassembler, opcode table, and analysis logic |

---

## 🧠 System Goals

- **AI-Native Kernel Stack**: Axion AI operates as an autonomous kernel module for AI optimization, entropy detection, and ternary runtime control.
- **HanoiVM**: Ternary recursion VM with T81/T243/T729 logic, symbolic execution, and stack promotion.
- **T81Lang**: Strongly typed, AI-assisted high-level language for ternary arithmetic and system programming.
- **Project Looking Glass**: A 3D visual window manager and introspection UI for AI behavior, ternary logic, and entropy feedback.
- **.cweb Format**: Structured plaintext package spec used by Axion for AI-driven source/binary builds.

---

## 🔁 Development Guidelines

- Modularize frequently — use `.cweb` files for split components under 50MB.
- Write to the `docs/` directory to keep concepts, specs, and roadmaps up-to-date.
- Keep all folders non-empty (Git limitation). Use `README.md` or `.keep` files.
- Use entropy and symbolic tracing when developing inside `hanoivm` or `axion-ai`.

---

## 🛠 Technologies Used

- C / Java / CUDA / Bash
- Custom `.cweb` build system
- Linux Kernel 6.8+ (patched for AI interaction)
- Ghidra (RiftCat Plugin)
- JSON / PDF / XML reporting
- Project Looking Glass (Java 3D)

---

## 📌 Future Goals

- LLVM backend for T81Lang → TISC codegen
- Axion-GAIA full GPU ternary AI bridge
- Quantum/entropy simulation APIs
- Autonomous AI packaging from logs + entropy feedback
- Secure AI sandboxing with rollback

---

> This system is experimental and radical by design. Expect recursion, entropy, and AI-native decisions.

---

© Copyleft Systems — `./night_shift.sh -sync -copyleftsystems`

