# 📚 Malloc/Calloc

Author: Lore, Joe, Kellen  
Course: CS 301 - Foundations of Computer Science  
Instructor: Allison Obourn  
Malloc Project (C programming language)  
Date: March 2026  

---

## 🎯 Overview

This project is a custom memory allocator written in C. It implements core functions similar `<stdlib.h>`’s `malloc`, `calloc`, and `free`. The allocator manages a single block of memory using a linked list of 4-byte bit-packed node header blocks. This library supports allocation, deallocation, and coalescing of free adjacent blocks.  

---

## 🏗️ Internal Design & Algorithms

### Memory Layout

This project manages a large block of memory passed in by the user through `init301`. This block is managed using a list header of 4-bytes, bit packed into the node. These nodes sit directly before the memory chunk they describe.

```text
|[node 4B]|[memory chunk]|[node 4B]|[memory chunk]|[node 4B]|[memory chunk]|
```

### Node Struct

Every header node is exactly 4 bytes. These are packed as follows:

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
When a free block is larger than needed, it is split into two blocks - one allocated to the request and one is left free. The leftover must be larger than NODE_SIZE (4 Bytes) to be worth splitting.

**Coalescing**  
If a block is freed, all free neighboring blocks are merged into a single larger block to prevent fragmentation. A maximum of 3 blocks can be merged at once - the previous block, the freed block, and the next block.

**Bit-Packing and Offset Storage**  
Block sizes are stored as 4-byte units rather than raw bytes using bit shifts:

- Storing: `size >> 2` (divide by 4)
- Retrieving: `size << 2` (multiply by 4)
- Navigating: `current + NODE_SIZE + (current->size << 2)`

**In-Place Linked List**  
Nodes are stored directly inside the memory block with no separate allocation. The next node is found mathematically instead of using pointers, this keeps each node exactly 4 bytes.

**Byte-Level Memory Operations**  
`memcpy301`, `memset301`, and `memzero301` cast pointers to `char*` to manipulate memory one byte at a time, since `void*` mathematically moves in 4-byte increments.

---

## 👥 Team Responsibilities

### Milestone 1

**Lore** - Led implementation of `malloc301` and `memdebug`, including first-fit allocation strategy, block splitting logic, and offset bit shift arithmetic. Contributed to overall system design and debugging.

**Joe** — Implemented `calloc301`, `memzero301`, and `get_heap_head`. Contributed to initial stub of `free301`. Also served as emotional support for the team.

**Kellen** - Designed and implemented `memimpl.h` struct layout, bit-packing system, and offset storage strategy. Implemented `init301` and contributed to `malloc301`. Provided architectural guidance on how malloc works internally to get the team up to speed.

### Milestone 2

**Lore** - Implemented `memcpy301`, `realloc301` and `sizeof301`. Contributed to `test.c` including test cases and CHECK macro for pass/fail validation.

**Joe** - Implemented `memzero301` and contributed to `test.c` including calloc and memzero, memcpy, and free test cases.

**Kellen** - Implemented `memset301` and `free301` including block coalescing logic. Contributed to `test.c` including free and memset test cases.

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

All tests are located in `test.c` and can be run with:

```bash
make test
./test
```

### Test Cases

Each function has its own test that prints expected vs. actual values, and reports if it passed or failed. Some of the tests are redundant as tests were generally written as functions were completed to test functionality.

- **`init_test`** - verifies initial heap state has one free block of correct size
- **`malloc_test`** - tests basic allocation, size rounding to multiples of 4, multiple allocations, invalid inputs (0, negative, too large)
- **`calloc_test`** - tests allocation of zeroed memory, verifies every byte is zero, tests invalid inputs
- **`memset_test`** - tests setting bytes to a value, verifies every byte is correct, tests boundary values (0, 255), tests invalid inputs.
  - Since `memzero301` simply calls `memset301` this test also tests `memzero301`
- **`free_test`** - allocates three blocks (100B, 200B, 300B) and tests freeing in various orders to verify coalescing behavior. Tests forward coalescing by freeing the middle block then the next block and verifying they merge into a single free block. Tests backward coalescing by freeing all remaining blocks and verifying the entire heap returns to a single free block. Verifies freed space can be reused by allocating into merged blocks. Also tests that `free301(NULL)` is a no-op and does not crash.
- **`memcpy_test`** -  allocates 2 blocks setting the value of A to 1's and B to 2's then tests `memcpy301` to copy the value from block A to block B.
- **`realloc_test`** - `realloc301` is implemented but not covered by the test suite, since the spec didn’t define its expected behavior.

### Memory Leak Testing

```bash
make valgrind    # Linux/WSL
make mac_leaks   # Mac
```

### Testing Strategy

- Tests are independent - each resets the heap with `init301` before running
- This way they can be commented out individually without affecting other tests.

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
- [Mac OSX Leaks Tool](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/ManagingMemory/Articles/FindingLeaks.html) - memory leak testing on Mac

---

## 🪞 Reflection

**Lore** - I had a hard time wrapping my head around the bit manipulation, once I got through that I found the realloc and memops stuff a bit fun.

**Joe** -  I really struggled with the initial understanding of getting malloc working and really just how the bit packing and manipulation all worked together but once that kind of stuff was figured out and laid out I started to feel better about the memops and testing suite because I just had a little better understanding of what it was I needed to be doing. Overall, this was definitely the toughest project of the quarter for me so I'm happy to see the light at the end of the tunnel.

**Kellen** - The most challenging part for me was wrapping my head around `malloc301` and the overall node structure. Understanding how a linked list could live inside the memory it was managing, with no separate allocation, took a while to click. The bit-packing was also initially confusing, cramming size, free, and last flags into exactly 4 bytes felt abstract at first.

Once I was able to visualize what was actually happening in memory - nodes sitting directly in front of the blocks they describe, the list growing and splitting as allocations came in, everything started to make sense. At that point the bit shifting arithmetic and offset storage felt natural rather than arbitrary. Seeing `print_blocks` output the heap state in real time was the moment it all came together.

Overall it ended up being one of the more interesting and challenging projects I've worked on. Low level memory management sounds intimidating but once you understand the mental model it's surprisingly elegant.
