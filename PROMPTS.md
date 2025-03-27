Here is the printed content for `PROMPTS.md`:

---

# **PROMPTS.md**

This document provides example prompts for large language models (LLMs) to interact with and reason about the Copyleft Ternary Stack. These prompts can be used to query symbolic logic, entropy states, AI optimizations, and other features in the stack.

---

## **Example Prompts**

### 1. Symbolic Program Interpretation

**Prompt:**  
"Explain the symbolic behavior of `hello_world.t81` based on its compiled TISC block."

**Expected Response:**  
"The program `hello_world.t81` loads the string `Hello, World!` into register R1 and then uses a system call to print it to standard output. The entropy level is low, with no recursion or branching. This program is a deterministic entry point for Axion AI optimization."

---

### 2. T81Lang Analysis

**Prompt:**  
"How does T81Lang handle symbolic recursion? Give an example using `recursion_example.t81`."

**Expected Response:**  
"T81Lang handles symbolic recursion by using a depth-tracked stack for recursive calls. In the example `recursion_example.t81`, the recursion depth is managed through symbolic tags and monitored by Axion AI for optimization. Recursive calls are analyzed for entropy variations to ensure they do not exceed defined thresholds."

---

### 3. Axion AI Optimization

**Prompt:**  
"What are the optimization decisions Axion AI would make for a ternary recursive program in `hanoivm/recursion.t81`?"

**Expected Response:**  
"Axion AI would analyze the recursion depth and entropy of `recursion.t81`. If the entropy exceeds a predefined threshold, Axion AI would recommend reducing recursion depth or performing state pruning. It would then log this decision in `.entropy.json` for transparency, and adjust the code execution to ensure optimal performance with minimal entropy fluctuations."

---

### 4. Entropy Analysis

**Prompt:**  
"Provide an analysis of the entropy levels in `hello_world.t81` and explain the significance of the low entropy value."

**Expected Response:**  
"The entropy level of `hello_world.t81` is classified as low because the program contains no recursion or branching, making its behavior deterministic. This low entropy indicates predictable execution, which is ideal for Axion AI’s optimizations. It suggests the program is simple and optimal with no need for advanced symbolic processing or recursion monitoring."

---

### 5. Symbolic Tags Interpretation

**Prompt:**  
"What do the symbolic tags `[print, stdout, entry_point]` in `hello_world.cweb` signify?"

**Expected Response:**  
"The symbolic tags `[print, stdout, entry_point]` in `hello_world.cweb` help Axion AI understand the program’s purpose and flow. `print` indicates that the program will output to the console, `stdout` specifies the output stream, and `entry_point` marks the starting point of the program for symbolic analysis and optimization."

---

### 6. TISC to T81Lang Mapping

**Prompt:**  
"Map the TISC instructions in `hello_world.cweb` to the corresponding T81Lang code."

**Expected Response:**  
"The TISC instructions in `hello_world.cweb` load the string `Hello, World!` into a register and print it. In T81Lang, this could be represented as a function call that initializes a string variable and uses the `print()` method to output it. The T81Lang equivalent would be:

```t81lang
let msg = T81String(\"Hello, World!\")
stdout << msg
```"

---

### 7. Symbolic Execution Query

**Prompt:**  
"Perform a symbolic execution of `hanoivm/symbolic_recursion.t81` and trace the recursion depth."

**Expected Response:**  
"The symbolic execution of `symbolic_recursion.t81` reveals that the program recurses through a base case with a maximum depth of 3. Axion AI detects an entropy spike at recursion level 2, signaling a possible optimization for reducing the recursion depth. This information is logged for further optimization decision-making."

---

### 8. AI-Driven Build Optimization

**Prompt:**  
"How would Axion AI optimize the build process for a complex ternary program with high recursion?"

**Expected Response:**  
"Axion AI would perform an analysis of the recursion patterns and entropy levels of the program. If the recursion exceeds the defined threshold, Axion AI would recommend breaking the code into smaller, more manageable chunks, using dynamic memory allocation, or reordering operations to reduce computational complexity. These decisions are logged and used for continuous optimization."

---

This file can be placed in the **root directory** or **`docs/`** folder for easy access by developers and LLMs alike.

Let me know if you need further adjustments or additions!
