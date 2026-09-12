# Libasm Builder Tasks

Statuses: TODO | IN_PROGRESS | REVIEW | BLOCKED | DONE

Mandatory only. No bonus. No libft.

| ID | Task | Status | Notes |
| --- | --- | --- | --- |
| TASK 00 | Repository and environment audit | DONE | 2026-09-12. Empty implementation tree; official subject v5.5 present. |
| TASK 01 | Build/test infrastructure | TODO | Makefile, test main, NASM/PIE toolchain. |
| TASK 02 | ft_strlen | TODO | |
| TASK 03 | ft_strcpy | TODO | |
| TASK 04 | ft_strcmp | TODO | |
| TASK 05 | ft_write | TODO | |
| TASK 06 | ft_read | TODO | |
| TASK 07 | ft_strdup | TODO | |
| TASK 08 | Full mandatory regression suite | TODO | |
| TASK 09 | ABI / errno audit | TODO | |
| TASK 10 | Makefile / clean-build audit | TODO | |
| TASK 11 | Subject compliance audit | TODO | |
| TASK 12 | ITa | TODO | Only after TASK 11. |
| TASK 13 | ITb | TODO | Only if ITa passes. |

## TASK 00 evidence (2026-09-12)

- Repository contents at HEAD `628c086`: `AGENTS.md`, `README.md`, `en.subject(libasm).pdf`.
- No `Makefile`, no `.s` sources, no test `main`, no `libasm.a`.
- Official subject: Libasm version 5.5 (pdfTeX, 2026-07-08).
- Host: Ubuntu 24.04.4 LTS, x86_64, glibc 2.39, gcc 13.3.0 (default PIE), GNU Make 4.3.
- NASM was missing from the Cloud Agent snapshot; installed `nasm 2.16.01` for this session only.
- NASM Intel `.s` assembled to ELF64, linked without `-no-pie`, ran and matched `strlen` on `"hello"`.
- Linux errno symbol is `__errno_location`. `___error` is not present (macOS).
- x86-64 syscall numbers: `read=0`, `write=1`. Do not use asm-generic 63/64.
