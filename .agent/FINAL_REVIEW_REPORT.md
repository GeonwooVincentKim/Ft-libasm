# Final Review Report — independent master verification

Status: READY_FOR_HUMAN
ITa: PASS (96/96) on MASTER_HEAD_SHA
ITb: PASS on MASTER_HEAD_SHA
Final Verdict: READY_FOR_HUMAN

## MASTER identity

- TARGET_BRANCH: `master`
- MASTER_HEAD_SHA: `0d091d292f4b966c5f1e541bac37b16bcf4c5dcb`
- origin/master: same SHA (fetched 2026-10-31)
- Commit: Merge pull request #2 from GeonwooVincentKim/cursor/add-ft-calloc-5aff
- Isolated worktree: `/tmp/libasm-master-review` (detached HEAD at origin/master)
- Local working branch was NOT used as the review target (`cursor/add-ft-calloc-5aff` @ `af82dd3`)

## MASTER_VS_PREVIOUS_TESTED_COMMIT

MISMATCH of commit SHA (previous recorded evidence used `af82dd3` / TASK 16 `01a3143` on the PR branch).

Source tree of `*.s`, `Makefile`, `libasm.h`, `main.c` is identical to `af82dd3` (`git diff af82dd3 HEAD -- those files` empty). Prior ITa/ITb numbers were **not** reused: this report’s commands were re-executed on `0d091d2`.

## Environment

- Authoritative specification: Libasm subject Version 6.0
- Host: Ubuntu 24.04 LTS, x86_64
- Toolchain: NASM 2.16.01, gcc 13.3.0, GNU Make 4.3, Valgrind 3.22.0
- Target ABI: System V AMD64, Linux, PIE (no `-no-pie`)

## Build evidence on MASTER_HEAD_SHA

Executed in `/tmp/libasm-master-review`:

1. `make fclean`
2. `make` — seven `nasm -f elf64` objects, `ar rcs libasm.a`
3. `make` again — `Nothing to be done for 'all'`
4. `make clean` — objects removed; `libasm.a` remains
5. `make` — rebuilds objects and archive
6. `make fclean` — library and testhook removed
7. `make re` — full rebuild
8. `make testhook` — PIE link, no `-no-pie`

`nm libasm.a` T symbols: ft_strlen, ft_strcpy, ft_strcmp, ft_write, ft_read, ft_strdup, ft_calloc.

`readelf -r ft_calloc.o`: `malloc`, `__errno_location` only (not libc calloc).

## ITa (executed on 0d091d2)

PASS. `./testhook` twice: **96 passed, 0 failed**. Covers seven functions including calloc(1,1)/(1,N)/(N,1), zeros, writable, free, zero-size, overflow SIZE_MAX*2, 2*SIZE_MAX, SIZE_MAX*SIZE_MAX, (SIZE_MAX/2+1)*2, 2*(SIZE_MAX/2+1), ENOMEM, below-overflow 256*256.

Valgrind: `valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=42 ./testhook` — 0 errors, 0 leaks, 29/29 alloc/free.

## ITb (executed on 0d091d2)

PASS. Seven `.s` sources on master, no libft, no `-no-pie`, NASM Intel, no inline ASM, Makefile NAME/all/clean/fclean/re, incremental second make idle, ABI push-before-malloc/errno, SYS_write=1 SYS_read=0, worktree git status clean of tracked files after build (gitignored artifacts only).

## Function review (master sources)

- ft_strlen: PASS
- ft_strcpy: PASS
- ft_strcmp: PASS (sign/unsigned; not exact ±1)
- ft_write: PASS (syscall 1, -1, errno)
- ft_read: PASS (syscall 0, EOF, -1, errno)
- ft_strdup: PASS (malloc, copy, NUL, alignment via push)
- ft_calloc: PASS (mul overflow before malloc, NULL+ENOMEM, zero-fill, malloc fail jz)

## Warnings

- Bundled `en.subject(libasm).pdf` remains v5.5 bytes; Version 6.0 is applied from the supplied update.
- Extra docs (`AGENTS.md`, `.agent/*`, `Memo.txt`) are outside a typical 42 hand-in.
- Valgrind invalid-fd warnings from EBADF tests are not errors.

## Final verdict

READY_FOR_HUMAN

Human final review and defense preparation are still required.
This verification did not merge, did not modify master, and did not submit to 42.
