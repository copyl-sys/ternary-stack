# 🧪 Test Strategy — Copyleft Ternary Stack

This document defines the testing architecture and validation pipeline for components within the Copyleft Ternary Stack. It ensures correctness across ternary execution, AI interactions, symbolic logic, and entropy tracing.

---

## ✅ Core Testing Goals

- Verify correctness of ternary logic (T81, T243, T729)
- Confirm symbolic tags are preserved during execution
- Validate entropy logs and AI responses are consistent
- Ensure `.cweb` packages build reproducibly
- Catch regressions in recursion handling, AI optimization, or disassembler output

---

## 📁 Recommended Folder Layout

```bash
tests/
├── hanoi_vm/
│   ├── test_recursion.t81
│   ├── test_stack_promote.t81
│   └── expected_output/
├── axion_ai/
│   ├── entropy_injection.test
│   ├── log_verification.test
├── t81lang/
│   ├── basic_types.t81
│   ├── symbolic_execution.t81
├── tisc_assembler/
│   ├── opcode_decode.tisc
│   └── symbolic_mapping.json
└── integration/
    ├── hvm_entropy_loop.test
    ├── ai_rollback_chain.test
```

---

## 🧮 Unit Testing Modules

### `hanoi_vm`
- Validate correct stack behavior under T81/T243 recursion
- Symbol-to-value and entropy output for each opcode
- Runtime comparisons to golden outputs

### `t81lang`
- Test type enforcement, expression correctness
- JIT output vs TISC compilation
- Optional: type fuzz testing with symbolic mutations

### `tisc_assembler`
- Confirm opcodes translate correctly
- Verify disassembler regenerates equivalent symbolic metadata

### `axion_ai`
- Test entropy triggers and threshold handling
- Check rollback, sandbox, and recompile actions are logged
- Validate `.cweb` reassembly for split packages

---

## 🔁 Integration Testing

- Simulate full `.cweb` builds from source → entropy analysis → log review
- Run HanoiVM with Axion enabled and trace entropy blob propagation
- Confirm Looking Glass output aligns with symbolic + entropy logs

---

## 📦 `.cweb` Package Validation

- Confirm all `.cweb` files resolve dependencies correctly
- Rebuild packages with entropy-driven mutations (e.g., randomize build flags)
- Verify auto-splitting into modular components maintains linkage

---

## 🧪 Automation Tooling

- Use a Python or shell-based test runner for `.t81` and `.test` files
- Support parallel test threads (esp. for entropy feedback loops)
- Include test coverage reports and log diff viewers

---

## 📈 Logging & Reports

- Store test logs in `logs/tests/SESSION_ID/`
- Enable filtering by:
  - Module
  - Entropy trigger
  - Symbolic value
  - Timestamp

---

## 🔒 Secure Testing Recommendations

- Run Axion sandbox tests in an isolated VM
- Cryptographically sign entropy test logs
- Validate rollback state hashes match previous snapshots

---

Last updated: March 2025
Maintained by: `copyleft systems`
Mode: `./night_shift.sh -sync -copyleftsystems`

