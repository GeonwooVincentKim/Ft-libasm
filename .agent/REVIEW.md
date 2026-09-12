# Review State

## TASK 00 self-review

Findings:
- Repository is docs-only. No assembly, Makefile, header, tests, or libasm.a yet.
- Subject v5.5 mandatory functions match AGENTS.md: ft_strlen, ft_strcpy, ft_strcmp, ft_write, ft_read, ft_strdup.
- Bonus explicitly out of scope.
- Host matches expected 42 Tokyo Linux target (x86-64, NASM Intel, PIE).
- Do not use macOS `___error` or BSD syscall numbers on this target.
- Do not use `-no-pie`.
- NASM objects should include `.note.GNU-stack` to avoid executable-stack linker warnings.
- No libft dependency present.
- No inline ASM present.

ABI concerns:
- None yet (no implementation). Future functions that call malloc / __errno_location must align RSP to 16 before CALL.

errno concerns:
- Future ft_read/ft_write must translate Linux syscall negative returns into errno + -1.

Specification concerns:
- Main test program is required by the subject and is not present yet (TASK 01).

Unresolved issues:
- None
