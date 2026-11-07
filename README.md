# Ft-libasm
Project for ft-libasm

make fclean
make

ar t libasm.a
nm -g --defined-only libasm.a | grep ft_

cc -Wall -Wextra -Werror main.c libasm.a -o test
./test

make


# Libasm Individual C Tests

`ft_calloc` を除くMandatory 6関数用の個別Cテストです。

## Compile examples

```bash
cc -Wall -Wextra -Werror test_ft_strlen.c ../libasm.a -o test_ft_strlen
cc -Wall -Wextra -Werror test_ft_strcpy.c ../libasm.a -o test_ft_strcpy
cc -Wall -Wextra -Werror test_ft_strcmp.c ../libasm.a -o test_ft_strcmp
cc -Wall -Wextra -Werror test_ft_write.c  ../libasm.a -o test_ft_write
cc -Wall -Wextra -Werror test_ft_read.c   ../libasm.a -o test_ft_read
cc -Wall -Wextra -Werror test_ft_strdup.c ../libasm.a -o test_ft_strdup
```

実行：

```bash
./test_ft_strlen
./test_ft_strcpy
./test_ft_strcmp
./test_ft_write
./test_ft_read
./test_ft_strdup
```

※ `../libasm.a` はテストディレクトリをrepository直下の子ディレクトリとして置いた場合の例です。
