# Review State

## TASK 15 — ft_calloc (in progress)

Intended implementation:
- `ft_calloc.s`: unsigned `mul` overflow check (high half in `rdx`).
- Overflow: set `errno` to `ENOMEM` via `__errno_location@plt`, return NULL.
- Success: `malloc@plt` then byte-zero the block; return pointer in `rax`.
- Zero `nmemb` or `size`: product 0, `malloc(0)`, no overflow (matches glibc).
- Stack: `push` before external calls so `rsp % 16 == 0`.
- No libc `calloc`, no libft.

ABI concerns to verify:
- `rdi`/`rsi` args; `rax` return
- total size preserved across `malloc` (`push`/`pop` into `rcx`)
- returned pointer preserved in `rax` while zeroing via `rdi`
- callee-saved unused
- overflow path alignment before `__errno_location`

errno: overflow sets ENOMEM=12; malloc failure relies on malloc.

Unresolved: pending build/test/valgrind.
