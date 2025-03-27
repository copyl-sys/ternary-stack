# ⚙️ Build System — Copyleft Ternary Stack

This document defines a modular, unified build process for compiling and deploying components within the Copyleft Ternary Stack. It supports manual, scripted, and AI-assisted builds using standard tools (Make, Bash, CMake) with hooks for `.cweb` package execution.

---

## 🧱 Build Goals

- Compile `HanoiVM`, `T81Lang`, `Axion`, and `TISC` modules in isolation or together
- Generate reproducible builds for `.cweb` packages
- Integrate build flags and AI optimizations dynamically
- Support entropy-aware rebuilds and rollback checkpoints

---

## 📁 Project Structure (Build Context)

```bash
ternary-stack/
├── Makefile
├── build.sh
├── config/
│   └── global.mk
├── axion-ai/
├── hanoivm/
├── t81lang/
├── tisc-assembler/
├── project-lookingglass/
└── .cweb/
```

---

## 🧪 Build Script (`build.sh`)

```bash
#!/bin/bash
set -e

MODULES=("hanoivm" "axion-ai" "t81lang" "tisc-assembler")

for module in "${MODULES[@]}"; do
    echo "🔧 Building $module..."
    make -C "$module"
done

echo "✅ All modules built successfully."
```

> You may run `./build.sh` from root to build all components.

---

## 🛠 Makefile Conventions

Each module should include a `Makefile` that supports:
```make
build:
	gcc -o bin/mybinary src/*.c -Iinclude $(CFLAGS)

clean:
	rm -rf bin/*
```

Include `../config/global.mk` for shared flags:
```make
include ../config/global.mk
```

---

## 🧠 Axion AI Hooks

When run through Axion:
- `.cweb` flags are parsed to override build options
- AI may inject entropy tuning (`-DENTROPY_TRACE`)
- Rollback state is stored after build

---

## 🧱 CMake Integration (Optional)

Use `CMakeLists.txt` for more complex modules (e.g., Looking Glass):
```cmake
project(LookingGlass)
add_executable(lookingglass src/main.java)
```

Run with:
```bash
cmake .
make
```

---

## 📦 Building from .cweb

```bash
axion build path/to/module.cweb
```

Axion will:
- Parse metadata
- Resolve dependencies
- Select the proper toolchain (make/cmake/custom)
- Track entropy logs and build metrics

---

## 🔁 Cleaning

To clean all modules:
```bash
./build.sh clean
```

Or clean a specific one:
```bash
make -C hanoivm clean
```

---

## 📌 Build Flags & Optimizations

Available flags:
- `DEBUG=1` → Enables debug symbols
- `ENTROPY_TRACE=1` → Enables entropy instrumentation
- `AI_OPT=1` → Applies Axion-suggested flags

```bash
make DEBUG=1 ENTROPY_TRACE=1
```

---

Last updated: March 2025
Maintained by: `copyleft systems`
Mode: `./night_shift.sh -sync -copyleftsystems`

