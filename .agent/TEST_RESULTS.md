# Test Results

## TASK 00–07 — PASS

## TASK 08 — Full mandatory regression

Date: 2026-09-12
Environment: Ubuntu 24.04.4 LTS x86_64, NASM 2.16.01, gcc 13.3.0
Test scope: clean rebuild; testhook x3; dedicated strlen/strcpy/strcmp/write/read/strdup edge binaries
Result: PASS

Commands:
- `make fclean && make testhook`
- `./testhook` run 1: 44 passed, 0 failed
- `./testhook` run 2: 44 passed, 0 failed
- `./testhook` run 3: 44 passed, 0 failed
- dedicated edge binaries: all *_EDGE_PASS

Coverage vs AGENTS.md:
- strlen: empty, single, normal, long, libc match
- strcpy: empty, normal, content, NUL, dest pointer, libc match
- strcmp: identical, smaller, larger, empty, lengths, unsigned bytes, sign vs libc
- write: success count/content, zero-length, invalid fd, errno
- read: success, zero-length, EOF, invalid fd, errno
- strdup: empty, normal, long, copy, NUL, separate allocation

Failure explanation: none
