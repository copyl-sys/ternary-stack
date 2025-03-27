# 📘 entropy-guide.md

## 🔍 Overview

This guide introduces the concept of **symbolic entropy** in the Copyleft Ternary Stack, describing how it is measured, tracked, and interpreted by **Axion AI**, **HanoiVM**, and symbolic execution engines. Entropy in this system does **not** refer to thermodynamic randomness but instead to **symbolic unpredictability**, **execution variability**, and **pattern divergence**.

---

## 🧠 What is Symbolic Entropy?

Symbolic entropy measures the degree to which a program's behavior, structure, or data diverges from predictable symbolic patterns. Axion AI uses entropy as a signal to:

- 🔄 Trigger recursion promotions (e.g., T81 → T243 → T729)
- ⚖️ Optimize symbolic logic for deterministic behavior
- 🚨 Detect anomalies, instability, or execution bottlenecks

**Entropy != randomness.**
- 🔹 Low entropy → predictable, static, symbolic structure
- 🔸 Medium entropy → dynamic but structured symbolic variation
- 🔺 High entropy → branching recursion, macro ambiguity, tensor-state non-linearity

---

## 📊 Entropy Metadata Fields

Each execution trace or compiled `.hvm` file can include a metadata block (`.entropy.json`) with fields:

```json
{
  "file": "example.hvm",
  "max_depth": 3,
  "entropy_range": [0.02, 0.88],
  "tier_promotion_events": 2,
  "detected_patterns": ["FIB_RECURSE", "T729Intent"],
  "anomalies": ["stack_growth_loop", "unbounded_tensor"]
}
```

---

## 🔁 Tier Promotion Rules

Axion AI uses entropy thresholds to determine when to promote or demote logic tiers:

| Entropy Level | Symbolic Tier | Action                     |
|---------------|----------------|-----------------------------|
| 0.0–0.2       | T81            | No promotion                |
| 0.2–0.6       | T243           | Promote if recursive        |
| >0.6          | T729           | Promote for AI macro use    |

Demotion occurs if entropy **drops below tier threshold** for more than `n=3` cycles or via explicit AI rollback commands.

---

## 🧠 Common Entropy Patterns

| Pattern             | Detected In         | Entropy Level | Symbolic Insight                          |
|---------------------|----------------------|----------------|--------------------------------------------|
| `FIB_RECURSE`       | Recursion examples   | Medium (0.3–0.6) | Stable but depth-sensitive recursion       |
| `INTENT_OVERFLOW`   | AI macro misuse      | High (>0.75)    | Possible overuse of AI dispatch tensors    |
| `UNROLLED_LOOP`     | Flattened iterations | Low (<0.15)     | AI may optimize to eliminate recursion     |
| `HOLO_FFT`          | Tensor spectral ops  | High (>0.8)     | Expected complexity from holomorphic ops   |

---

## 📎 Entropy Tags in `.hvm`

During disassembly, entropy markers may appear:

```hvm
@entropy:0.71
OP_T729_INTENT
@entropy:0.22
OP_T243_STATE_ADV
```

These tags help guide Axion’s NLP commands, rollback thresholds, and optimization pathways.

---

## 🧪 Developer Tools

- `logviewer.cweb` — Live entropy visualizer and filter
- `recursive_tier_execution.cweb` — Entropy-controlled stack tiering
- `axion-ai.cweb` — Optimization engine reading entropy tags

Use these tools to monitor how symbolic entropy affects execution flow, AI decisions, and performance.

---

## 🧠 Axion Optimization Modes

| Mode         | Behavior Description                              |
|--------------|----------------------------------------------------|
| `stable`     | Minimal promotion, deterministic recursion         |
| `adaptive`   | Responsive to entropy curves (default)             |
| `aggressive` | Prioritize T729 ops, even on medium entropy levels |

---

## 🧾 Recommended Practice

- Always include entropy logs when analyzing recursion.
- Review `.entropy.json` alongside `.hvm` output.
- Use `snapshot`, `rollback`, and `optimize` AI NLP commands based on entropy deltas.

---

> "Entropy isn't chaos—it's just a signal we're not done optimizing."  — `manifesto.cweb`
