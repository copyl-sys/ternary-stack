# 🧠 Looking Glass JSON Schema — Ternary State Visualization

This document defines the JSON schema exported by Axion/HanoiVM and consumed by `Project Looking Glass`, the 3D visualization layer for the Copyleft Ternary Stack. It allows interactive inspection of symbolic entropy zones, recursion patterns, and AI behavior over time.

---

## 🎯 Purpose

Looking Glass uses structured runtime metadata to render:
- Ternary recursion flows (T81, T243, T729)
- Symbolic operand propagation
- Entropy hotspots (color-coded by intensity)
- AI triggers and rollback events

---

## 📁 Example Export

```json
{
  "session": "abc123",
  "timestamp": "2025-03-27T20:12:00Z",
  "depth": 9,
  "layer": "T243",
  "opcode": "TISC_243MUL",
  "operand": {
    "type": "T81Float",
    "symbol": "β",
    "value": "00T12F"
  },
  "entropy": 0.78,
  "ai_action": "recompile",
  "visual_hint": {
    "color": "#FF6600",
    "size": 3.2,
    "glow": true
  }
}
```

---

## 🔖 JSON Schema Fields

| Field         | Type       | Description |
|---------------|------------|-------------|
| `session`     | `string`   | Unique session ID |
| `timestamp`   | `string`   | ISO UTC timestamp |
| `depth`       | `int`      | VM recursion depth |
| `layer`       | `string`   | Logic layer: `T81`, `T243`, or `T729` |
| `opcode`      | `string`   | Executed opcode mnemonic |
| `operand`     | `object`   | Symbolic operand metadata (type, tag, value) |
| `entropy`     | `float`    | Entropy score (0.0–1.0) |
| `ai_action`   | `string`   | Axion behavior (e.g., optimize, recompile, rollback) |
| `visual_hint` | `object`   | Optional rendering style (color, size, glow) |

---

## 🖼️ Visual Mapping Guidelines

| Field         | Render Behavior |
|---------------|------------------|
| `entropy`     | Color gradient (e.g. blue → orange → red) |
| `depth`       | Z-axis or recursion spiral height |
| `ai_action`   | Timeline glyph / animation overlay |
| `symbol`      | Hoverable tag with semantic context |
| `layer`       | Visual grouping by VM tier (T81/T243/T729) |

---

## 🔁 Source Modules Exporting Schema

- `hanoivm_vm.cweb` → injects `depth`, `opcode`, `layer`, `operand`
- `axion-ai.cweb` → injects `entropy`, `ai_action`, and `visual_hint`
- `disassembler.cweb` → optional symbolic decoding + operand type hint

---

## 📡 Transport + Storage

- Exported in real time via IPC or socket
- Archived as `.json` in `/logs/lookingglass/SESSION_ID.json`
- Optional format: `.lgx` (compressed binary or streamable format)

---

## 🧪 Validation

- JSON schema should be testable with automated snapshot matchers
- Log files may be replayed into Looking Glass for debugging or demo mode

---

## 🛣️ Future Enhancements

- Support nested operand trees for symbolic logic chaining
- GPU acceleration hints (per object visual weight)
- AI-generated annotations for anomaly classification
- Event timelines with reversible playback

---

Last updated: March 2025
Maintained by: `copyleft systems`
Mode: `./night_shift.sh -sync -copyleftsystems`

