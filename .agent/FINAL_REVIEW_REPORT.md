# Final Review Report

Status: READY_FOR_FINAL_REVIEW
ITa: PASS
ITb: PASS
Final Verdict: READY_FOR_FINAL_REVIEW

## Environment

- Official subject: en.subject(libasm).pdf Version 5.5
- Host: Ubuntu 24.04.4 LTS, x86_64
- Toolchain: NASM 2.16.01, gcc 13.3.0, GNU Make 4.3, binutils 2.42
- Target ABI: System V AMD64, Linux syscalls, PIE (no `-no-pie`)
- errno helper: `__errno_location` (Linux; subject also allows `___error`)
- Persistent branch: `automation/libasm`

## Commit SHA

- ITb verification base: `12000ef1a1c7ef363092e3460fe49246c5d9f798`
- Final Builder checkpoint: this commit on `automation/libasm`

## Build evidence

- `make fclean && make` produces `libasm.a`
- `nasm -f elf64` on six `.s` files, archived with `ar rcs`
- `make testhook` links `main.c` with `-L. -lasm` as a PIE executable
- Incremental rebuild, `clean`, `fclean`, and `re` verified

## ITa result

PASS. Clean rebuild, all six symbols linkable, testhook 44/44 twice, including read/write success, read/write errno, and strdup allocation/copy. No crashes.

## ITb result

PASS. All 25 evaluation-simulation checks passed:

1. Repository structure
2. Mandatory-only (no bonus)
3. No Libft dependency
4. `.s` assembly sources
5. NASM build
6. Intel syntax
7. No inline ASM
8. No `-no-pie`
9. Required Makefile rules
10. Incremental rebuild
11. `clean`
12. `fclean`
13. `re`
14. Fresh build
15. `libasm.a`
16. Test main link (PIE)
17. Full ITa suite again (44/44)
18. Calling convention review
19. Callee-saved unused / preserved
20. Stack alignment before external calls (PLT)
21. Syscall error handling
22. errno audit
23. Final regression (44/44)
24. git status inspection
25. Unresolved defect check

## Failing tests

None.

## Warnings

- Linker would warn / fail on PC32 calls to libc under PIE. External libc calls use `wrt ..plt`.
- NASM objects include `.note.GNU-stack` to mark the stack non-executable.

## Unresolved risks

- Evaluator machines that are macOS would need `___error` and BSD syscall numbers. 42 Tokyo / this subject path is treated as Linux x86-64.
- `NULL` inputs remain undefined (same as libc); not used as PASS/FAIL gates.

## Final verdict

READY_FOR_FINAL_REVIEW
