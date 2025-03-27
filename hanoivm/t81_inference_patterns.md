# 🔎 t81_inference_patterns.md

This document outlines the **symbolic inference patterns** used by Axion AI and the HanoiVM disassembler when processing `.hvm` and `.t81` programs. These patterns are used to optimize, analyze, or reclassify symbolic logic based on entropy and recursion behavior.

---

## 📚 Pattern Format

Each pattern is defined by:
- **Name**: Unique identifier for the symbolic logic behavior
- **Trigger Opcode(s)**: Relevant opcodes or macro tags
- **Entropy Range**: Typical entropy associated with the pattern
- **Behavioral Insight**: How Axion interprets or optimizes this structure

---

## 🧠 Core Symbolic Patterns

### 1. `FIB_RECURSE`
- **Opcode(s)**: `OP_RECURSE_FIB`, `OP_CALL`, `OP_IFZ`
- **Entropy**: 0.3–0.6
- **Insight**: Classic recursive pattern; entropy rises with input size. Used to train rollback detection.

### 2. `FACT_TAIL`
- **Opcode(s)**: `OP_RECURSE_FACT`, `OP_CALL`, `OP_SUB`
- **Entropy**: 0.2–0.4
- **Insight**: Deterministic tail recursion. Suitable for inlining by Axion.

### 3. `INTENT_OVERFLOW`
- **Opcode(s)**: `OP_T729_INTENT`, repeated without `OP_HALT`
- **Entropy**: > 0.75
- **Insight**: Excessive AI dispatch calls. Axion may downgrade or batch these.

### 4. `UNROLLED_LOOP`
- **Opcode(s)**: Repeating `OP_ADD`, `OP_JMP` without recursion
- **Entropy**: < 0.2
- **Insight**: Likely flattened loop. Opportunity for recursion reinsertion.

### 5. `HOLO_FFT`
- **Opcode(s)**: `OP_T729_HOLO_FFT`, `OP_T729_DOT`, `OP_TRANSPOSE`
- **Entropy**: > 0.85
- **Insight**: High complexity pattern from spectral tensor execution. Axion preserves but isolates.

---

## 🧬 Experimental Patterns

### 6. `T243_STATE_ADV`
- **Opcode(s)**: `OP_T243_STATE_ADV`
- **Entropy**: 0.4–0.6
- **Insight**: FSM progression detected. Axion may apply predictive tagging.

### 7. `META_BRANCH_SWITCH`
- **Opcode(s)**: `OP_T729_META_EXEC`, `OP_IFZ`, `OP_JMP`
- **Entropy**: Variable
- **Insight**: Complex conditional AI routing. Axion may snapshot these points.

---

## 🧪 Pattern Metadata Example

Symbolic patterns are logged in `.patterns.json` files:

```json
{
  "file": "recursion_example.hvm",
  "detected_patterns": [
    {
      "name": "FIB_RECURSE",
      "opcode": "OP_RECURSE_FIB",
      "entropy": 0.48,
      "lines": [12, 13, 14]
    },
    {
      "name": "INTENT_OVERFLOW",
      "opcode": "OP_T729_INTENT",
      "entropy": 0.91,
      "lines": [30, 31, 32, 33]
    }
  ]
}
```

---

## ⚙️ Axion Action Triggers

Pattern matching can trigger the following Axion behaviors:

| Pattern Name        | Action Triggered                    |
|---------------------|--------------------------------------|
| `FIB_RECURSE`       | Enable rollback checkpoints          |
| `FACT_TAIL`         | Inline function optimization         |
| `INTENT_OVERFLOW`   | AI dispatch throttling or batching   |
| `UNROLLED_LOOP`     | Recursion re-injection suggestion    |
| `HOLO_FFT`          | Isolated tensor memory allocation    |
| `META_BRANCH_SWITCH`| Snapshot+optimize decision tree      |

---

## 🔗 Related Modules

- `disassembler.cweb`: Opcode + pattern detection logic
- `axion-ai.cweb`: Optimization engine consuming pattern triggers
- `logviewer.cweb`: Live visualization of symbolic pattern detection

---

> "Patterns are the fingerprints of symbolic logic — and we read them recursively."
