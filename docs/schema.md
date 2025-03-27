# `.cweb` Schema

This document defines the schema for `.cweb` files used in the Copyleft Ternary Stack. `.cweb` files are used for symbolic modular packaging and AI-driven builds.

---

## Header Fields

- `name` (string): The name of the package or module.
- `version` (semver): The version identifier for the package/module.
- `entropy` (string): The symbolic entropy level of the package. Possible values are:
  - `low`: No recursive depth, deterministic.
  - `moderate`: Some recursion or symbolic variation.
  - `high`: High recursion, symbolic complexity, or randomness.
- `symbolic_tags` (list): A list of AI-readable tags for symbolic analysis (e.g., `[print, recursion, entropy]`).

## Sections

### `--- BEGIN TISC ---`
Defines the raw TISC assembly or low-level ternary operations.

### `--- END TISC ---`
Denotes the end of the TISC block. This is where the ternary instructions stop.

### AI Metadata Section (Optional)
- `ai_guidance` (string): An AI-readable hint about the symbolic behavior of the code.
- `warnings` (list): Any known issues, or AI warnings, e.g., recursion depth exceeds threshold.
- `symbolic_tags` (list): Repeated for clarity and guidance.

Example `.cweb`:
```cweb
@cweb_package
name: hello_world
version: 0.1.0
entropy: low
symbolic_tags: [print, stdout, entry_point]

--- BEGIN TISC ---
LOAD R1, "Hello, World!"
SYSCALL PRINT, R1
RET
--- END TISC ---

// AI Notes:
// - Symbolic entry point detected.
// - No recursion or branching.
// - Entropy level within baseline threshold.
// - Suitable for Axion AI optimization logging.
```

## Usage

`.cweb` files should be placed under the `src/` or `examples/` directory. They can be compiled using `t81_compile.py` and interpreted by HanoiVM. AI-assisted optimizations are logged in `.entropy.json` and `.ast.json` files for further symbolic analysis.

**End of Schema.**
