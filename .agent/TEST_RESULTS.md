# Test Results

## TASK 00–04 — PASS

## TASK 05 — ft_write

Date: 2026-09-12
Environment: Ubuntu 24.04.4 LTS x86_64, NASM 2.16.01, gcc 13.3.0
Test scope: pipe write, file write, zero-length, invalid fd, errno vs libc
Result: PASS

Commands:
- `make testhook` (PIE, no -no-pie)
- harness write cases: all PASS
- dedicated edge binary: pipe/file/zero/EBADF/libc errno match

Notes:
- First link failed with R_X86_64_PC32 against `__errno_location` under PIE.
- Fixed with `call __errno_location wrt ..plt` (R_X86_64_PLT32).
- Stack: push errno value before CALL keeps 16-byte alignment.

Failure explanation: none
