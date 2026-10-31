# Review State

## TASK 16 — Version 6.0

Findings:
- Mandatory set is seven functions. `ft_calloc` is required.
- Existing six functions were not rewritten.
- `ft_calloc.s` detects `nmemb * size` overflow with unsigned `mul` (`rdx != 0`) BEFORE `malloc`.
- Overflow: `__errno_location@plt`, store ENOMEM (12), return NULL. `malloc` is not called.
- Success: `malloc@plt`, zero-fill, pointer in `rax`.
- Zero sizes: product 0, `malloc(0)`, skip stores. Pointer may be NULL or unique; tests do not require one value.
- Relocs: `malloc` and `__errno_location` only. No libc `calloc`. No libft.
- Stack: `push` before `malloc` and before `__errno_location` (`rsp % 16 == 0`).
- No callee-saved registers used.

ABI / errno: no blocking issues on Linux x86-64.

Unresolved issues: none blocking.
