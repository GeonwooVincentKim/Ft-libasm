# Review Log

## TASK 00 — Repository and environment audit

Date: 2026-09-12

### Self-review findings

- Repository is a rules + subject seed only. No mandatory implementation exists.
- Official subject (v5.5) matches AGENTS.md mandatory list: `ft_strlen`, `ft_strcpy`, `ft_strcmp`, `ft_write`, `ft_read`, `ft_strdup`, plus a test `main` and `libasm.a`.
- Bonus chapter exists in the PDF and is explicitly out of scope.
- No libft dependency is present (and must not be introduced).
- Cloud Agent host is a valid Linux x86-64 development environment after installing NASM.
- Man pages are unavailable; later tasks must compare against libc via headers / live libc calls, not `man`.

### ABI concerns

- System V AMD64: integer/pointer args in `rdi, rsi, rdx, rcx, r8, r9`; return in `rax`.
- Callee-saved: `rbx, rbp, r12-r15`.
- Stack alignment: `rsp` 16-byte aligned at `call` sites to libc (`malloc`, `__errno_location`).
- PIC/PIE: do not use non-RIP-relative absolute addressing that would require `-no-pie`.
- Linux syscalls use `r10` for the 4th argument, not `rcx`.

### errno concerns

- Linux: call `__errno_location`, store the positive errno at the returned `int *`.
- Darwin `___error` must not be the only path if the evaluator is Linux (42 Tokyo assumption).
- Subject requires errno to be set properly on syscall failure (`write` / `read`). `strdup` inherits malloc failure errno.

### Specification concerns

- Subject requires a submitted test `main`. AGENTS.md also requires a main capable of testing the mandatory implementation.
- Subject forbids `-no-pie`.
- Subject requires NASM + Intel syntax + `.s` files + no inline ASM.
- `ft_strcmp` must follow `strcmp` signed-return / unsigned-byte semantics; tests must not require exact `-1`/`1`.
- Undefined inputs (NULL pointers to strlen/strcpy/strcmp/strdup) must not be turned into mandatory pass/fail gates.

### Unresolved issues

- No assembly yet; ABI/errno review is planning-only.
- NASM not persisted in the environment snapshot.
- Next task must introduce build/test infrastructure without implementing all functions at once.
