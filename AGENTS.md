# 42 Tokyo Libasm — Cursor Engineering Rules

## 1. Authority

The official Libasm subject supplied by the user is the authoritative specification.

Never use another student's Libasm implementation as a solution source.

If another source conflicts with the official supplied subject,
the supplied subject wins.

Do not silently apply requirements from another Libasm version.

---

## 2. Scope

Current scope: MANDATORY ONLY.

Required library:

`libasm.a`

Required functions:

- `ft_strlen`
- `ft_strcpy`
- `ft_strcmp`
- `ft_write`
- `ft_read`
- `ft_strdup`

A `main` function capable of testing the mandatory implementation
and linking with `libasm.a` must be maintained.

Do NOT implement bonus unless the user explicitly authorizes it.

---

## 3. No libft Dependency

This Libasm project is standalone.

Do NOT introduce:

- `libft.a`
- the previous Libft repository
- copied Libft source files
- a Libft build dependency

Using another function implemented inside THIS Libasm project
is not considered a Libft dependency.

---

## 4. Technical Requirements

The implementation must respect the supplied subject.

Verify:

- 64-bit assembly
- NASM
- Intel syntax
- `.s` source files
- no inline assembly
- never use `-no-pie`
- correct calling convention
- correct ABI behavior
- correct register preservation
- correct stack alignment before external calls
- correct syscall behavior
- correct syscall error handling
- correct `errno` behavior
- correct memory handling

Do not change implementation merely to match the Cloud Agent host
if that would diverge from the actual evaluator target.

Record environment assumptions.

---

## 5. Makefile Requirements

The Makefile must provide at least:

- `$(NAME)`
- `all`
- `clean`
- `fclean`
- `re`

It must rebuild/relink only what is necessary.

Expected mandatory artifact:

`libasm.a`

---

## 6. Development Model

Never implement the entire project in a single uncontrolled step.

Perform ONE logical task per Builder run unless explicitly instructed otherwise.

Default order:

TASK 00 — Repository and environment audit
TASK 01 — Build/test infrastructure
TASK 02 — ft_strlen
TASK 03 — ft_strcpy
TASK 04 — ft_strcmp
TASK 05 — ft_write
TASK 06 — ft_read
TASK 07 — ft_strdup
TASK 08 — Full mandatory regression suite
TASK 09 — ABI / errno audit
TASK 10 — Makefile / clean-build audit
TASK 11 — Subject compliance audit
TASK 12 — ITa
TASK 13 — ITb

---

## 7. Task Workflow

For each Builder task:

1. Read this `AGENTS.md`.
2. Read the official subject.
3. Read `.agent/TASKS.md`.
4. Read `.agent/STATE.md`.
5. Read `.agent/REVIEW.md`.
6. Select exactly one permitted task.
7. Mark it `IN_PROGRESS`.
8. Inspect existing implementation.
9. Describe the intended change briefly.
10. Modify only necessary files.
11. Build.
12. Execute relevant tests.
13. Execute edge-case tests.
14. Compare with libc where appropriate.
15. Inspect `git diff`.
16. Perform self-review.
17. Update `.agent/*`.
18. Report evidence.

Never mark a task DONE because compilation alone succeeded.

---

## 8. Testing Rules

Tests must cover functional behavior and failure behavior where applicable.

### ft_strlen

Verify valid-string behavior including:

- empty string
- single character
- normal string
- long string

Compare with libc `strlen`.

### ft_strcpy

Verify:

- empty string
- normal string
- copied content
- NUL termination
- destination return pointer

Compare with libc `strcpy`.

### ft_strcmp

Verify:

- identical strings
- first string smaller
- first string larger
- empty strings
- different lengths
- unsigned-byte-sensitive comparisons where relevant

Do NOT require exact `-1` or `1`.

Validate correct equality/sign semantics.

### ft_write

Verify:

- successful write
- byte count
- zero-length operation
- invalid descriptor
- failure return value
- errno

Use pipes/files when useful.

### ft_read

Verify:

- successful read
- byte count
- zero-length read
- EOF
- invalid descriptor
- failure return value
- errno

Use pipes/files when useful.

### ft_strdup

Verify:

- empty string
- normal string
- long string
- copied content
- NUL termination
- separately allocated memory
- memory correctness

---

## 9. Undefined Behavior

Do not invent requirements for undefined inputs.

Tests intended as mandatory PASS/FAIL gates must be based on behavior
required by the referenced functions and official subject.

Experimental robustness tests may exist,
but they must be labeled separately and must not incorrectly redefine
subject compliance.

---

## 10. Project State Files

Maintain:

`.agent/TASKS.md`
`.agent/STATE.md`
`.agent/TEST_RESULTS.md`
`.agent/REVIEW.md`
`.agent/FINAL_REVIEW_REPORT.md`

### TASKS.md

Statuses:

- TODO
- IN_PROGRESS
- REVIEW
- BLOCKED
- DONE

### STATE.md

Record:

- current phase
- current task
- latest successful build
- latest successful test
- unresolved issues
- next expected action

### TEST_RESULTS.md

Record:

- command
- environment
- test scope
- PASS/FAIL
- relevant output
- failure explanation

### REVIEW.md

Record:

- self-review findings
- ABI concerns
- errno concerns
- specification concerns
- unresolved issues

---

## 11. Git Rules

Builder automation MAY:

- modify local/working branch files
- create an automation branch
- commit to an automation branch
- open/update a PR if configured

Builder automation MUST NOT:

- push directly to official 42/Vogsphere
- access Intra
- submit the project
- mark the project finished
- register an evaluation
- alter Git remotes
- expose credentials
- merge final submission changes automatically

The user owns final submission.

---

## 12. External Source Rules

Do NOT search for or copy complete Libasm implementations from:

- student GitHub repositories
- student GitLab repositories
- answer repositories
- solution blogs

Technical documentation for NASM, x86-64, ABI, syscalls,
and libc semantics may be consulted when necessary.

Use such information for understanding,
not for copying project implementation.

---

## 13. Completion Status

Every run must finish with one of:

`PASS`
`PASS_WITH_NOTES`
`FAIL`
`BLOCKED`

And report:

TASK:
STATUS:
FILES_INSPECTED:
FILES_CHANGED:
BUILD_COMMANDS:
TEST_COMMANDS:
TEST_RESULTS:
DIFF_SUMMARY:
RISKS:
NEXT_ACTION:

Do not hide failures.

---

# Final Integration Test Gates

## ITa — Mandatory Library Integration

ITa is an internal automation gate.

ITa must begin from a clean build state.

Required checks:

1. Build succeeds.
2. `libasm.a` exists.
3. All six mandatory functions are linkable.
4. Required `main` compiles and links with `libasm.a`.
5. All mandatory function regression tests pass.
6. read/write success behavior passes.
7. read/write failure and errno behavior passes.
8. strdup allocation/copy tests pass.
9. No unexpected crash occurs.
10. Full regression suite passes repeatedly.

Any mandatory failure means:

`ITa = FAIL`

Only all-green results allow:

`ITa = PASS`

---

## ITb — Final Evaluation Simulation

ITb is the final internal end-to-end gate.

Start from a clean checkout/state.

Verify:

1. Repository structure.
2. Mandatory-only implementation.
3. No Libft dependency.
4. `.s` assembly source usage.
5. NASM build.
6. Intel syntax.
7. No inline ASM.
8. No `-no-pie`.
9. Required Makefile rules.
10. Correct incremental rebuild behavior.
11. `clean`.
12. `fclean`.
13. `re`.
14. Fresh build.
15. `libasm.a`.
16. Test main link.
17. Full ITa suite again.
18. Calling convention / ABI review.
19. Callee-saved register audit where relevant.
20. Stack alignment audit where external calls occur.
21. syscall error handling audit.
22. errno audit.
23. final regression.
24. final git diff/status inspection.
25. unresolved defect check.

Any blocking failure means:

`ITb = FAIL`

Only all mandatory checks passing allow:

`ITb = PASS`

When ITb finishes, write:

`.agent/FINAL_REVIEW_REPORT.md`

with:

- environment
- commit SHA
- build evidence
- ITa result
- ITb result
- failing tests
- warnings
- unresolved risks
- final verdict
