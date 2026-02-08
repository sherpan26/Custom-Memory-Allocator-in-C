# MyMalloc — Custom Memory Allocator in C

A custom memory allocator that mimics `malloc()` / `free()` on top of a fixed-size heap.
Implements alignment, block metadata, reuse, and safety checks to catch invalid frees.

## Highlights
- Fixed-size heap (512 bytes)
- 8-byte alignment
- Per-block metadata tracking
- Block splitting and coalescing (if enabled/implemented)
- Error detection for invalid pointers / double frees
- Debug-friendly reporting with file/line macros

## Project Structure
- `src/mymalloc.c`, `include/mymalloc.h` — allocator implementation + public API
- `tests/memgrind.c` — benchmark driver (runs multiple workloads, reports avg runtime)
- `tests/testA.c` – `tests/testE.c` — targeted tests for allocation/free patterns
- `makefile` — build + test automation

## Test Workloads (Memgrind)
- **testA:** allocate and immediately free small blocks in a loop
- **testB:** allocate many small blocks, then free all
- **testC:** randomized alloc/free pattern to simulate fragmentation
- **testD:** larger-block stress to exercise splitting/coalescing behavior
- **testE:** optional custom stress test

## Build + Run
```bash
make
./memgrind

