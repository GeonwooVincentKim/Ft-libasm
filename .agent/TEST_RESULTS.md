# Test Results

## TASK 00–10 — PASS

## TASK 11 — Mandatory subject compliance audit

Date: 2026-09-12
Environment: Ubuntu 24.04.4 LTS x86_64, NASM 2.16.01, gcc 13.3.0
Subject: en.subject(libasm).pdf Version 5.5
Result: PASS

Checklist:
- libasm.a name: PASS
- testing main links with library: PASS (PIE, no -no-pie)
- six mandatory functions as .s + archive symbols: PASS
- 64-bit ELF objects: PASS
- NASM Intel syntax (no AT&T %reg/$imm): PASS
- no inline ASM: PASS
- no bonus files/symbols: PASS
- no libft build/source dependency: PASS (AGENTS.md mentions libft only as a prohibition)
- errno via __errno_location: PASS
- malloc only in ft_strdup: PASS
- testhook 44/44: PASS

Failure explanation: none
