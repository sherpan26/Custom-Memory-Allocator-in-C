# Custom-Memory-Allocator-in-C
# MyMalloc: Custom Memory Allocator in C

This project implements a custom memory allocator in C that mimics the behavior of `malloc()` and `free()` using a fixed-size memory block. It includes robust error handling, alignment guarantees, and support for common allocation patterns. 

## 📁 Project Structure

- `mymalloc.c` / `mymalloc.h`: Core implementation of the memory allocator.
- `memgrind.c`: Benchmark driver that runs 5 different test cases and records average execution time.
- `testA.c` – `testD.c`: Individual test programs for various allocation and deallocation scenarios.
- `makefile`: Automates compilation of the project and test cases.

## 🛠️ Features

- **512-byte fixed memory region**
- **8-byte memory alignment**
- **Metadata tracking for each block**
- **Dynamic block splitting and coalescing (optional)**
- **Error reporting with source location (via macros)**

## 🧪 Tests

The following tests are implemented:

- `testA`: Allocates and immediately frees 1-byte blocks in a loop.
- `testB`: Allocates 120 1-byte blocks, then frees them all.
- `testC`: Random allocation/deallocation until 120 allocations complete.
- `testD`: Stress test with large blocks and fragmentation.
- `testE`: Custom stress test slot (optional to implement).

Run all tests and measure average time:

```bash
make
./memgrind
