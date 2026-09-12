# Libasm Builder State

## Current phase

TASK 00 complete. Mandatory implementation has not started.

## Current task

TASK 00 — Repository and environment audit — DONE (2026-09-12)

Next eligible task: TASK 01 — Build/test infrastructure

## Latest successful build

None. No project Makefile or `libasm.a` exists yet.

Environment smoke (not project build):

- `nasm -f elf64` produced ELF64 relocatable object
- `gcc` linked a PIE executable without `-no-pie`
- Probe `smoke_len("hello")` == libc `strlen` (`5`)

## Latest successful test

None for mandatory functions.

Environment probe only: NASM + gcc PIE link + runtime compare with libc `strlen` — PASS

## Environment assumptions

These describe the Cloud Agent host. Do not change the implementation merely to match this host if that would diverge from the 42 Tokyo evaluator.

| Item | Value |
| --- | --- |
| Official subject | `en.subject(libasm).pdf` version 5.5 |
| Scope | Mandatory only (`libasm.a` + six functions + test main) |
| Expected evaluator | 42 Tokyo Linux x86-64 (System V AMD64 ABI) |
| Cloud Agent OS | Ubuntu 24.04.4 LTS, kernel 6.12.94+, x86_64 |
| Assembler | NASM 2.16.01 (installed this session; not persisted in snapshot) |
| Compiler | gcc 13.3.0, `--enable-default-pie`, `__PIE__=2` |
| libc | glibc 2.39 |
| errno hook | `extern int *__errno_location(void);` (Linux) |
| Forbidden | inline ASM, AT&T syntax, `-no-pie`, libft, bonus unless authorized |
| Syscalls (x86-64) | `SYS_read=0`, `SYS_write=1` |
| `malloc` | allowed for `ft_strdup` |

## Repository inventory

Present:

- `AGENTS.md` — builder rules
- `README.md` — one-line placeholder
- `en.subject(libasm).pdf` — authoritative subject
- `.agent/*` — builder state (this run)

Absent (required later):

- `Makefile` with `$(NAME)`, `all`, `clean`, `fclean`, `re`
- `ft_strlen.s` `ft_strcpy.s` `ft_strcmp.s` `ft_write.s` `ft_read.s` `ft_strdup.s`
- test `main` that links with `libasm.a`
- `libasm.a`

## Unresolved issues

1. NASM is not part of the Cloud Agent snapshot. Later runs must install it or the environment must be updated. Recorded; not a subject-compliance blocker.
2. Man pages are stripped on this minimized image. Prototypes were taken from system headers, not `man 3`/`man 2`.
3. Linker warned that objects without `.note.GNU-stack` imply an executable stack. Not a subject requirement, but later `.s` files should mark the stack non-executable.
4. No mandatory functions exist yet.

## Next expected action

TASK 01 — Build/test infrastructure:

- Persist a NASM-aware Makefile that produces `libasm.a` without `-no-pie`
- Add a test `main` skeleton that can grow with each function
- Do not implement the six functions in that task beyond the minimum needed to keep the empty/stub library linkable, unless TASK 01 is defined as infrastructure only (preferred: stub objects or wait until TASK 02 adds the first real function)
