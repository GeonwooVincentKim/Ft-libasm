# Test Results

## TASK 00–14 — PASS (pre-calloc)

Previous: testhook 44 passed, 0 failed. ITa PASS. ITb PASS.

## TASK 15 — ft_calloc

Date: 2026-10-10
Environment: Ubuntu 24.04 LTS x86_64, NASM 2.16.01, gcc 13.3.0, Valgrind 3.22.0

### Build

Command: `make fclean && make && make test`
Result: PASS
- `nasm -f elf64` on seven `.s` files including `ft_calloc.s`
- `libasm.a` contains `T ft_calloc`
- testhook PIE link (`gcc -Wall -Wextra -Werror main.c -L. -lasm`)
- no `-no-pie`

Command: `make re`
Result: PASS. Incremental: touching `ft_calloc.s` rebuilds only that object then relinks the archive.

### testhook

Command: `./testhook` (twice)
Scope: existing 44 cases + 23 ft_calloc cases
Result: PASS — `67 passed, 0 failed` (both runs)

Existing tests: all still PASS (strlen/strcpy/strcmp/write/read/strdup).
ft_calloc tests:
- calloc(1,1) alloc / zero / writable / free
- calloc(10, sizeof(int)) alloc / zeros / matches libc / writable / free
- calloc(0,0), (0,1), (1,0) nullness + errno vs libc
- calloc(0, SIZE_MAX) non-NULL unique block (product 0), errno unchanged
- overflow SIZE_MAX*2, 2*SIZE_MAX, (SIZE_MAX/2+1)*3 → NULL + ENOMEM
- calloc(4096,1) zeros

### Valgrind

Command: `valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=42 ./testhook`
Result: PASS
- 67 passed, 0 failed
- HEAP: 18 allocs, 18 frees, 0 bytes in use
- `All heap blocks were freed -- no leaks are possible`
- `ERROR SUMMARY: 0 errors from 0 contexts`
- Invalid-fd warnings come from existing write/read EBADF tests, not leaks

### Symbols / disassembly

`nm libasm.a`: `T ft_calloc` plus the original six T symbols.
`objdump -d ft_calloc.o`: `mul %rsi`, `test %rdx,%rdx`, `call malloc@plt`, byte zero loop, overflow `movl $0xc,(%rax)` then `xor %rax,%rax`.

### Notes

- Host glibc calloc(0,*) returns a freeable pointer and does not touch errno; overflow returns NULL with ENOMEM=12.
- libc calloc(0, SIZE_MAX) is not compared under Valgrind (fishy-size intercept). ft_calloc implements 0 * SIZE_MAX as malloc(0).
- Overflow errno is asserted on ft_calloc itself (ENOMEM). libc-intercepted calloc under Valgrind is not used as the errno oracle.
