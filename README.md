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
### Memory Layout
This project manages a large block of memory passed in by the user through `init301`. This block is managed using a list header of 4-bytes, bit packed into the node. These nodes sit directly before the memory chunk they describe.
```text
|[node 4B]|[memory chunk]|[node 4B]|[memory chunk]|[node 4B]|[memory chunk]|
```
### Node Struct
Every header node is exactly 4 bytes. these are packed as follows:
- 28 bits -> size -- stored in sets of 4 Bytes. (shift left 2 to get bytes)
- 1 bit -> free ----- binary marker to signify if the trailing block is in use or not. (1 = free | 0 = in-use)
- 1 bit -> last ------ binary marker to signify if the node is the last in the list.
- 2 bits -> reserved for additional binary markers, and to ensure everything stays in chunks of 4 bytes.

### Algorithms
**First-Fit**  
`malloc301` scans the memory block starting at the head and uses the first free chunk that is large enough to hold the request. The size of the request is rounded up to the nearest multiple of 4 using an ADD, SHIFT, SHIFT method `((size + 3) >> 2) << 2`.  
- ADD 3 to ensure we round up
- SHIFT right by 2 (divide by 4) to do the actual rounding, odd numbers will have the remainder dropped.
- SHIFT left by 2 (multiply by 4) to return to the original size domain.

**Block Split**  
When a free block is larger than needed, it is split into two blocks - one 
allocated to the request and one is left free. The leftover must be larger than 
NODE_SIZE (4 Bytes) to be worth splitting.

**Coalescing**  
If block is freed, all free neighboring blocks are merged into a single larger 
block to prevent fragmentation. a maximum of 3 blocks can be merged at once -
the previous block, the freed block, and the next block.

**Bit-Packing and Offset Storage**  
Block sizes are stored as 4-byte units rather than raw bytes using bit shifts:
- Storing: `size >> 2` (divide by 4)
- Retrieving: `size << 2` (multiply by 4)
- Navigating: `current + NODE_SIZE + (current->size << 2)`

**In-Place Linked List**  
Nodes are stored directly inside the memory block with no separate 
allocation. The next node is found mathematically instead of using pointers, this keeps each node exactly 4 bytes.

**Byte-Level Memory Operations**  
`memcpy301`, `memset301`, and `memzero301` cast pointers to `char*` to 
manipulate memory one byte at a time, since `void*` mathematically moves in 
4-byte increments.

---

## 👥 Team Responsabilities
<!-- Spec requires: "Who was responsible for which part(s) of the work." 
 running list based on who contributed the most to each section not necessarily by physically tuyping and committing but by overall contribution intelectually or conceptually -->
 ### Milestone 1

**Lore** - Led implementation of `malloc301` and `memdebug`, including 
first-fit allocation strategy, block splitting logic, and offset bit shift 
arithmetic. Contributed to overall system design and debugging.

**Joe** — Implemented `calloc301`, `memzero301`, and `get_heap_head`. 
Contributed to initial stub of `free301`. Also served as emotional support 
for the team and was "bullied" by Kellen.

**Kellen** - Designed and implemented `memimpl.h` struct layout, bit-packing 
system, and offset storage strategy. Implemented `init301` and contributed 
to `malloc301`. Provided architectural guidance on how malloc works 
internally to get the team up to speed. Chief bully.

### Milestone 2
<!-- initial roles randomly assigned but this will probably change as we code the rest of this project -->
**Lore** - Implemented `memcpy301`, `realloc301` and `sizeof301`. Contributed to 
`test.c` including test cases and CHECK macro for pass/fail validation.

**Joe** - Implemented `memzero301` and contributed to `test.c` 
including calloc and memzero test cases.

**Kellen** - Implemented `memset301` and `free301` including block 
coalescing logic. Contributed to `test.c` including free and memset 
test cases.

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
All tests are located in `test.c` and can be run with:

```bash
make test
./test
```

### Test Cases
Each function has its own test that print expected vs Actual values, and reports if it passed or failed. some of the tests are redundant as tests were generally written as functions were completed to test functionality.

- **`init_test`** - verifies initial heap state has one free block of correct size
- **`malloc_test`** - tests basic allocation, size rounding to multiples of 4, multiple allocations, invalid inputs (0, negative, too large)
- **`calloc_test`** - tests allocation of zeroed memory, verifies every byte is zero, tests invalid inputs
- **`memset_test`** - tests setting bytes to a value, verifies every byte is correct tests boundary values (0, 255), tests invalid inputs.  
  - since `memzero301` simply calls memzero this test also tests `memzero301`
- **`free_test`** - allocates three blocks (100B, 200B, 300B) and tests freeing in various orders to verify coalescing behavior. Tests forward coalescing by freeing the middle block then the next block and verifying they merge into a single free block. Tests backward coalescing by freeing all remaining blocks and verifying the entire heap returns to a single free block. Verifies freed space can be reused by allocating into merged blocks. Also tests that `free301(NULL)` is a no-op and does not crash.
- **`memcpy_test`** - 
- **`realloc_test`** - 

### Memory Leak Testing

```bash
make valgrind    # Linux/WSL
make mac_leaks   # Mac
```

### Testing Strategy

- Tests are independent - each resets the heap with `init301` before running
- this way they can be commented out individually without affecting other tests.

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
## TODO: write reflections on the project

**Lore** -  

**Joe** - 

**Kellen** - 


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
