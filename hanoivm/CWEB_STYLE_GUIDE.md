# 🎨 CWEB_STYLE_GUIDE.md — Literate Symbolic Coding Standard (Axion/HanoiVM)

This document defines the **official `.cweb` style guide** for the Copyleft Ternary Stack. It enforces clarity, modularity, AI readability, and long-term maintainability across all symbolic `.cweb` modules.

---

## 📦 File Naming Convention

- Use lowercase, dash-separated names:
  - `hanoivm_vm.cweb`, `axion-ai.cweb`, `t81lang_parser.cweb`
- Prefix test files: `test_`, visual files: `frame_`, log tools: `log_`
- Versioned examples: `example_add_v1.cweb`

---

## 🧠 Module Header Block

Each file must begin with a module comment:
```cweb
@* filename.cweb | One-line purpose statement
Additional context or integration notes.
@#
```

---

## 🔗 Section Naming Patterns

Use `@<...@>=` tags to define logical modular blocks:
```cweb
@<Include Dependencies@>=
#include <stdio.h>
...
@#

@<Stack Control Operations@>=
void drop81(void) {...}
@#
```
- Keep section titles semantic.
- Do **not** overload sections; separate logic into atomic regions.

---

## 🛠️ Function Definitions

- One function per `@<...@>=` block unless tightly related.
- Always prefer verbosity over ambiguity.
- Use inline comments for AI audit and Axion hooks:
```c
axion_log("[VM] Executing T81_MATMUL");
```

---

## 📋 Header (`@h`) Blocks

- Provide full external interfaces via `@h`.
- Keep header declarations readable and minimal.
- Match header blocks with internal section order when possible.

---

## 📐 Line Width & Layout

- Max width: **100 columns**
- No tabs: **use 4-space indentation**
- Group includes by domain: stdlib → project-local → ai/runtime

---

## 🔍 Logging & Debugging

- All critical branches should be logged via `axion_log()`
- Example:
```c
if (stack_empty()) {
    axion_log("[Stack] Underflow error");
    exit(1);
}
```
- Include opcode names, IP location, symbolic intent when relevant

---

## 🔧 AI Metadata Hooks

- Use `axion_log_metadata()`, `log_entropy_trace()`, etc., for structured symbolic introspection.
- Metadata logs must be verifiable and semantically tagged.

---

## 📄 Documentation Style

- Always place semantic intent at top of module
- Embed usage examples in test `.cweb` where applicable
- Consider AI explainability at every function boundary

---

## ❌ Do Not:

- ❌ Use `goto`, unlabeled breaks, or obscure bit tricks
- ❌ Write monolithic 500+ line files (split with purpose)
- ❌ Assume binary-only logic: always account for ternary conditions
- ❌ Interleave AI and stack logic unless clearly documented

---

## ✅ Do:

- ✅ Split responsibilities into `*_stack`, `*_recursion`, `*_dispatch`
- ✅ Keep macros named descriptively: `OP_T729_META_EXEC`, `PROMOTE_T243()`
- ✅ Think recursively. Document loops as symbolic or entropic
- ✅ Let Axion introspect decisions: logging > performance

---

> Literate code is more than readable. It is symbolic, testable, recursive—and designed for AI to collaborate with humans.
