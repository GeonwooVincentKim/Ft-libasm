# Self-review

## TASK 00 — Repository and environment audit

Date: 2026-09-12

### Self-review findings

- The GitHub repository is a documentation-only seed: rules, README, and the official subject PDF. There is no Libasm implementation to review yet.
- The official subject is version 5.5. Mandatory requirements match `AGENTS.md`: `libasm.a`; `ft_strlen`, `ft_strcpy`, `ft_strcmp`, `ft_write`, `ft_read`, `ft_strdup`; a test `main`; 64-bit NASM Intel `.s` files; no inline ASM; no `-no-pie`; syscall error handling and `errno`.
- Bonus functions and `t_list` are specified but are out of scope unless explicitly authorized.
- No libft tree, `libft.a`, or Libft sources are present.

### ABI concerns

- Target calling convention is System V AMD64: arguments in `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9`; return in `rax`; callee-saved `rbx`, `rbp`, `r12`–`r15`.
- `ft_strdup` will call `malloc`. The stack must be 16-byte aligned immediately before that call (`rsp ≡ 8 (mod 16)` after a `call` that has not yet adjusted the frame, so an odd number of extra 8-byte pushes or a dummy `sub rsp, 8` is required).
- Linux syscall ABI uses `r10` for the 4th argument, not `rcx`. `read`/`write` use only three arguments (`rdi`, `rsi`, `rdx`), so this distinction is not needed for the mandatory syscalls.
- Cloud Agent gcc defaults to PIE. A NASM ELF64 object linked without `-no-pie` produced a working PIE executable. Implementation must remain compatible with that model.

### errno concerns

- Subject allows `___error` or `errno_location`.
- This host and the assumed 42 Tokyo Linux evaluator export `__errno_location` (glibc). `___error` is Darwin and is not present here.
- On Linux, a failed syscall returns `-errno` in `rax` (typically in `-4095..-1`). The wrapper must store the positive errno through `__errno_location` and return `-1`.
- Do not use asm-generic syscall numbers (`read=63`, `write=64`). x86-64 Linux numbers are `read=0`, `write=1`.

### Specification concerns

- Tests must follow referenced libc/syscall behavior. Do not invent NULL-pointer or other undefined-behavior gates.
- `ft_strcmp` must be validated by equality/sign, not by requiring exactly `-1`/`1`.
- `ft_write` / `ft_read` must be checked for success counts, zero-length, invalid fd, `-1`, and errno.
- `ft_strdup` may call `malloc`; allocation failure should return NULL (libc `strdup` behavior) and leave errno as `malloc` set it.

### Unresolved issues

- NASM is not baked into the Cloud Agent snapshot (installed ad-hoc this session).
- No implementation files exist.
- Executable-stack linker note should be addressed when `.s` files are added (`section .note.GNU-stack noalloc noexec nowrite progbits`).
- ITa / ITb have not run.

### Verdict

TASK 00 PASS. Safe to start TASK 01.
