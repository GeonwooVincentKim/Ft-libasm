# Test Results

## TASK 16 — Version 6.0

Date: 2026-10-31
Environment: Ubuntu 24.04 LTS x86_64, NASM 2.16.01, gcc 13.3.0, Valgrind 3.22.0

### Build

Command: `make fclean && make && make test`
Result: PASS

Command: `make re`
Result: PASS. Incremental: touching `ft_strlen.s` rebuilds only that object then `ar`.

### testhook

Command: `./testhook` (twice after clean rebuild and after `make re`)
Result: PASS — `72 passed, 0 failed`

Existing six-function cases still PASS.
ft_calloc v6.0 cases:
- calloc(1,1) / calloc(10,int) zeros, writable, free, vs libc
- zero nmemb/size vs libc nullness
- calloc(0, SIZE_MAX) no crash (freeable)
- overflow SIZE_MAX*2, 2*SIZE_MAX, (SIZE_MAX/2+1)*2, (SIZE_MAX/2+1)*3, large*large → NULL + ENOMEM
- below-overflow 256*256 zeros
- calloc(4096,1) zeros

### Valgrind

Command: `valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=42 ./testhook`
Result: PASS
- 72 passed, 0 failed
- 19 allocs / 19 frees, 0 bytes in use
- ERROR SUMMARY: 0 errors from 0 contexts

### Symbols

`nm libasm.a`: T ft_strlen, ft_strcpy, ft_strcmp, ft_write, ft_read, ft_strdup, ft_calloc
`readelf -r ft_calloc.o`: malloc, __errno_location (not calloc)
`objdump -d ft_calloc.o`: mul / test rdx / jnz overflow before call malloc
