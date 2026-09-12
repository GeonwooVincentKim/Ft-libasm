# Review State

## TASK 07 self-review (ft_strdup)

Findings:
- malloc(len+1), copy including NUL, return new pointer or NULL if malloc fails.
- malloc failure leaves errno to malloc (no extra errno write).
- Copy is independent of ft_strcpy; dest pointer stays in RAX.

ABI concerns:
- `push rdi` aligns stack before ft_strlen and malloc.
- malloc uses `wrt ..plt`; ft_strlen is same-archive PC32 (valid in final PIE).

errno concerns:
- None beyond malloc's own failure path.

Specification concerns:
- Subject allows calling malloc. No libft.

Unresolved issues:
- None for ft_strdup.
