# 🔌 INTEGRATION.md — Copyleft Ternary Stack: FFI and Multi-language Embedding

This document details how external systems—written in **C**, **C++**, **Rust**, and others—can embed and communicate with the **HanoiVM** execution core using the provided **FFI layer**.

---

## 🧱 Architecture Overview

```
+----------------------+      +----------------------+       +----------------------+  
|   External Program   | <--→ |   FFI Layer (C ABI)  | <--→  |  HanoiVM + T81 Stack  |
+----------------------+      +----------------------+       +----------------------+
       (Rust, C++, etc.)            (hanoivm_ffi.cweb)               (hanoivm_vm.cweb)
```

- Extern programs call `hvm_create()`, `hvm_stack_push()`, `hvm_execute()` via a portable C ABI.
- Internally, the FFI layer bridges to the recursive stack logic (e.g., `push81u`, `pop81u`).
- Axion AI hooks remain functional within the embedded VM context.

---

## 📦 Embedded Header: `hanoivm_ffi.cweb`

Provides a minimal, ABI-safe struct-based interface:

```c
typedef struct HanoiVM HanoiVM;
typedef enum { T81_TYPE = 0, T243_TYPE, T729_TYPE } HVMValueType;

typedef struct {
  HVMValueType type;
  union {
    uint64_t t81_value;
    void* t243_ptr;
    void* t729_tensor;
  } data;
} HVMValue;

HanoiVM* hvm_create();
void hvm_destroy(HanoiVM* vm);
int hvm_execute(HanoiVM* vm, int max_steps);
int hvm_stack_push(HanoiVM* vm, HVMValue val);
HVMValue hvm_stack_peek(HanoiVM* vm);
int hvm_stack_pop(HanoiVM* vm);
```

---

## 🦀 Rust Example (via `bindgen`)

```rust
extern "C" {
    fn hvm_create() -> *mut HanoiVM;
    fn hvm_stack_push(vm: *mut HanoiVM, val: HVMValue) -> i32;
    fn hvm_execute(vm: *mut HanoiVM, max_steps: i32) -> i32;
}

let vm = unsafe { hvm_create() };
let val = HVMValue {
    type_: T81_TYPE,
    data: HVMValue__bindgen_union_field { t81_value: 0x1234567890 },
};
unsafe {
    hvm_stack_push(vm, val);
    hvm_execute(vm, 100);
}
```

---

## 💡 C++ Example

```cpp
extern "C" {
#include "hanoivm_ffi.h"
}

HanoiVM* vm = hvm_create();
HVMValue val;
val.type = T81_TYPE;
val.data.t81_value = 0x112233445566;
hvm_stack_push(vm, val);
hvm_execute(vm, 500);
```

---

## 🧪 Testing FFI Integration

To test whether HanoiVM works embedded in an external program:

```c
#include "hanoivm_ffi.h"

int main() {
    HanoiVM* vm = hvm_create();
    HVMValue val = { .type = T81_TYPE, .data.t81_value = 0xAA55AA55 };
    hvm_stack_push(vm, val);
    hvm_execute(vm, 100);
    hvm_destroy(vm);
    return 0;
}
```

---

## ⚠️ Notes

- All FFI calls are **thread-safe but not reentrant**.
- Axion AI telemetry and rollback hooks still activate via `τ[27]`.
- Tier promotion will function **internally** as long as stack state reflects symbolic entropy.
- CMake or Bazel users can link against `hanoivm_ffi.c` and its dependencies.

---

## 🧠 FFI Future Extensions

| Feature                   | Status     | Notes                                         |
|---------------------------|------------|-----------------------------------------------|
| `hvm_load_hvm_file()`     | 🔜 Planned | Allow `.hvm` loading from external callers     |
| Tensor pointer FFI API    | 🔜 Planned | T729 tensor access from external tools         |
| Axion JSON Log Streaming  | 🔄 In Dev  | Real-time feedback to calling process          |
| Rust `cbindgen.toml`      | ✅ Done    | Header generator config for Rust ↔ C ABI       |

---

> The FFI interface enables HanoiVM to serve as a **symbolic execution backend** for any language.
> Embedding HanoiVM is recommended for any AI-aware system needing **deterministic ternary logic.**

