# Review State

## TASK 05 self-review (ft_write)

Findings:
- Uses Linux SYS_write (rax=1) with rdi/rsi/rdx already in place.
- Negative syscall return is negated, stored through `__errno_location`, and the function returns -1.
- Success path leaves errno untouched (same as libc).
- External call uses `wrt ..plt` so the object is PIE-safe without `-no-pie`.
- `push rax` before CALL aligns RSP (entry RSP ≡ 8 mod 16).

ABI concerns:
- No callee-saved registers used.
- PLT call required for PIE; do not revert to PC32 `call`.

errno concerns:
- Invalid fd sets EBADF and matches libc write.

Specification concerns:
- None.

Unresolved issues:
- None for ft_write.
