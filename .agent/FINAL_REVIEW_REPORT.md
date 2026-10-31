# Final Review Report

Status: READY_FOR_HUMAN
ITa: PASS (72/72)
ITb: PASS
Final Verdict: READY_FOR_HUMAN

## Environment

- Authoritative specification: Libasm subject Version 6.0 (seven mandatory functions)
- Bundled file `en.subject(libasm).pdf` in-tree is still v5.5 bytes; v6.0 user requirements override it
- Host: Ubuntu 24.04 LTS, x86_64
- Toolchain: NASM 2.16.01, gcc 13.3.0, GNU Make 4.3, Valgrind 3.22.0
- Target ABI: System V AMD64, Linux syscalls, PIE (no `-no-pie`)
- Branch: `cursor/add-ft-calloc-5aff`

## Commit SHA

- TASK 16 checkpoint: `01a3143b5634bee76ad83faede2bf6b7cc1edf0c` on `cursor/add-ft-calloc-5aff`

## Build evidence

- `make fclean && make` / `make re` produce `libasm.a`
- Seven `.s` files, `nasm -f elf64`, `ar rcs`
- testhook PIE link without `-no-pie`
- Incremental rebuild, `clean`, `fclean`, `re` verified
- Seven T symbols in `libasm.a`

## ITa result

PASS. Clean rebuild, seven symbols linkable, testhook 72/72 twice. read/write success+errno, strdup, calloc zeros/overflow/malloc-fail path. No crashes.

## ITb result

PASS. Structure, mandatory-only (no bonus list functions), no libft, NASM Intel `.s`, no inline ASM, no `-no-pie`, Makefile rules, ft_calloc in SRCS, incremental/clean/fclean/re, ABI (push before malloc/errno), syscall 0/1, errno, calloc overflow-before-malloc, Valgrind 0/0, regression 72/72.

## Function status

- ft_strlen = PASS
- ft_strcpy = PASS
- ft_strcmp = PASS
- ft_write = PASS
- ft_read = PASS
- ft_strdup = PASS
- ft_calloc = PASS

## Failing tests

None.

## Warnings

- In-tree PDF file was not replaced with a binary v6.0 document; Version 6.0 is applied from the supplied subject update.
- Extra repo docs (`AGENTS.md`, `.agent/*`, `Memo.txt`) are outside a typical 42 hand-in.
- Valgrind invalid-fd warnings come from EBADF tests.

## Unresolved risks

- macOS evaluators would need `___error` and BSD syscalls. This path is Linux x86-64.
- Zero-size calloc pointer identity is platform-defined; tests require safety, not one pointer value.

## Final verdict

READY_FOR_HUMAN
