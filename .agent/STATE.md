# Libasm Project State

Phase: IMPLEMENTATION
Current Task: TASK 02
Latest Build: PASS (make / make testhook / make re)
Latest Tests: TASK 01 infrastructure PASS
ITa: NOT_RUN
ITb: NOT_RUN

Environment assumptions:
- Official subject: en.subject(libasm).pdf Version 5.5
- Evaluator target: 42 Tokyo Linux x86-64 (System V AMD64 ABI)
- Host: Ubuntu 24.04.4 LTS, NASM 2.16.01, gcc 13.3.0, PIE default ON
- errno via `__errno_location`; Linux SYS_read=0 SYS_write=1
- Must never use `-no-pie`

Unresolved Issues:
- Function bodies are still placeholders (xor rax,rax; ret). Functional tests are expected to fail until TASK 02–07.

Next Action:
- Implement and verify ft_strlen
