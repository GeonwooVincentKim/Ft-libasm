# Libasm Project State

Phase: INFRASTRUCTURE
Current Task: TASK 01
Latest Build: NOT_RUN
Latest Tests: TASK 00 environment audit PASS
ITa: NOT_RUN
ITb: NOT_RUN

Environment assumptions (authoritative for this Builder):
- Official subject: en.subject(libasm).pdf Version 5.5
- Evaluator target: 42 Tokyo Linux x86-64 (System V AMD64 ABI)
- Host: Ubuntu 24.04.4 LTS, kernel 6.12.94+, x86_64
- Toolchain: NASM 2.16.01, gcc 13.3.0, GNU Make 4.3, GNU binutils 2.42
- Object format: ELF64, Intel syntax, `nasm -f elf64`
- gcc default: PIE ON (DYN). Must never use `-no-pie`
- errno: `__errno_location` (Linux). Subject also allows `___error` (macOS) — not used
- Linux syscalls: SYS_read=0, SYS_write=1
- Syscall error: RAX in [-4095, -1] => errno = -RAX, return -1
- External calls (malloc / __errno_location): 16-byte stack alignment before CALL
- Arguments: rdi, rsi, rdx, rcx, r8, r9
- Callee-saved: rbx, rbp, r12-r15
- No existing .s sources, Makefile, header, or libasm.a
- Mandatory only: no bonus, no libft
- Persistent branch: automation/libasm (created from origin/master; origin/automation/libasm did not exist)

Unresolved Issues:
- None

Next Action:
- Execute TASK 01 build and test infrastructure
