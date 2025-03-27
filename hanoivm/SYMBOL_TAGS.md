# 🏷️ SYMBOL_TAGS.md — T81Lang + Axion Symbolic Metadata Tags

This document defines the standard set of symbolic tags used across the Copyleft Ternary Stack to describe recursion, entropy, AI behavior, and symbolic structure in `.t81`, `.cweb`, and `.hvm` artifacts.

---

## 🧠 Purpose
Symbolic tags provide metadata to Axion AI and the HanoiVM disassembler for introspection, optimization, and debugging.

Tags are used in:
- `.t81` source files (via inline `@tag:` comments)
- `.entropy.json` metadata logs
- `.cweb` metadata blocks
- Project Looking Glass visualization overlays

---

## 🔖 Core Tag Categories

### 📌 Recursion & Structure
| Tag               | Description                                       |
|------------------|---------------------------------------------------|
| `@entry_point`   | Designates main function / recursion root         |
| `@recursive`     | Function or opcode has recursive behavior         |
| `@tail_call`     | Function uses tail-recursive optimization         |
| `@pure`          | No side-effects, eligible for caching             |

### 🔁 Symbolic Execution
| Tag               | Description                                       |
|------------------|---------------------------------------------------|
| `@symbolic`      | Operand or function acts on symbolic data         |
| `@stateful`      | Depends on stateful or FSM logic                  |
| `@stateless`     | Free of global state                             |
| `@ai_macro`      | Represents an AI-dispatchable macro pattern       |

### 🎲 Entropy & Optimization
| Tag               | Description                                       |
|------------------|---------------------------------------------------|
| `@entropy_high`  | Detected high entropy (> threshold)              |
| `@entropy_low`   | Low entropy / stable symbolic path                |
| `@hot_path`      | Frequently executed, optimized by Axion           |
| `@rollable`      | Eligible for rollback in entropy regression       |

### 🧠 Axion AI Control
| Tag               | Description                                       |
|------------------|---------------------------------------------------|
| `@axion_only`    | Code region restricted to Axion AI execution     |
| `@no_optimize`   | Skip Axion optimization (debug/testing)           |
| `@snapshot`      | Symbolic snapshot capture point                   |
| `@ai_intent`     | Symbolic hint for future AI behavior              |

---

## 📤 Usage Examples

```t81lang
@tag: @entry_point @symbolic
fn main() -> T81Int {
    let n = T81Int(9)
    return factorial(n) @tag: @recursive @entropy_low
}
```

```json
{
  "ip": 44,
  "opcode": "T729_INTENT",
  "tags": ["@ai_macro", "@symbolic", "@entropy_high"]
}
```

---

> Tags are recursively resolved by Axion. Use sparingly and purposefully.

For best results, cross-reference with `LLM_CORRECTIONS.md`, `PROMPTS.md`, and `GLOSSARY.md`.
