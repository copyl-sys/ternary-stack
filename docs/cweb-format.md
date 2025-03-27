# 📦 .cweb Format Specification (Axion Package System)

`.cweb` is a plaintext, AI-aware packaging format used by the Axion AI module to manage, optimize, and build software in the Copyleft Ternary Stack. It defines how packages are described, compiled, split, versioned, and introspected—including symbolic metadata and entropy annotations.

---

## 🧾 File Overview

A `.cweb` file is structured into **predefined sections** with optional AI, symbolic, or security metadata. Files over 50MB are auto-split by Axion into modular subcomponents.

### ✨ Auto-generated Example (from `t81_compile.py`)
```json
@name: t81-sample-module
@version: 0.1.0
@description: Auto-generated from T81Lang parser (t81-sample-module)
@license: GPL-3.0

@source:
  type: local
  path: ./t81-sample-module/

@build:
  system: custom
  flags:
    - -DUSE_AXION

@dependencies:
  runtime: []

@ai:
  optimize: true
  entropy-feedback: true

@split:
  enabled: false
  max_size_mb: 50

@symbols:
  - symbol: ⍺
    entropy: 0.82
    tag: "checksum"
  - symbol: β
    entropy: 0.42
    tag: "probe"
```

---

## 📚 Required Headers

| Field         | Description |
|---------------|-------------|
| `@name`       | Unique package/module identifier |
| `@version`    | Follows semver (`X.Y.Z`) |
| `@description`| Short human-readable summary |
| `@license`    | SPDX license string |
| `@source`     | Path or git location of source files |

---

## 🔨 Build System Options

- `make`, `cmake`, `meson`, `cargo`, `custom`
- Axion can generate or override these with build plans using entropy analysis

---

## 📦 Dependency Types

- `runtime:` → Required during execution
- `build:` → Needed during compilation
- `optional:` → May depend on `use`-flags or architecture constraints

---

## 🧠 AI Fields

| Field               | Description |
|---------------------|-------------|
| `optimize`          | Enables compile-time optimization from Axion’s AI engine |
| `entropy-feedback`  | Enables recursive recompilation based on entropy trace logs |

These influence `t81_compile.py` and future build flows that incorporate entropy heuristics and symbolic modeling.

---

## 🔐 Security Fields

- `sandbox:` → Enables isolated builds  
- `rollback:` → Allows auto-revert if anomalies are found

---

## 📊 Symbol Metadata: `@symbols`

Symbol table exported from `t81_compile.py`’s entropy logger:
```json
@symbols:
  - symbol: ⍺
    entropy: 0.82
    tag: "checksum"
  - symbol: β
    entropy: 0.42
    tag: "probe"
```

This field allows Axion to:
- Model runtime entropy
- Track symbolic feedback loops
- Auto-partition modules using symbolic weights

---

## 🗂️ File Splitting (Auto-Modularization)

Axion will:
- Split packages > 50MB into components (e.g., `core`, `ai`, `utils`)
- Preserve metadata and dependency links
- Log rationale in `logs/` directory in JSON or XML format

---

## 📁 Suggested Folder Structure
```bash
mypackage/
├── mod.cweb
├── src/
├── include/
├── ai/
├── tests/
├── build.sh
└── logs/
```

---

## 🔗 Blockchain & Verification (Planned)

- Metadata hashes logged on local AI-secure chain
- Optionally synced to Axion HiveNet peer nodes
- Full audit trail for package transformations and entropy shifts

---

## 🧩 Usage With Axion
```bash
axion install mod.cweb
axion build mod
axion log-view mod --format=json
```

Generated `.cweb` files (like `t81-sample-module.cweb`) can be directly passed to Axion tooling, entropy analyzers, or symbolic report generators.

---

**Last updated:** March 2025  
**Maintained by:** `copyleft systems`  
**Mode:** `./night_shift.sh -sync -copyleftsystems`
