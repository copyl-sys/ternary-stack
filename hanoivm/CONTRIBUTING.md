# 🤝 Contributing to **HanoiVM**

Welcome! 🎉 We're thrilled you're considering contributing to **HanoiVM** — a recursive, AI-augmented ternary virtual machine at the core of the T81Lang, Axion, and Alexis Linux ecosystems.

This guide will walk you through our contribution process, standards, and best practices.

---

## 📦 Project Overview

HanoiVM is written in **literate programming** style (`.cweb`) and compiled using `cweave`, `ctangle`, LLVM, and Bazel. It supports AI-augmented symbolic logic in ternary computing tiers (`T81`, `T243`, `T729`) and integrates with:

- ✳️ `Axion AI` — entropy feedback and optimization
- 💠 `T81Lang` — high-level ternary programming language
- 📊 `RiftCat`, `Looking Glass` — security and visualization tools
- 🔁 `LLVM`, `FFI`, `GPU Backends` — full-stack integration

---

## 🛠️ Development Requirements

Ensure your environment includes:

- `clang`, `llvm-17`, `lld-17`
- `cmake`, `ninja`
- `bazel` (≥6.0)
- `cweb`, `texlive-full` (for literate docs)
- GPU tooling (optional): `nvcc`, `rocm-dev`

Run:

```bash
./tangle-all.sh  # Extract all .cweb modules
bazel build //...
bazel test //...
```

---

## ✍️ Code Style & Structure

### 🧵 Literate `.cweb` Format

All logic is written in `.cweb` files, combining C/C++ and documentation. Follow these conventions:

- Use `@<Section Title@>=` blocks for logic separation.
- Always include an embedded `@h` header block (e.g., `libt81.h`).
- Structure `.cweb` like a narrative — clean, modular, and annotated.

### 🔠 Naming

| Entity        | Convention          | Example                     |
|---------------|---------------------|-----------------------------|
| Functions     | `snake_case`        | `evaluate_opcode()`         |
| Structs/Types | `T81PascalCase`     | `T81BigIntImpl`, `T729MindMap` |
| Macros        | `ALL_CAPS`          | `OP_T729_META_EXEC`         |
| Files         | Descriptive `cweb`  | `hanoivm_vm.cweb`, `axion-ai.cweb` |

---

## 🧪 Testing

All contributions **must include test coverage** for:

- Opcode behavior
- Stack/FFI consistency
- Tier transitions
- AI logic triggers (if applicable)

Run:

```bash
bazel test //:disasm_logic_test
```

For GPU-related changes:

```bash
./cuda_backend --test
./gaia_backend --test
```

For kernel module validation (optional):

```bash
sudo insmod hanoivm-test.ko
cat /sys/kernel/debug/hanoivm-test
```

---

## 🧠 Axion AI Contributions

Axion is a **black-box optimizer** but logs its symbolic entropy decisions.

If contributing to `axion-ai.cweb` or entropy macros:

- Log all actions to `debugfs` or `logviewer.cweb`.
- Avoid manual overrides: Axion should always determine final behavior.
- Preserve NLP command compatibility (`optimize`, `rollback`, etc.).

Use verbose logging for macro-level opcode logic, especially in AI-enhanced opcodes.

---

## 🔗 FFI Considerations

When modifying `libhanoivm_ffi.so`:

- Ensure ABI compatibility (`extern "C"`, no C++ symbols).
- Update `hanoivm_ffi.cweb` docs if function signatures change.
- Validate against at least one binding: `hanoivm-py`, `hanoivm-rs`, or `ctypes`.

---

## 📜 Pull Request Guidelines

1. **Fork + Feature Branch**  
   Work off `main` using a branch like `feature/ternary-mindmap`.

2. **Describe Changes Clearly**  
   Include:
   - Which `.cweb` modules were affected
   - Which opcodes/types were introduced or modified
   - Whether entropy/AI behavior is affected

3. **Run Tests + Linting**  
   Pass all Bazel and CI checks.

4. **Link to Issues**  
   Reference related issues or Roadmap items with `Closes #xxx`.

5. **Be Literate**  
   Maintain the readability of your `.cweb` blocks — code is documentation here.

---

## 💬 Communication

- **Discussions:** Use GitHub Discussions for questions, ideas, and architectural proposals.
- **Issues:** For bugs, feature requests, or odd symbolic behavior.
- **Commits:** Use semantic prefixes (`fix:`, `feat:`, `docs:`, `refactor:`).

---

## 🔐 Security & Ethics

Ternary computing, entropy analysis, and symbolic recursion have serious implications for AI, cryptography, and national infrastructure. Please:

- Never submit backdoors, tracking code, or malicious macros.
- Respect ethical use cases (e.g., forensic tooling, open AI).
- Use `SECURITY.md` to report vulnerabilities privately.

---

## 📜 License

By contributing, you agree to license your work under the **MIT License** and follow the project's values of transparency, recursion, and symbolic clarity.

---

> 🧠 *“Your code becomes thought when written as recursion.” — The Hanoi Manifesto*
