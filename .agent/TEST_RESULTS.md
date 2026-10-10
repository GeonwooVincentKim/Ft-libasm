# Test Results

## TASK 00–14 — PASS (pre-calloc)

Previous: testhook 44 passed, 0 failed. ITa PASS. ITb PASS.

## TASK 15 — ft_calloc

Status: IN_PROGRESS (implementation added; validation pending)

Commands to run:
- `make fclean && make && make test`
- `valgrind --leak-check=full --show-leak-kinds=all ./testhook`
- `nm libasm.a`
- `objdump -d ft_calloc.o`
