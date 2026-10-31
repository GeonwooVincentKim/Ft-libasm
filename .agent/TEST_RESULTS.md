# Test Results

## TASK 17 — ft_calloc v6.0 test matrix

Date: 2026-10-31
Environment: Ubuntu 24.04 LTS x86_64, NASM 2.16.01, gcc 13.3.0, Valgrind 3.22.0
Subject: Version 6.0

### Build

Command: `make fclean && make && make test`
Result: PASS

### testhook

Command: `./testhook` (twice)
Result: PASS — `96 passed, 0 failed`

Existing six-function cases still PASS.

ft_calloc focused matrix:
- (1,1), (1,64), (64,1), (4,int), (16,long), (10,int), moderate 512, 256*256, 4096
- zeros, writable, free, libc memcmp where size is valid
- (0,0), (0,1), (1,0) nullness+errno vs libc
- (0, SIZE_MAX) no crash
- overflow: SIZE_MAX*2, 2*SIZE_MAX, SIZE_MAX*SIZE_MAX, (SIZE_MAX/2+1)*2, 2*(SIZE_MAX/2+1), plus prior cases
- overflow errno ENOMEM

### Valgrind

Command: `valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=42 ./testhook`
Result: PASS
- 96 passed, 0 failed
- 29 allocs / 29 frees, 0 bytes in use
- ERROR SUMMARY: 0 errors from 0 contexts
