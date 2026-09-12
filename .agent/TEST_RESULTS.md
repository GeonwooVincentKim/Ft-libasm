# Test Results

## TASK 00–09 — PASS

## TASK 10 — Makefile / clean-build audit

Date: 2026-09-12
Environment: Ubuntu 24.04.4 LTS x86_64, NASM 2.16.01, GNU Make 4.3
Test scope: required rules, incremental rebuild, clean, fclean, re, no -no-pie, no libft
Result: PASS

Commands / evidence:
- Rules present: NAME, all, $(NAME), clean, fclean, re
- `make` then `make` -> Nothing to be done for 'all'
- touch ft_strcmp.s && make -> only ft_strcmp.o + libasm.a updated
- clean: objects gone, libasm.a and testhook kept
- fclean: libasm.a, testhook, objects gone
- re: full rebuild of libasm.a
- ASFLAGS = -f elf64; no -no-pie; no libft references

Failure explanation: none
