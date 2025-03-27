# 📦 .cweb Format Specification (Axion Package System)

`.cweb` is a plaintext, AI-aware packaging format used by the Axion AI module to manage, optimize, and build software in the Copyleft Ternary Stack. It defines how packages are described, compiled, split, versioned, and deployed across the stack.

---

## 🧾 File Overview

A `.cweb` file is structured into **predefined sections** with optional AI or security flags. Files over 50MB are auto-split by Axion into modular subcomponents.

Example:
```cweb
@name: hanoi-vm
@version: 0.3.1
@description: Recursive ternary virtual machine for T81/T243/T729 logic
@license: GPL-3.0
@homepage: https://github.com/copyl-sys/hanoivm

@source:
  type: git
  url: https://github.com/copyl-sys/hanoivm.git
  commit: 1a2b3c4

@build:
  system: make
  flags:
    - -DUSE_AXION
    - -O3

@dependencies:
  build:
    - axion-core
  runtime:
    - t81-runtime >= 0.2.0

@arch:
  - x86_64
  - aarch64
  - riscv64

@ai:
  optimize: true
  entropy-feedback: true

@binary:
  supported: false

@security:
  sandbox: true
  rollback: true

@logs:
  format: json
  retention: infinite

@split:
  enabled: true
  max_size_mb: 50
```

---

## 📚 Required Headers

| Field       | Description |
|-------------|-------------|
| `@name`     | Unique package identifier |
| `@version`  | Follows semver (`X.Y.Z`) |
| `@description` | One-line explanation |
| `@license`  | SPDX license ID |
| `@homepage` | Optional URL to docs or repo |

---

## 🔨 Build System Options

- `make`, `cmake`, `meson`, `cargo`, `custom`
- Axion can generate build plans dynamically using AI inference

---

## 📦 Dependency Types

- `build:` for tools needed during compilation
- `runtime:` for linked libraries or systems used during execution
- Optional `optional:` with `use`-like flags

---

## 🧠 AI Fields

| Field            | Description |
|------------------|-------------|
| `optimize`       | Enables AI optimization routines (e.g., compile-time heuristics) |
| `entropy-feedback` | Enables feedback loop from runtime entropy tracing to recompile/restructure |

---

## 🔐 Security Fields

- `sandbox:` isolates build in a jailed environment
- `rollback:` supports reversion if anomaly or corruption detected

---

## 🗂️ File Splitting (Auto-Modularization)

Axion will:
- Split any `.cweb`-defined package > 50MB into submodules (e.g., `core`, `drivers`, `utils`)
- Maintain linkage integrity and dependency resolution
- Log reasoning behind splits (stored in `logs/` with timestamped JSON/XML)

Example:
```
linux-core.cweb
linux-drivers.cweb
linux-tools.cweb
```

---

## 📁 Suggested Folder Structure

```bash
mypackage/
├── mod.cweb
├── src/
├── include/
├── tests/
├── ai/
├── build.sh
└── logs/
```

---

## 🛡️ Blockchain & Verification (Planned)

- All `.cweb` packages will be optionally tracked in a local metadata blockchain
- Package hashes, logs, and build signatures will be stored and verifiable
- Distributed peer audit mode for public `.cweb` registries

---

## 🧩 Usage With Axion

```bash
axion install hanoi-vm.cweb
axion build hanoi-vm
axion log-view hanoi-vm --format=json
```

---

Last updated: March 2025
Maintained by: `copyleft systems`
Mode: `./night_shift.sh -sync -copyleftsystems`

