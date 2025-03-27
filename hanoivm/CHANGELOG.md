# 📜 CHANGELOG.md

## [v0.9.1] - 2025-03-27

### ✨ Added

- **🌉 FFI Layer for Cross-Language Integration**
  - Introduced `hanoivm_ffi.cweb`, a portable C ABI wrapper for the HanoiVM runtime
  - Provides external access to VM context, stack operations, and execution control
  - Supports symbol-safe APIs for `hvm_create`, `hvm_execute`, `hvm_stack_push/pop/peek`, and event hooks
  - Dynamic callback registration via `hvm_set_event_callback` for Axion-style introspection

- **📦 Shared Library Build**
  - New build target for `libhanoivm_ffi.so` (via Makefile and `build-all.cweb`)
  - Position-independent code with full ternary operand conversion for FFI consumers
  - Compatible with Rust (`bindgen`/`cxx`), Python (`ctypes`/`cffi`), and C++

- **📄 Literate Documentation**
  - `README.md` and `MANIFESTO.md` updated with FFI embedding instructions
  - `ROADMAP.md` updated with new **Phase 6**: FFI Integration milestone
  - `.cweb` comments inside `hanoivm_ffi.cweb` document API stability and usage strategy

- **🔧 Bazel Compatibility**
  - Prep for new Bazel targets (`libhanoivm_ffi.so`, `ffi_test_runner`)
  - Future language bindings: `hanoivm_rs`, `hanoivm_py`, and `hanoivm_node`

### 🧪 Tests & Validation

- Manual FFI smoke test completed with Rust test harness
- JSON-level introspection validated via FFI stack peek/push cycles
- Confirmed no stack corruption or operand misalignment with base-81 representations

### 🔧 Changed

- **🛠️ Build Scripts**
  - `Makefile` and `build-all.cweb` updated to compile and package `libhanoivm_ffi.so`
  - Modularized `COMPILER_BIN` and `FFI_SRCS` for reuse across Make and Bazel

- **📖 Documentation Enhancements**
  - Expanded usage examples for external developers
  - Added `.so` references to packaging and install sections

- **🧩 Stack API Standardization**
  - Internal `push81u`/`pop81u` used directly in FFI interface for safe base-81 marshalling
  - Consolidated symbolic conversions for consistent external behavior

### 🐞 Fixed

- **📦 Package Script Corrections**
  - `build-all.cweb` tarball generation now includes `libhanoivm_ffi.so` correctly
  - Resolved issue where `COMPILER_BIN` was incomplete during `make package`

---

## [v0.9] - 2025-03-27

_See previous entry for full GPU, LLVM, and AI integration updates._

---

## 🔮 Notes & Future Directions

The v0.9.1 release completes the foundation for **multi-language HanoiVM integration**. With a stable FFI layer and shared library export:

- ✅ External CLI and REPL tools can embed HanoiVM
- ✅ Symbolic bytecode can now be generated and executed outside of native `.cweb`
- 🔜 Language-specific bindings (Rust, Python) coming in Phase 6
- 🔜 WASM compatibility is under early investigation

> _“The VM no longer speaks only C. It speaks wherever it is called.”_ — `hanoivm_ffi.cweb`
