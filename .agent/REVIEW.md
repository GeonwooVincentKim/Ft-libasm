# Review State

## TASK 02 self-review (ft_strlen)

Findings:
- Matches man 3 strlen: count bytes until NUL, return count.
- Compared with libc on empty, single, normal, long strings.
- NULL input is undefined in libc; not tested as a mandatory gate.

ABI concerns:
- Uses only RAX (return) and RDI (argument). No callee-saved registers.
- No stack frame, no external calls, no alignment requirement.

errno concerns:
- Not applicable.

Specification concerns:
- None.

Unresolved issues:
- None for ft_strlen.
