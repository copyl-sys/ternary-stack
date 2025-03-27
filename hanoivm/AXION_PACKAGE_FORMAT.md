# 📦 AXION_PACKAGE_FORMAT.md — The `.cwebpkg` Specification

The `.cwebpkg` format is the standardized, AI-native packaging system used by the Axion AI kernel and Alexis Linux ecosystem. It defines symbolic packages for source, binary, and AI-optimized components within the Copyleft Ternary Stack.

---

## 🧾 Header Structure
Each `.cwebpkg` file begins with a symbolic metadata block:

```ini
[package]
name = "example"
version = "0.1.0"
description = "Symbolic tensor FFT library for T729"
license = "MIT"
homepage = "https://github.com/copyl-sys"
```

---

## 🧩 Source Handling
```ini
[source]
url = "https://github.com/copyl-sys/example.tar.gz"
sha256 = "<verified-hash>"
method = "fetch"
```  
Supports: `fetch`, `git`, `local`

---

## ⚙️ Build System
```ini
[build]
tool = "make"  # Options: make, cmake, meson, bazel
cflags = "-O2 -Wall"
ldflags = ""
use_ai = true
```

---

## 📦 Dependencies
```ini
[dependencies]
libt81 = "1.2.0"
axion-ai = "*"
```
Supports optional, build-time, runtime flags via extensions:

```ini
[features]
fuzzing = false
simd = true
```

---

## 🏗️ Architecture
```ini
[arch]
x86_64 = true
aarch64 = true
riscv64 = true
```

---

## 🔄 Binary Support
```ini
[binary]
supported = true
path = "bin/example"
```

---

## 🧠 AI Optimization
```ini
[ai]
optimize = true
entropy_sensitive = true
allow_rollback = true
```
Axion uses this block to determine optimization strategy.

---

## 🚫 File Size Enforcement
Maximum package size per `.cwebpkg` is **50MB**. Axion will:
- Automatically split oversized packages (`example-core.cwebpkg`, `example-ext.cwebpkg`)
- Log split decisions with symbolic reasoning

---

## 📁 Logs + Export Format
```ini
[logs]
format = "json"
persist = true
```
Export options: `json`, `xml`, `plaintext`

---

## 🔐 Security Features
```ini
[security]
sandbox = true
signed = true
rollback = true
```

---

## 📜 Summary
`.cwebpkg` is designed to:
- Be auditable, AI-refinable, and modular
- Represent both source and binary logic
- Fit cleanly into Axion’s optimization and rollback system

It is the **package DNA** of symbolic AI systems.
