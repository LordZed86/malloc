# 📚 Malloc/Calloc

Author: Lore, Joe, Kellen  
Course: CS 301 — Foundations of Computer Science  
Instructor: Allison Obourn  
Malloc Project (C programming language)  
Date: March 2026  

---

## 🎯 Overview

---

## 🏗️ Internal Design & algorithms
<!-- Spec requires: "A brief description of how your allocation system works
internally and any relevant algorithms not in this spec." -->
---

## 👥 Team Responsabilities
<!-- Spec requires: "Who was responsible for which part(s) of the work." -->
---

## 📁 File Structure

```text
cs301project/
 ├── memalloc.c       # Core allocation functions (malloc301, free301, etc.)
 ├── memalloc.h
 ├── memops.c         # Bulk memory operations (memcpy301, memset301, etc.)
 ├── memops.h
 ├── memdebug.c       # Debugging utilities (print_block, print_blocks)
 ├── memdebug.h
 ├── memimpl.h        # Internal structs/macros
 ├── test.c           # Testing program
 ├── Makefile         
 └── README.md
```

---

## ⚙️ How to Build and Run

```bash
make          # Build everything
make test     # Build test program
make clean    # Remove .o files and executables
make dist     # Create cs301project.tar.gz for submission
```
<!-- could add memory leak tests or others but these are the required for now -->
---

## 🔬 Testing
<!-- Spec requires: "A brief description of the testing you have performed,
the behavior of your test program, etc." -->
---

## 📦 Resources Used
<!-- Spec requires: "A brief comment about what resources you used." -->
---

## 🪞 Reflection
<!-- Spec requires: "A very brief reflection: What parts were hardest?
What parts were fun or interesting?" -->
---

## 🧱 Project tasklist (constraints and features)

### Constraints

- Cannot call `malloc`, `calloc`, `realloc`, or `free` anywhere in your code.
- Cannot use C++.
- Block list must be implemented in-place inside the managed memory pool.
- Each list node header must be exactly 4 bytes.
- Memory must be allocated in multiples of 4 bytes.
- Heap size assumed to be no more than 256MB (2²⁸ bytes).
- Only allowed libraries: `stdio`, `stdlib`, `stdbool`, `string`, `ctype`, `time`, `unistd`.
- No `.c` file may include another `.c` file.
- All globals/functions not in a `.h` file must be declared `static`.
- Must produce zero errors or warnings under `gcc -Wall`.

### Features

- `init301(void* block, int size)` — initialize the memory pool.
- `malloc301(int size)` — first-fit allocation, rounded to multiples of 4.
- `calloc301(int num, int size)` — allocate and zero-initialize.
- `realloc301` — reallocate a block.
- `free301(void* p)` — free and coalesce neighboring free blocks (up to 3-way merge).
- `sizeof301(void* p)` — return allocated size of a block.
- `memcpy301` — copy non-overlapping memory regions.
- `memset301` — set bytes to a value.
- `memzero301` — zero out bytes.
- `print_block(void* block)` — print one block's debug info.
- `print_blocks(void)` — print all blocks numbered with 2-digit right-aligned fields.
- `Makefile` with targets: `all`, `test`, `dist`, `clean`, plus per-file `.o` targets with proper dependencies.
- `test.c` testing program exercising all functions non-trivially.
- `README` covering authorship, design, testing, resources, and reflection.
- GitHub repo with regular, meaningful commits throughout development.
