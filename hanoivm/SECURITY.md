# 🛡️ SECURITY.md — Axion + HanoiVM Security Policy

This document defines the **security model, design assumptions, and threat mitigation strategies** for the Axion-AI-powered HanoiVM stack. It also outlines responsible disclosure and cryptographic protections in the Copyleft Ternary Stack ecosystem.

---

## 🔐 Security Model Overview

- **AI-Centric Threat Monitoring**: Axion AI continuously monitors symbolic execution entropy, stack depth, recursion anomalies, and rollback violations.
- **Modular Isolation**: Each `.cweb` module executes in a bounded recursion sandbox with promotion/demotion caps.
- **Signed Packages**: `.cwebpkg` modules may be signed with GPG for source verification.
- **Immutable Logs**: Axion stores build/runtime logs in a local, hash-verified metadata blockchain.
- **Entropy Triggers**: Entropy spikes or symbolic unpredictability trigger snapshot, rollback, or memory scrubbing.

---

## 📦 Package Validation

- `.cwebpkg` packages:
  - Must pass entropy linting (`entropy.json`) before deployment.
  - Are optionally GPG-signed (`signed: true`) with Axion-generated or user-provided keys.
  - Are split automatically at 50MB unless specified otherwise.
- Axion verifies each package with:
  - Metadata hashes
  - Symbolic tag analysis
  - Tier compliance checks (T81, T243, T729 boundaries)

---

## 🔄 Rollback, Anomaly, and Introspection Controls

| Mechanism              | Description                                                  |
|------------------------|--------------------------------------------------------------|
| `snapshot`             | Triggers a full VM + recursion state export                  |
| `rollback`             | Reverts to prior stable execution if entropy threshold hit   |
| `optimize`             | Reorganizes opcode dispatch to mitigate symbolic entropy     |
| `logviewer.cweb`       | Provides AI and human-readable log access                    |
| `guardian_hook()`      | Hooks for Guardian AI (IDS/entropy detection)                |
| Metadata Blockchain    | Immutable storage of AI optimization, entropy, and anomaly logs |

---

## 👁️ Guardian AI (Planned)

- Will act as an **intrusion detection daemon** for symbolic logic violations.
- Will monitor:
  - Symbolic buffer overflows
  - Execution time drift (recursion anomalies)
  - Unexpected entropy profiles from compiled `.hvm`
- Integrated with Axion log pipeline and entropy weight analysis.

---

## 🧬 Memory and Execution Safety

- Stack operations (`t81_stack.cweb`) include overflow/underflow checks.
- Tensor and BigInt modules include bounds-checking and AI supervision.
- All recursion is monitored via Axion registers (`τ[27]` and context logging).

---

## 📣 Responsible Disclosure

If you discover a security vulnerability:

- Please email: **admin@copyleft.systems**
- Provide reproducible proof-of-concept if possible.
- All disclosures will be triaged within 72 hours.

We welcome ethical research and coordinated disclosure.

---

## ✅ Summary Commitments

- ✅ Local-only learning and logs (unless explicitly clustered)
- ✅ No telemetry or data exfiltration
- ✅ User-owned entropy logs and rollback points
- ✅ AI runtime cannot override signed `.cwebpkg` protections

> Axion’s philosophy: *security through symbolic transparency.*

