# Test Results

## TASK 00–03 — PASS

## TASK 04 — ft_strcmp

Date: 2026-09-12
Environment: Ubuntu 24.04.4 LTS x86_64, NASM 2.16.01, gcc 13.3.0
Test scope: identical, empty, prefix/length, case, unsigned 0x01/0xFF/NUL; sign vs libc
Result: PASS

Commands:
- `make testhook`
- harness strcmp cases: all PASS
- dedicated edge binary: all signs and several exact diffs match glibc strcmp

Failure explanation: none
