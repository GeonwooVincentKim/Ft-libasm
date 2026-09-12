# Libasm Builder State

- current phase: infrastructure pending
- current task: TASK 00 DONE; next = TASK 01 Build/test infrastructure
- latest successful build: none (no Makefile / sources yet)
- latest successful test: none
- READY_FOR_FINAL_REVIEW: no
- ITa: not run
- ITb: not run

## Environment assumptions

- Implementation target: Linux x86-64 System V AMD64 ABI.
- errno helper: `extern __errno_location` (subject allows `___error` or `errno_location`).
- NASM Intel syntax, 64-bit, `.s` files, no inline ASM, no `-no-pie`.
- Cloud Agent snapshot did not include NASM. This session installed `nasm 2.16.01` via apt. Later pods may need the same install unless the environment snapshot is updated.
- gcc on this host produces PIE by default. Link tests without `-no-pie`.

## Unresolved issues

- Mandatory implementation does not exist yet.
- Build/test infrastructure does not exist yet.
- NASM is not part of the durable environment snapshot.
- Man pages are missing on this host; libc prototypes were taken from headers.

## Next expected action

TASK 01 — create Makefile (`libasm.a`, all/clean/fclean/re), test `main` scaffold, ignore rules, and a header declaring the six mandatory functions. Do not implement the assembly functions yet beyond empty/failing stubs if required to prove the link path, or keep objects unimplemented until TASK 02.
