# 📐 T81_IR_SPEC.md — Intermediate Representation for T81Lang

This document defines the canonical Intermediate Representation (IR) format used by the T81Lang compiler pipeline. The IR is designed for symbolic ternary computation, AI-guided optimization, and `.hvm` bytecode emission.

---

## 🎯 Design Goals
- Support symbolic, recursive, and entropy-aware logic
- Be easily serializable to JSON (`.ir.json`) and `.hvm`
- Maintain clarity between semantic layers: T81 → IR → TISC
- Enable Axion AI optimization hooks and symbolic introspection

---

## 📄 IR Node Format (JSON)
```json
{
  "op": "IR_ADD",
  "args": ["%1", "%2"],
  "dest": "%3",
  "tags": ["@symbolic", "@hot_path"]
}
```

---

## 🧱 Core Instruction Set
| IR Opcode     | Description                              | Ternary Tier | Tags             |
|---------------|------------------------------------------|--------------|------------------|
| `IR_ADD`      | Add two symbolic T81 values              | T81          | `@symbolic`      |
| `IR_SUB`      | Subtract symbolic values                 | T81          | `@symbolic`      |
| `IR_MUL`      | Multiply symbolic values                 | T81          | `@symbolic`      |
| `IR_DIV`      | Divide with ternary safety checks        | T81          | `@symbolic`      |
| `IR_MOD`      | Ternary modulo                          | T81          | `@symbolic`      |
| `IR_NEG`      | Negation (flip polarity)                | T81          | `@symbolic`      |
| `IR_CMP3`     | Trinary comparison                      | T81          | `@symbolic`      |
| `IR_PUSH`     | Push a value to T81 stack               | T81          | `@stateful`      |
| `IR_POP`      | Pop a value from stack                  | T81          | `@stateful`      |

---

## 🔁 Control Flow
| IR Opcode     | Description                              | Tags              |
|---------------|------------------------------------------|-------------------|
| `IR_JMP`      | Unconditional jump                      | `@stateless`      |
| `IR_JZ`       | Jump if zero (ternary)                  | `@symbolic`       |
| `IR_CALL`     | Function call                           | `@recursive`      |
| `IR_RET`      | Return from function                    | `@stateful`       |

---

## 🧠 Symbolic / AI Macros
| IR Opcode           | Description                           | Tier     | Tags                  |
|---------------------|---------------------------------------|----------|-----------------------|
| `IR_TNN_ACCUM`      | AI-accumulation (tensor or scalar)    | T729     | `@ai_macro`           |
| `IR_T81_MATMUL`     | Matrix multiplication in T81 space    | T81      | `@symbolic`           |
| `IR_T729_INTENT`    | Dispatch AI semantic intent           | T729     | `@ai_macro`, `@entropy_high` |
| `IR_T729_HOLO_FFT`  | Holomorphic symbolic FFT              | T729     | `@symbolic`, `@entropy_high` |
| `IR_T243_STATE_ADV` | FSM state transition macro            | T243     | `@symbolic`, `@stateful` |

---

## 🔣 Naming Convention
- `%N` — SSA-style symbolic registers
- `@tag:` — Inline symbolic metadata for Axion
- `.ir.json` — IR file format passed into `.hvm` emitter

---

## 🔗 Integration Points
- `t81lang_irgen.cweb` — IR generator from AST
- `emit_hvm.cweb` — HVM bytecode generator from IR
- `axion-ai.cweb` — Entropy analysis and symbolic dispatch
- `disassembler.cweb` — Symbolic introspection of `.hvm`

---

> Axion reads tags during IR generation to preemptively optimize recursion depth, entropy levels, and symbolic intent.

Cross-reference with: `SYMBOL_TAGS.md`, `PROMPTS.md`, `LLM_CORRECTIONS.md`, and `GLOSSARY.md` for coherent reasoning.
