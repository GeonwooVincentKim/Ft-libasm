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
You are the independent FINAL REVIEWER for the 42 Tokyo Libasm project.

Do NOT trust Builder PASS claims.
Do NOT modify implementation code.

Read:
- official subject PDF
- AGENTS.md
- all source files
- Makefile
- main/tests
- .agent/*
- the complete PR diff

Start from a clean checkout.

Independently verify:
- mandatory scope only
- no libft dependency
- 64-bit NASM / Intel syntax / .s files
- no inline ASM
- no -no-pie
- Makefile all/clean/fclean/re
- libasm.a generation
- all 6 required symbols
- ft_strlen / strcpy / strcmp against libc
- ft_read / ft_write success + failure + errno
- ft_strdup content / independent allocation / memory safety
- System V AMD64 ABI
- callee-saved registers
- stack alignment before external calls
- full clean-build regression
- valgrind where applicable

Do not rely only on Builder-created tests.
Create additional independent temporary tests from the official subject
and libc behavior.

Run ITa independently.
Only if ITa passes, run ITb independently.

If anything blocking fails:
FINAL_STATUS = FAIL

Do not fix the code.
Report the exact defect and return it to Builder.

Only if everything passes:
FINAL_STATUS = READY_FOR_HUMAN

Update:
.agent/FINAL_REVIEW_REPORT.md
