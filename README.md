# Ft-libasm
Project for ft-libasm

make fclean
make

ar t libasm.a
nm -g --defined-only libasm.a | grep ft_

cc -Wall -Wextra -Werror main.c libasm.a -o test
./test

make
