# Review State

## TASK 17 — ft_calloc focused v6.0 test matrix

Implementation (unchanged this task):
- `ft_calloc.s`: unsigned `mul` into `rdx:rax`; `rdx != 0` is overflow, checked BEFORE `malloc`.
- Overflow: `__errno_location@plt`, store ENOMEM=12, return NULL. No malloc.
- Success: `malloc@plt(total)`, byte-zero loop, return pointer in `rax`.
- Zero product: `malloc(0)`, skip stores.
- Relocs: `malloc`, `__errno_location` only. No libc calloc. No libft.
- ABI: `push` before both external calls. Size preserved in `rcx`. Pointer stays in `rax` while `rdi` fills. No callee-saved registers.

Tests added this task (existing six-function tests untouched):
- calloc(1,64), (64,1), (4,int), (16,long), moderate 512 vs libc
- overflow SIZE_MAX*SIZE_MAX and 2*(SIZE_MAX/2+1)

Existing six functions were not rewritten.

Unresolved issues: none blocking.
