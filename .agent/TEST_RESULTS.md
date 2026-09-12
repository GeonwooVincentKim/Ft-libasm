# Test Results

## TASK 00 — Repository and environment audit

Date: 2026-09-12
Environment: Ubuntu 24.04.4 LTS x86_64, NASM 2.16.01, gcc 13.3.0
Test scope: toolchain, ABI/PIE, libc prototypes, syscall numbers, repository inventory
Result: PASS

## TASK 01 — Build and test infrastructure

Date: 2026-09-12
Environment: Ubuntu 24.04.4 LTS x86_64, NASM 2.16.01, gcc 13.3.0
Test scope: Makefile rules, libasm.a, linkable mandatory symbols, PIE link, incremental rebuild, clean/fclean/re
Result: PASS

Commands:
- `make` -> nasm -f elf64 all six .s files, ar rcs libasm.a
- `nm -g libasm.a` -> T symbols: ft_strlen ft_strcpy ft_strcmp ft_write ft_read ft_strdup
- `make testhook` -> gcc -Wall -Wextra -Werror main.c -L. -lasm -o testhook
- `file testhook` -> ELF 64-bit LSB pie executable (no -no-pie)
- Incremental: touch ft_strlen.s && make rebuilt only ft_strlen.o and libasm.a
- `make clean` removed .o, left libasm.a
- `make fclean` removed libasm.a and testhook
- `make re` rebuilt libasm.a
- Makefile contains NAME, all, clean, fclean, re; no -no-pie

Failure explanation: none

Note: functional `./testhook` is not a TASK 01 gate. Placeholders return 0.
