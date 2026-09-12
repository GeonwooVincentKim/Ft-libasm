# Test Results

## TASK 00–08 — PASS

## TASK 09 — ABI / calling convention / errno audit

Date: 2026-09-12
Environment: Ubuntu 24.04.4 LTS x86_64, NASM 2.16.01, gcc 13.3.0
Test scope: static register/stack/relocation review; runtime callee-saved probe; errno paths
Result: PASS

Evidence:
- No function writes rbx/rbp/r12-r15.
- Runtime ABI harness: magic values in rbx/rbp/r12-r15 survived ft_strlen, ft_strcpy, ft_strcmp, failing ft_write, failing ft_read, and ft_strdup.
- External libc calls use R_X86_64_PLT32 (`__errno_location`, `malloc`).
- Same-archive `ft_strlen` call is R_X86_64_PC32 (resolved inside the PIE executable).
- write/read: `push` before CALL keeps 16-byte alignment; errno stored as 32-bit int; return -1.
- strdup: `push rdi` aligns stack before ft_strlen and malloc.
- testhook remains PIE; Makefile has no `-no-pie`.

Failure explanation: none
