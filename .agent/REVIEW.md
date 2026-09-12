# Review State

## TASK 00 self-review

See prior TASK 00 notes. Host matches 42 Tokyo Linux x86-64 NASM/PIE target.

## TASK 01 self-review

Findings:
- Makefile uses NASM Intel via `nasm -f elf64`, archives `libasm.a`, and never passes `-no-pie`.
- Extra `test` / `testhook` rules are convenience only; required rules are present.
- Incremental rebuild works (`%.o: %.s`).
- `main.c` links all six mandatory symbols and contains libc-differential tests for later tasks.
- Placeholder `.s` files export the required globals and mark `.note.GNU-stack` non-executable.
- No inline assembly, no libft, no bonus sources.
- `ft_strdup` tests are NULL-safe so the harness does not crash on placeholders.

ABI concerns:
- Placeholders do not yet preserve anything or call externals.

errno concerns:
- Not implemented yet (TASK 05/06).

Specification concerns:
- Subject requires a testing main compiled with the library: satisfied at link time.
- Functional correctness is deferred to TASK 02–07.

Unresolved issues:
- None for infrastructure.
