# Libasm — `make re` 後のビルド・シンボル・動作確認手順

## 1. 目的

この資料は、Libasmプロジェクトで `make re` を実行した後に、

- `libasm.a` が正しく生成されているか
- Mandatory 7関数のObject FileがLibraryに含まれているか
- 各 `ft_*` symbol がexportされているか
- `main.c` から正しくlink・実行できるか
- `ft_calloc` のzero initializationとoverflow処理が正しいか
- 不要なrebuildが発生していないか
- Memory leakや不正なMemory accessがないか

を確認するための手順です。

対象となるMandatory関数は以下の7つです。

```text
ft_strlen
ft_strcpy
ft_strcmp
ft_write
ft_read
ft_strdup
ft_calloc
```

---

# 2. まず clean rebuild を行う

最初に、古いObject FileやLibraryが残った状態で確認しないようにします。

```bash
make re
```

またはより明示的に、

```bash
make fclean
make
```

でも構いません。

ビルド後に、

```bash
ls
```

などで `libasm.a` が存在することを確認します。

---

# 3. `libasm.a` に各 `.o` が含まれているか確認する

Static Libraryの中身は `ar` で確認できます。

```bash
ar t libasm.a
```

想定される結果の例：

```text
ft_strlen.o
ft_strcpy.o
ft_strcmp.o
ft_write.o
ft_read.o
ft_strdup.o
ft_calloc.o
```

ここで重要なのは、Version 6.0では `ft_calloc.o` もMandatoryとしてLibraryに含まれていることです。

もし `ft_calloc.o` が存在しない場合は、

- Makefileのsource list
- object list
- archive rule

を確認する必要があります。

---

# 4. 7つの `ft_*` symbol がexportされているか確認する

LibraryにObject Fileが入っていても、必要なsymbolが正しく定義されているとは限りません。

そのため `nm` を使用します。

```bash
nm -g --defined-only libasm.a | grep ft_
```

最低でも次の7つが確認できる必要があります。

```text
ft_strlen
ft_strcpy
ft_strcmp
ft_write
ft_read
ft_strdup
ft_calloc
```

`nm` は、

> Libraryの中にどのsymbolが定義されているか

を確認するためのコマンドです。

---

# 5. `main.c` と `libasm.a` をlinkして実行する

提出用またはテスト用の `main.c` がある場合は、Libraryと一緒にcompileします。

```bash
cc -Wall -Wextra -Werror main.c libasm.a -o test
```

実行：

```bash
./test
```

注意：

```text
-no-pie
```

は使用しません。

Subjectで禁止されているためです。

---

# 6. `ft_calloc` を単独で確認する

`ft_calloc` はVersion 6.0で追加されたMandatory関数なので、個別テストを行うことを推奨します。

以下のような一時的なテストファイルを作成できます。

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

void *ft_calloc(size_t nmemb, size_t size);

int main(void)
{
    size_t i;

    printf("=== normal calloc ===\n");

    unsigned char *p = ft_calloc(10, sizeof(unsigned char));

    if (!p)
    {
        perror("ft_calloc");
        return 1;
    }

    for (i = 0; i < 10; i++)
    {
        printf("%u ", p[i]);

        if (p[i] != 0)
        {
            printf("\nFAIL: memory is not zero\n");
            free(p);
            return 1;
        }
    }

    printf("\nPASS: all bytes are zero\n");

    p[0] = 42;
    p[9] = 100;

    printf("Writable: %u %u\n", p[0], p[9]);

    free(p);

    printf("\n=== overflow ===\n");

    errno = 0;

    void *overflow = ft_calloc(SIZE_MAX, 2);

    printf("ptr   = %p\n", overflow);
    printf("errno = %d (%s)\n", errno, strerror(errno));

    if (overflow == NULL)
        printf("PASS: overflow returned NULL\n");
    else
    {
        printf("FAIL: overflow allocation succeeded\n");
        free(overflow);
    }

    return 0;
}
```

例えばファイル名を、

```text
calloc_test.c
```

とした場合、

```bash
cc -Wall -Wextra -Werror calloc_test.c libasm.a -o calloc_test
./calloc_test
```

で実行できます。

---

# 7. `ft_calloc` の正常系で確認すること

通常のallocationでは、最低限以下を確認します。

```c
ft_calloc(1, 1)
ft_calloc(1, 10)
ft_calloc(10, 1)
ft_calloc(4, sizeof(int))
```

確認項目：

- pointerが正常に返る
- allocationされた範囲がすべて0
- Memoryへ書き込み可能
- `free()` 可能
- Buffer外へ書き込んでいない

成功したallocationについては、

```text
0 0 0 0 ...
```

のようにすべて0であることを確認します。

---

# 8. `ft_calloc` のoverflowを確認する

Version 6.0では、

```c
nmemb * size
```

の `size_t` overflowを自分で検出する必要があります。

最低限、以下のようなケースを確認します。

```c
ft_calloc(SIZE_MAX, 2)
ft_calloc(2, SIZE_MAX)
ft_calloc(SIZE_MAX, SIZE_MAX)
ft_calloc(SIZE_MAX / 2 + 1, 2)
```

overflow時に重要なのは、

```text
wrappedした小さい値をmallocに渡さない
```

ことです。

期待する結果：

```text
ptr = NULL
```

さらにtarget環境に合わせて `errno` も確認します。

---

# 9. overflow境界の直前も確認する

overflowするケースだけでなく、

> overflowしない最大付近の値

もロジック上確認すると安心です。

例えば、

```c
size_t n = SIZE_MAX / 2;
```

のような値について、

```text
n * 2
```

がoverflowしない範囲かどうかを確認します。

実際に極端な巨大Memoryをallocateする必要はありません。

重要なのは、overflow判定ロジックの境界が正しいかを確認することです。

---

# 10. zero-size allocation

次のようなケースも確認します。

```c
ft_calloc(0, 0)
ft_calloc(0, 1)
ft_calloc(1, 0)
ft_calloc(0, SIZE_MAX)
```

zero-size allocationでは、

```text
必ずNULLでなければならない
```

とは限りません。

そのため、

- crashしない
- 不正なzeroingをしない
- 返されたpointerを必要に応じて安全に扱える

ことを確認します。

---

# 11. Assemblyの実際のMachine Codeを確認する

各Object Fileがどのような命令になっているかは `objdump` で確認できます。

例えば、

```bash
objdump -d -Mintel ft_calloc.o
```

Object Fileが `obj/` にある場合は、

```bash
objdump -d -Mintel obj/ft_calloc.o
```

Library全体を見る場合：

```bash
objdump -d -Mintel libasm.a
```

長い場合：

```bash
objdump -d -Mintel libasm.a | less
```

`less` の中で、

```text
/ft_calloc
```

と入力すると `ft_calloc` を検索できます。

---

# 12. `make` のincremental buildを確認する

一度buildした後、sourceを変更せずにもう一度、

```bash
make
```

を実行します。

この時、

```text
何も再compileされない
```

のが理想です。

Subjectでは、

> 必要なものだけをrecompile/relinkする

ことが求められています。

毎回すべての `.s` がcompileされる場合はMakefileを確認します。

---

# 13. `clean`, `fclean`, `re` の確認

### `make clean`

```bash
make clean
```

期待：

- `.o` が削除される
- `libasm.a` は残る

### `make fclean`

```bash
make fclean
```

期待：

- `.o` が削除される
- `libasm.a` も削除される

### `make re`

```bash
make re
```

期待：

- 一度clean/fclean相当の処理
- その後fresh build
- `libasm.a` が再生成される

---

# 14. Memory check

Valgrindが利用可能な環境であれば、

```bash
valgrind --leak-check=full ./test
```

を実行します。

特に、

- `ft_strdup`
- `ft_calloc`

はMemory allocationを行うため、確認する価値があります。

確認項目：

- Invalid read
- Invalid write
- definitely lost
- indirectly lost

などがないことを確認します。

---

# 15. 最終確認用コマンド一覧

学校で最終確認する場合は、以下の順番で実行すると分かりやすいです。

```bash
make fclean
make

ar t libasm.a

nm -g --defined-only libasm.a | grep ft_

cc -Wall -Wextra -Werror main.c libasm.a -o test
./test

make
```

`ft_calloc` を個別確認する場合：

```bash
cc -Wall -Wextra -Werror calloc_test.c libasm.a -o calloc_test
./calloc_test
```

Valgrindが利用可能なら：

```bash
valgrind --leak-check=full ./test
```

---

# 16. コマンドの意味を覚える

Defenseではコマンドそのものを暗記するより、

```text
ar      → libasm.aの中にどのObject Fileが入っているか
nm      → どのsymbolが定義・exportされているか
cc      → main.cとlibasm.aをlinkできるか
./test  → 実際の動作
objdump → Assembly/Objectの実際の命令
valgrind→ Memory問題
```

という役割を理解しておく方が重要です。

---

# 17. 最終チェックリスト

提出前に次を確認します。

- [ ] `make re` が成功する
- [ ] `libasm.a` が生成される
- [ ] `ar t libasm.a` に7つのMandatory Objectがある
- [ ] `nm` で7つの `ft_*` symbolを確認できる
- [ ] `main.c` と `libasm.a` が正常にlinkできる
- [ ] `./test` が正常終了する
- [ ] `ft_strlen` PASS
- [ ] `ft_strcpy` PASS
- [ ] `ft_strcmp` PASS
- [ ] `ft_write` PASS
- [ ] `ft_read` PASS
- [ ] `ft_strdup` PASS
- [ ] `ft_calloc` PASS
- [ ] `ft_calloc` のzero initialization PASS
- [ ] `ft_calloc` のoverflow detection PASS
- [ ] 2回目の `make` で不要なrebuildがない
- [ ] `clean` が正しく動く
- [ ] `fclean` が正しく動く
- [ ] `re` が正しく動く
- [ ] `-no-pie` を使用していない
- [ ] 可能であればValgrindもPASS

この確認を行えば、単に「compileできる」だけではなく、

> Libraryに正しく含まれているか  
> Symbolとして見えているか  
> Cからlinkできるか  
> 実際に正しく動作するか

まで段階的に確認できます。
