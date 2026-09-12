# Review State

## TASK 06 self-review (ft_read)

Findings:
- Uses Linux SYS_read (rax=0) with rdi/rsi/rdx already in place.
- Same errno/PLT/stack-alignment pattern as ft_write.

ABI concerns:
- No callee-saved registers. `wrt ..plt` for PIE.

errno concerns:
- Invalid fd sets EBADF and matches libc read.

Specification concerns:
- None.

Unresolved issues:
- None for ft_read.
