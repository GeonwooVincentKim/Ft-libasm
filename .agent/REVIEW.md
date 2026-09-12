# Review State

## TASK 04 self-review (ft_strcmp)

Findings:
- Zero-extends bytes (`movzx`) so comparison is unsigned, matching libc strcmp.
- Returns 32-bit difference in EAX (not a forced -1/1). Tests only require sign/equality.
- Empty, prefix, and high-bit bytes covered.

ABI concerns:
- Uses RAX, RCX, RDI, RSI. No callee-saved registers, no stack.

errno concerns:
- Not applicable.

Specification concerns:
- None.

Unresolved issues:
- None for ft_strcmp.
