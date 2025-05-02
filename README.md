# 🍒 cherry-v

A lightweight RISC-V translator written in C++.

Cherry-picked bits and branches, reimagining the RISC-V instruction set with simplicity and clarity in mind.

Originally made with Kotlin a long time ago [(check here)](https://github.com/cheporte/riscv-translator), this project aims to refine and improve what was done before.
And refresh some memory as well ;>

---

## ✨ Overview

`cherry-v` is a small translator for RISC-V assembly, aiming to convert `.s` source files into machine-readable binary output. It's written in modern C++ with a modular and clean design, using CMake as its build system.

This project is both a learning journey and a tool-in-progress.

---

## 📁 Project Structure

```
cherry-v/
├── include/                        # Header files
├── src/                            # Source files
├── test/                           # Sample assembly programs
├── build/                          # CMake build output
├── data/                           # (Optional) future ISA specs
├── CMakeLists.txt                  # Build configuration
└── README.md                       # This file!
```

---

## 🚀 Build Instructions

### Using CMake:

```bash
mkdir build
cd build
cmake ..
make
```
Your executable will be built as `./cherry-v`.

## 🛠 Requirements
- C++17 or later
- CMake 3.10+
- A basic terminal and desire to tinker 🍃

## 📝 License
MIT License. Use it, break it, improve it, share it. ❤️

## 📜 A Note from the Author

This project was born out of curiosity, burnout, and a little rebellion against bloated tools.
It's not perfect—but neither are cherry blossoms. That's why they’re beautiful.