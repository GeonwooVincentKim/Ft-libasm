# Review State

## TASK 03 self-review (ft_strcpy)

Findings:
- Copies including the terminating NUL.
- Returns the original destination pointer (saved in RAX at entry).
- Trailing bytes after the copied string match libc (verified with 0x5A fill + memcmp).

ABI concerns:
- Uses RAX, RDI, RSI, DL only (caller-saved). No callee-saved registers, no stack.

errno concerns:
- Not applicable.

Specification concerns:
- Overlapping buffers are undefined in strcpy; not tested as a gate.

Unresolved issues:
- None for ft_strcpy.
