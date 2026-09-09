# Libasm Cursor Agent Rules

## Authority

The official 42 Libasm subject provided by the user is the authoritative specification.

Never use another student's GitHub Libasm implementation as a source for the solution.

If information from another source conflicts with the provided subject, the provided subject always wins.

## Scope

Implement ONLY the mandatory part of Libasm.

Required functions:

- ft_strlen
- ft_strcpy
- ft_strcmp
- ft_write
- ft_read
- ft_strdup

Required output:

- libasm.a
- Makefile
- test main / test code as required by the provided subject

Do NOT implement bonus features unless explicitly requested by the user.

## libft

This project is standalone.

Do NOT add the user's previous libft project as a dependency.

Do NOT link libft.a.

Do NOT copy implementation code from the user's old libft unless the user explicitly requests an analysis of it.

If helper functionality is needed, first determine whether it can be implemented directly within the Libasm subject constraints.

Using another function implemented inside this Libasm project is allowed only when technically appropriate and compliant with the subject.

## Technical Requirements

The implementation must comply with the current provided subject.

Verify all of the following:

- x86-64 / 64-bit assembly
- NASM
- Intel syntax
- assembly source files use `.s`
- no inline assembly
- never use the `-no-pie` compilation flag
- respect the System V AMD64 ABI
- preserve callee-saved registers where required
- respect stack alignment before external function calls
- correctly handle syscall failures
- correctly set `errno`
- avoid crashes, invalid memory access, double free, or other unexpected termination

## Mandatory Functions

### ft_strlen

Reproduce the relevant behavior of `strlen`.

Test at minimum:

- empty string
- one-character string
- normal ASCII string
- long string

Compare results against libc `strlen`.

### ft_strcpy

Reproduce the relevant behavior of `strcpy`.

Test at minimum:

- empty string
- one-character string
- normal string
- destination contents
- returned destination pointer

Compare results against libc `strcpy`.

### ft_strcmp

Reproduce the relevant behavior of `strcmp`.

Do NOT assume the return value must be exactly `-1`, `0`, or `1`.

Test sign/result semantics against libc for:

- identical strings
- shorter/longer strings
- first differing byte
- empty strings
- unsigned-byte-sensitive values where appropriate

### ft_write

Reproduce the required behavior of `write`.

Verify:

- successful write
- returned byte count
- zero-length write
- invalid file descriptor
- failure return value
- correct `errno`

Use pipes or temporary files where useful.

### ft_read

Reproduce the required behavior of `read`.

Verify:

- successful read
- returned byte count
- zero-length read
- EOF behavior
- invalid file descriptor
- failure return value
- correct `errno`

Use pipes or temporary files where useful.

### ft_strdup

Reproduce the relevant behavior of `strdup`.

Verify:

- empty string
- normal string
- long string
- returned data equality
- independent allocated memory
- memory correctness

Compare against libc behavior where appropriate.

## Build Requirements

The resulting static library must be named:

`libasm.a`

The Makefile must contain at least:

- `$(NAME)`
- `all`
- `clean`
- `fclean`
- `re`

The Makefile should rebuild/relink only what is necessary.

Do not introduce unnecessary dependencies.

## Development Philosophy

Do NOT implement the whole project in one step.

Perform exactly one logical task at a time unless explicitly instructed otherwise.

Default implementation order:

1. Repository audit
2. Build and test infrastructure
3. ft_strlen
4. ft_strcpy
5. ft_strcmp
6. ft_write
7. ft_read
8. ft_strdup
9. Full integration tests
10. ABI / errno audit
11. Clean-build verification
12. Human review preparation

For every implementation task:

1. Read the relevant subject requirement.
2. Inspect the current repository state.
3. Identify exactly which files need modification.
4. Briefly describe the intended implementation.
5. Modify only necessary files.
6. Build the project.
7. Run relevant tests.
8. Run edge-case tests.
9. Compare against libc behavior where appropriate.
10. Inspect the resulting git diff.
11. Update project state files.
12. Report the result.

Do not move to the next mandatory function if the current task has unresolved failures.

## Testing Policy

Compilation success alone is NOT sufficient.

Tests should cover:

- normal behavior
- edge cases
- return values
- memory behavior
- ABI-sensitive behavior where practical
- syscall error handling
- `errno`
- clean rebuilds

Prefer differential testing against libc when appropriate.

Do not weaken or remove a failing test merely to obtain a passing result.

Never hide, ignore, or silently suppress failures.

## Independent Self-Review

Before reporting a task as complete, review your own changes for:

- subject compliance
- correctness
- System V AMD64 ABI compliance
- register preservation
- stack alignment
- syscall semantics
- errno handling
- memory safety
- Makefile correctness
- test coverage
- unnecessary complexity

If anything is uncertain, report the uncertainty explicitly.

## Project State

Maintain the following files:

`.agent/STATE.md`

`.agent/TASKS.md`

`.agent/TEST_RESULTS.md`

`.agent/REVIEW.md`

### STATE.md

Record:

- current phase
- current task
- latest successful build
- latest successful tests
- unresolved issues
- next recommended action

### TASKS.md

Use statuses such as:

- TODO
- IN_PROGRESS
- REVIEW
- BLOCKED
- DONE

Do not mark a task DONE unless its acceptance criteria have been satisfied.

### TEST_RESULTS.md

Record:

- command executed
- test scope
- result
- relevant failure details
- date/time if useful

### REVIEW.md

Record:

- code review findings
- ABI concerns
- errno concerns
- subject compliance findings
- items requiring human review

## Git Safety

NEVER perform any of the following:

- `git push`
- force push
- modify Git remotes
- delete or replace Git remotes
- submit the project to 42
- mark the project as finished
- register a peer evaluation
- access the user's 42 Intra account
- access or request 42 credentials
- expose authentication tokens
- expose private SSH keys

Do not change remote configuration even if you believe it would make the task easier.

Local source modifications are allowed.

Local commits may only be created when explicitly requested by the user.

## External Sources

Do NOT search for or copy complete Libasm solutions from:

- GitHub student repositories
- GitLab student repositories
- solution blogs
- answer repositories
- published 42 project solutions

Documentation about:

- x86-64 instructions
- NASM syntax
- Linux syscalls
- System V AMD64 ABI
- libc API behavior

may be consulted when necessary.

Any external technical reference must be used to understand the underlying technology, not to copy another student's project implementation.

## Human Ownership

The final project must be understandable by the user during peer evaluation.

Prefer clear, straightforward implementations over clever or unnecessarily optimized assembly.

For every completed function, maintain enough information for the user to explain:

- what the function does
- input arguments and registers
- return value and register
- important assembly instructions
- loop/control flow
- caller-saved vs callee-saved considerations
- syscall behavior where applicable
- errno behavior where applicable
- memory allocation behavior where applicable
- important edge cases

## Completion Report

For every task, report:

1. Task completed
2. Files inspected
3. Files changed
4. Implementation summary
5. Commands executed
6. Tests executed
7. Test results
8. Git diff summary
9. Known risks or uncertainties
10. Recommended next task

Use one of these final statuses:

- `PASS`
- `PASS_WITH_NOTES`
- `FAIL`
- `BLOCKED`

A task is NOT complete merely because the project compiles.

## Final Restrictions

Do not:

- implement the entire project without incremental review
- implement bonus work without explicit approval
- introduce libft as a dependency
- push or submit anything
- conceal failures
- claim compliance without testing it

When uncertain, stop and report the issue rather than making an irreversible change.
