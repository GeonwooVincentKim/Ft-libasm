# Review State

## Final self-review

Findings:
- Mandatory-only libasm.a implemented in NASM Intel 64-bit `.s` files.
- Functions: ft_strlen, ft_strcpy, ft_strcmp, ft_write, ft_read, ft_strdup.
- Makefile has NAME/all/clean/fclean/re and incremental rebuild.
- Testing main links without `-no-pie`.
- Syscall failures set errno via `__errno_location@plt` and return -1.
- ft_strdup calls malloc@plt; stack aligned before calls.
- No bonus, no libft, no inline ASM.
- ITa PASS, ITb PASS.

ABI concerns: none remaining.
errno concerns: none remaining.
Specification concerns: none remaining.
Unresolved issues: none.
