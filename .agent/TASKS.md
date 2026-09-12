# Libasm Builder Tasks

Statuses: TODO | IN_PROGRESS | REVIEW | BLOCKED | DONE

Dependency order is mandatory. Do not start a later task while an earlier incomplete task remains.

| ID | Task | Status | Notes |
|----|------|--------|-------|
| 00 | Repository and environment audit | DONE | 2026-09-12. Empty implementation tree. Subject v5.5 confirmed. NASM missing from snapshot; installed 2.16.01 on this host. |
| 01 | Build/test infrastructure | TODO | Makefile, test main, headers, ignore rules. |
| 02 | ft_strlen | TODO | Depends on TASK 01. |
| 03 | ft_strcpy | TODO | Depends on TASK 02. |
| 04 | ft_strcmp | TODO | Depends on TASK 03. |
| 05 | ft_write | TODO | Depends on TASK 04. Syscall + errno. |
| 06 | ft_read | TODO | Depends on TASK 05. Syscall + errno. |
| 07 | ft_strdup | TODO | Depends on TASK 06. malloc + copy. |
| 08 | Full mandatory regression suite | TODO | Depends on TASK 07. |
| 09 | ABI / errno audit | TODO | Depends on TASK 08. |
| 10 | Makefile / clean-build audit | TODO | Depends on TASK 09. |
| 11 | Subject compliance audit | TODO | Depends on TASK 10. |
| 12 | ITa | TODO | Depends on TASK 11. |
| 13 | ITb | TODO | Depends on TASK 12 PASS. |

## TASK 00 — Repository and environment audit

Status: DONE

Completed: 2026-09-12

### Repository tree (start of run)

Present:

- `AGENTS.md`
- `README.md` (`# Ft-libasm` / `Project for ft-libasm`)
- `en.subject(libasm).pdf` (official subject, version 5.5)
- Git history: `e243f32` initial, `f14e177` / `4d8f86f` AGENTS, `628c086` subject PDF

Absent (mandatory project artifacts):

- `.agent/*` (created by this task)
- `Makefile`
- any `*.s` assembly sources
- `libasm.a`
- test `main`
- headers
- `.gitignore`

### Subject confirmation

Official PDF is authoritative. Mandatory-only scope. No bonus. No libft. See `SUBJECT_EXTRACT.md`.

### Environment (this Cloud Agent host)

| Item | Value |
|------|--------|
| OS | Ubuntu 24.04-class Linux, kernel 6.12.94+, x86_64 |
| gcc | 13.3.0 (`gcc` → gcc-13). Default output is PIE (`ELF64 DYN`). |
| make | GNU Make 4.3 |
| binutils | 2.42 (ar, ld, objdump present) |
| glibc | 2.39 (`__errno_location` is the errno accessor) |
| nasm | Not in the snapshot. Installed this session: NASM 2.16.01 |
| man pages | Minimized image; man pages unavailable. Prototypes taken from system headers. |
| PIE | gcc defaults to PIE. Do not use `-no-pie`. Assembly must be PIC-safe. |

### Evaluator-target assumption

42 Tokyo cluster target is treated as Linux x86-64 + NASM + Intel syntax + glibc.

- Use `__errno_location` (Linux), not Darwin `___error`.
- Syscall ABI: `rax` = number, args `rdi rsi rdx r10 r8 r9`, return in `rax`, error if `rax` in `-4095..-1`.
- Do not change the implementation merely to match this Cloud Agent host if that would diverge from a Linux 42 evaluator.

### Eligibility

TASK 01 is the next eligible task.
