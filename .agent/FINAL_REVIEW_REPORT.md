# Final Review Report

Status: READY_FOR_REVIEW (ft_calloc added)
ITa: PASS (67/67 testhook after ft_calloc)
ITb: PASS historically (pre-calloc 44/44); calloc added as live-eval mandatory
Final Verdict: READY_FOR_REVIEW

## Environment

- Official subject: en.subject(libasm).pdf Version 5.5 (does not list ft_calloc)
- Live evaluation: ft_calloc is required; implemented as mandatory
- Host: Ubuntu 24.04 LTS, x86_64
- Toolchain: NASM 2.16.01, gcc 13.3.0, GNU Make 4.3, Valgrind 3.22.0
- Target ABI: System V AMD64, Linux syscalls, PIE (no `-no-pie`)
- errno helper: `__errno_location` (Linux)
- Branch: `cursor/add-ft-calloc-5aff`

## Commit SHA

- TASK 15 checkpoint: `139497bb2bd2667d882417701b1f23c199adfdd6` on `cursor/add-ft-calloc-5aff`

## Build evidence

- `make fclean && make` produces `libasm.a`
- `nasm -f elf64` on seven `.s` files, archived with `ar rcs`
- `make testhook` links `main.c` with `-L. -lasm` as a PIE executable
- Incremental rebuild, `clean`, `fclean`, and `re` verified
- `nm libasm.a` exports `ft_strlen`, `ft_strcpy`, `ft_strcmp`, `ft_write`, `ft_read`, `ft_strdup`, `ft_calloc`

## ITa result

PASS. Clean rebuild, all required symbols linkable, testhook 67/67 twice, including original 44 cases plus ft_calloc zeros, overflow, and free. No crashes.

## ITb result

Historical PASS on the six original functions. This revision adds ft_calloc without rewriting them. Makefile rules, NASM Intel `.s`, no inline ASM, no `-no-pie`, no libft remain intact.

## ft_calloc

- Prototype: `void *ft_calloc(size_t nmemb, size_t size);`
- Overflow: unsigned MUL high-half check; NULL + ENOMEM
- malloc failure: return NULL
- Zero fill of the allocated region; pointer writable and freeable
- Valgrind: 0 errors, 0 leaks

## Failing tests

None.

## Warnings

- Linker would warn / fail on PC32 calls to libc under PIE. External libc calls use `wrt ..plt`.
- NASM objects include `.note.GNU-stack` to mark the stack non-executable.
- testhook invalid-fd Valgrind warnings are from existing EBADF cases.

## Unresolved risks

- Evaluator machines that are macOS would need `___error` and BSD syscall numbers. 42 Tokyo / this path is Linux x86-64.
- `NULL` string inputs for the original functions remain undefined (same as libc); not used as PASS/FAIL gates.
- malloc-failure is reviewed in code (`jz .done`) rather than forced via rlimit in testhook.

## Final verdict

READY_FOR_REVIEW
