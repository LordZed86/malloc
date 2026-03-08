# 📚 Malloc/Calloc

Author: Lore, Joe, Kellen  
Course: CS 301 - Foundations of Computer Science  
Instructor: Allison Obourn  
Malloc Project (C programming language)  
Date: March 2026  

---

## 🎯 Overview
This project is a custom memory allocator written in C, it implements core  
functions similar `<stdlib>`'s malloc/calloc and free. this allocator manages  
a single block of memory using a linked list of 4-byte bit-packed node header  
blocks. This library supports allocation, deallocation, and coalescing of free  
adjacent blocks.  

---

## 🏗️ Internal Design & algorithms
<!-- Spec requires: "A brief description of how your allocation system works
internally and any relevant algorithms not in this spec." -->
---

## 👥 Team Responsabilities
<!-- Spec requires: "Who was responsible for which part(s) of the work." 
 running list based on who contributed the most to each section not necessarily by physically tuyping and committing but by overall contribution intelectually or conceptually -->
 ### Milestone 1

**Lore** - `malloc301` including first-fit strategy, block splitting, 
and offset bit shift arithmetic

**Joe** - `calloc301`, `free301` including block coalescing

**Kellen** - `memimpl.h` struct design, bit-packing and offset storage system,
init301

### Milestone 2

**Lore** -

**Joe** - 

**Kellen** -

### Milestone 3

**Lore** -

**Joe** - 

**Kellen** -

---

## 📁 File Structure

```text
cs301project/
 ├-- memalloc.c       # Core allocation functions (malloc301, free301, etc.)
 ├-- memalloc.h
 ├-- memops.c         # Bulk memory operations (memcpy301, memset301, etc.)
 ├-- memops.h
 ├-- memdebug.c       # Debugging utilities (print_block, print_blocks)
 ├-- memdebug.h
 ├-- memimpl.h        # Internal structs/macros
 ├-- test.c           # Testing program
 ├-- Makefile         
 └-- README.md
```

---

## ⚙️ How to Build and Run

### Build

```bash
make          # Build everything
make clean    # Remove .o files and executables
make dist     # Create cs301project.tar.gz for submission
```

### Run
```bash
./test        # Runs the test program
```

### Memory Leak Detection

```bash
make valgrind   # Linux/WSL - runs test with full leak checking
make mac_leaks  # Mac - runs test with macOS leaks tool
```

### Requirements

- GCC compiler
- Mac: macOS leaks tool (built in)
- Linux/WSL: Valgrind (`sudo apt install valgrind`)
- Windows: Use WSL or SSH into a Linux server.  

---

## 🔬 Testing
<!-- Spec requires: "A brief description of the testing you have performed,
the behavior of your test program, etc." -->
---

## 📦 Resources Used
- Course slides and lecture notes
- Assignment specification
- [C Documentation - cppreference](https://en.cppreference.com/index.html) - general C language reference
- [Bit Fields in C - cppreference](https://en.cppreference.com/w/c/language/bit_field) - declaring and using bit fields in structs
- [Bit Shifting in C - cppreference](https://en.cppreference.com/w/c/language/operator_arithmetic) - bit shift operators
- [Bit Twiddling Hacks - Stanford](https://graphics.stanford.edu/~seander/bithacks.html) - bit manipulation reference and code snippets
- [First-Fit Memory Allocation - Wikipedia](https://en.wikipedia.org/wiki/First-fit_bin_packing) - first-fit allocation algorithm
- [Memory Alignment and Padding - Wikipedia](https://en.wikipedia.org/wiki/Data_structure_alignment) - data alignment and padding reference
- [Valgrind Documentation](https://valgrind.org/docs/manual/manual.html) - memory leak testing on Linux/WSL
- [Mac OSX Leaks Tool](https://leopard-adc.pepas.com/documentation/Darwin/Reference/ManPages/index.html) - memory leak testing on Mac
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

- `init301(void* block, int size)` - initialize the memory pool.
- `malloc301(int size)` - first-fit allocation, rounded to multiples of 4.
- `calloc301(int num, int size)` - allocate and zero-initialize.
- `realloc301` - reallocate a block.
- `free301(void* p)` - free and coalesce neighboring free blocks (up to 3-way merge).
- `sizeof301(void* p)` - return allocated size of a block.
- `memcpy301` - copy non-overlapping memory regions.
- `memset301` - set bytes to a value.
- `memzero301` - zero out bytes.
- `print_block(void* block)` - print one block's debug info.
- `print_blocks(void)` - print all blocks numbered with 2-digit right-aligned fields.
- `Makefile` with targets: `all`, `test`, `dist`, `clean`, plus per-file `.o` targets with proper dependencies.
- `test.c` testing program exercising all functions non-trivially.
- `README` covering authorship, design, testing, resources, and reflection.
- GitHub repo with regular, meaningful commits throughout development.
