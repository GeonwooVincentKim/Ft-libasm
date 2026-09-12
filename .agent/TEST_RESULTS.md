# Test Results

## TASK 00–06 — PASS

## TASK 07 — ft_strdup

Date: 2026-09-12
Environment: Ubuntu 24.04.4 LTS x86_64, NASM 2.16.01, gcc 13.3.0
Test scope: empty, single, normal, spaces, 4096; separate allocation; NUL; libc strcmp
Result: PASS

Commands:
- `make testhook`
- `./testhook` -> 44 passed, 0 failed
- dedicated edge binary: empty/single/normal/spaces/4096 all PASS

Notes:
- Uses ft_strlen from this library (allowed) and malloc@plt.
- push rdi before calls keeps 16-byte stack alignment.
- Returned pointer differs from src.

Failure explanation: none
