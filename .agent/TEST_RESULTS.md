# Test Results

## TASK 00–11 — PASS

## TASK 12 — ITa mandatory integration gate

Date: 2026-09-12
Environment: Ubuntu 24.04.4 LTS x86_64, NASM 2.16.01, gcc 13.3.0
Start: `make fclean` then `make all`
Result: ITa = PASS

Checks:
1. Build succeeds: PASS (`nasm -f elf64` + `ar rcs libasm.a`)
2. libasm.a exists: PASS
3. Six functions linkable: PASS (`nm` T symbols in archive and testhook)
4. main links with libasm.a: PASS (PIE testhook, no -no-pie)
5. Mandatory regression: PASS (44/44)
6. read/write success: PASS
7. read/write failure + errno: PASS
8. strdup alloc/copy: PASS
9. No crash: PASS
10. Suite repeated: PASS (run 2 also 44/44)

Note: an initial `nm | grep -q` helper falsely flagged missing symbols due to SIGPIPE + pipefail; `nm` listing confirms all six T symbols.

Failure explanation: none
