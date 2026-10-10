# Review State

## TASK 15 — ft_calloc

Findings:
- `ft_calloc.s` added; existing six functions unchanged.
- Unsigned `mul` into `rdx:rax`; `rdx != 0` is overflow (no naive `nmemb * size`).
- Overflow: `__errno_location@plt`, store 32-bit ENOMEM (12), return NULL.
- Success: `malloc@plt(n)`, zero `n` bytes, return original pointer in `rax`.
- `n == 0` (nmemb or size 0, including 0 * SIZE_MAX): malloc(0), skip stores.
- malloc failure: `test rax, rax` / `jz .done`, return NULL; errno left to malloc.
- No libc calloc. No libft. `wrt ..plt` for PIE. `.note.GNU-stack` present.

ABI:
- Entry: `rdi` = nmemb, `rsi` = size, return `rax`.
- `push rax` before malloc: preserves total size and makes `rsp % 16 == 0`.
- After malloc, size recovered in `rcx`; pointer stays in `rax` while `rdi` walks the fill.
- Overflow path also `push`/`pop` before `__errno_location`.
- No callee-saved registers used.
- `errno` is `int`: `mov dword [rax], 12`.

errno:
- Overflow: ENOMEM.
- malloc fail: malloc's ENOMEM.
- Zero-size success: errno not modified (matches host glibc).

Specification:
- Live evaluation requires ft_calloc even though subject v5.5 omits it.
- Behavior matched to Linux x86-64 glibc for tested cases.

Unresolved issues: none blocking.
