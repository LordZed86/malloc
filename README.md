# 📚 Malloc/Calloc

Author: Lore, Joe, Kellen  
Course: CS 301 — Foundations of Computer Science  
Instructor: Allison Obourn  
Malloc Project (C programming language)  
Date: March 2026  

---

## 🎯 Overview

---

## 🧠 Key Features

---

## 📁 File Structure

//old file structure used lmao

```text
MyMDb/
 ├── devcontainer/           
 │   └── devcontainer.json    # Defines environment setup for cloud development
 ├── img/                    
 │   ├── bacon_filmography.png      # Example screenshot: filmography
 │   ├── bacon_load.png             # Example screenshot: initial load
 │   └── bacon_overlap.png          # Example screenshot: overlap search
 ├── node_modules/            # Installed dependencies (npm, do not edit)
 │   └── ...                  
 ├── public/                  # Static assets served by Express
 │   ├── mymdb.css            # Stylesheet
 │   ├── mymdb.html           # HTML
 │   └── mymdb.js             # Client-side JavaScript
 ├── mymdb-service.js         # Node.js + Express backend service
 ├── package-lock.json        # Auto-generated dependency lockfile
 ├── package.json             # Project metadata, dependencies, start/dev scripts
 └── README.md                # Documentation and debugging notes
```

### Image credit

---

## ⚙️ How to run

---

## 🌐 Service API (query parameters)

---

## 🧩 UI behavior (client)

---

## 🛠️ Debugging Notes

---

## 🖼️ Screenshots

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