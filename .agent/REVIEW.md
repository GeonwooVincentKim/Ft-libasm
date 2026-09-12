# Review State

## TASK 09 self-review (ABI / errno)

Findings:
- System V AMD64 argument registers used correctly (rdi/rsi/rdx).
- Returns in rax/eax.
- Callee-saved registers unused and empirically preserved.
- Syscall clobbers (rcx/r11) are caller-saved; acceptable.
- errno set only on syscall failure via `__errno_location` (Linux). Subject also allows `___error` (macOS); not used on this target.
- Stack aligned (RSP ≡ 0 mod 16) before every CALL.

ABI concerns:
- None remaining.

errno concerns:
- None remaining.

Specification concerns:
- None.

Unresolved issues:
- None
