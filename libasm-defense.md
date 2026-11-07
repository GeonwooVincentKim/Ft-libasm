# Libasm — C言語とx86-64 Assemblyの対応・Defense用解説

## 1. この資料について

この資料は、Libasmで実装したC標準関数とx86-64 Assemblyコードの対応関係を説明するためのDefense用メモです。

対象となるMandatory関数は以下の7つです。

- `ft_strlen`
- `ft_strcpy`
- `ft_strcmp`
- `ft_write`
- `ft_read`
- `ft_strdup`
- `ft_calloc`

特に、C言語では一行で書ける処理がAssemblyではどのようにレジスタ・メモリ・分岐命令へ分解されるのかを中心にまとめています。

---

## 2. C、Assembly、機械語の関係

Assemblyそのものが機械語というわけではありません。

大まかな流れは次のようになります。

```text
C source
   ↓
Compiler
   ↓
Assembly / intermediate representation
   ↓
Assembler
   ↓
Object file (.o)
   ↓
Linker
   ↓
Executable
```

Libasmでは自分でAssemblyを書くため、

```text
.s
 ↓ nasm
.o
 ↓ ar
libasm.a
```

という流れになります。

Assemblyは、CPUが実行する機械語を、人間が比較的読みやすい記号で記述したものと考えると分かりやすいです。

---

## 3. RegisterとMemoryは別物

CPUにはRegisterがあります。

例：

```text
rax
rbx
rcx
rdx
rsi
rdi
rsp
rbp
r8
...
```

RegisterはCPU内部に存在する非常に小さく高速な保存領域です。

一方、

```text
[rdi]
[rsi]
[rax + 1]
```

のような表現はMemoryを意味します。

例えば、

```asm
mov al, [rsi]
```

はC風に書くと、

```c
al = *rsi;
```

に近い意味です。

`rsi`に入っているのはアドレスであり、`[rsi]`と書くことで、そのアドレス先の値を読みます。

したがって、

```text
Register != Memory
```

です。

Registerの集合がMemoryになるわけではありません。

---

## 4. 64bit Registerとデータサイズ

x86-64では同じRegisterでも異なるサイズがあります。

```text
rax   64 bit
eax   32 bit
ax    16 bit
al     8 bit
```

同様に、

```text
rdx
edx
dx
dl
```

もそれぞれサイズが異なります。

AssemblyにはCのような、

```c
char
int
long
size_t
```

という型システムはありません。

その代わり、何bitのデータを操作するかを命令やRegisterで表します。

Memoryのサイズを明示する場合は、

```text
byte   8 bit
word  16 bit
dword 32 bit
qword 64 bit
```

を使います。

例えば、

```asm
cmp byte [rdi], 0
```

は、`rdi`が指している場所から1byteだけ読み、その値が0かどうかを比較しています。

---

## 5. Intel Syntaxの基本

このプロジェクトではIntel syntaxを使用します。

基本形は、

```asm
instruction destination, source
```

です。

例えば、

```asm
mov rax, rbx
```

は、

```c
rax = rbx;
```

のような意味です。

---

## 6. なぜMemoryからMemoryへ直接コピーしないのか

レビューで出た例：

```asm
mov dl, byte [rsi]
mov byte [rdi], dl
```

これは、

```text
Memory
  ↓
Register
  ↓
Memory
```

という処理です。

Cでは、

```c
*dst = *src;
```

と一行で書けます。

しかし通常のx86 `mov` 命令では、

```asm
mov [rdi], [rsi]
```

のような一般的なMemory-to-Memoryコピーはできません。

そのため一度Registerへ読み込みます。

```asm
mov dl, byte [rsi]
```

C風：

```c
tmp = *src;
```

その後、

```asm
mov byte [rdi], dl
```

C風：

```c
*dst = tmp;
```

となります。

※ `movsb` のようなMemory間コピー用のstring instructionもありますが、通常の `mov` とは別の仕組みです。

---

## 7. System V AMD64 Calling Convention

関数を呼ぶ時、

```c
foo(a, b, c);
```

のような引数がAssemblyコード上に直接見えないことがあります。

理由は、x86-64 Linuxでは最初の引数を主にRegisterで渡すためです。

| Argument | Register |
|---|---|
| 1 | rdi |
| 2 | rsi |
| 3 | rdx |
| 4 | rcx |
| 5 | r8 |
| 6 | r9 |

Return valueは通常 `rax` に入ります。

例えば、

```c
write(fd, buf, size);
```

なら、

```text
rdi = fd
rsi = buf
rdx = size
```

となります。

そのため、

```asm
call malloc
```

だけを見ると引数がないように見えますが、その直前に

```asm
mov rdi, rax
call malloc
```

のように書いてあれば、

```c
malloc(rax);
```

に相当します。

`call`命令そのものに変数名を書く必要はありません。

---

## 8. section / global / extern

### `section .text`

主に実行コードを配置する領域です。

```asm
section .text
```

関数本体は通常ここに置きます。

### `section .data`

初期値を持つ静的データを配置します。

```asm
section .data
message db "hello", 0
```

### `section .bss`

初期化されていない静的データを配置します。

### `global`

```asm
global ft_strlen
```

は、このsymbolを外部から参照できるようにするという意味です。

### `extern`

```asm
extern malloc
```

は、`malloc`がこのファイル内には実装されていないが、外部Libraryに存在することを表します。

---

## 9. LabelとJump

AssemblyにはCの `while` や `if` そのものはありません。

代わりに、

```asm
.loop:
```

のようなLabelとJumpを使います。

`.loop`はbooleanではありません。

単純に、コード中のある位置を示す名前です。

例えば、

```asm
cmp byte [rdi + rax], 0
je .done
```

では、`cmp` がCPUのflagを更新します。

比較結果が等しい場合、Zero Flagが1になります。

`je` は Jump if Equal なので、その場合 `.done` へ移動します。

C風に書くと、

```c
if (s[i] == '\0')
    goto done;
```

に近い処理です。

---

## 10. XORはなぜ使うのか

例えば、

```asm
xor rax, rax
```

があります。

XORには、

```text
A XOR A = 0
```

という性質があります。

そのため、

```asm
xor rax, rax
```

は実質的に、

```c
rax = 0;
```

のようなRegister初期化として使えます。

`ft_strlen`では文字列長カウンタを0から始める用途に使えます。

---

## 11. ft_strlen

Cで表すと概念的には、

```c
size_t ft_strlen(const char *s)
{
    size_t i = 0;

    while (s[i] != '\0')
        i++;

    return i;
}
```

です。

Assemblyでは概念的に、

```asm
xor rax, rax

.loop:
    cmp byte [rdi + rax], 0
    je .done

    inc rax
    jmp .loop

.done:
    ret
```

となります。

Calling Conventionから、

```text
rdi = s
rax = return value
```

なので、`rax`をそのままlength counterとして使えます。

---

## 12. ft_strcpy

Cでは概念的に、

```c
char *ft_strcpy(char *dst, const char *src)
{
    char *ret = dst;

    while (1)
    {
        *dst = *src;

        if (*src == '\0')
            break;

        dst++;
        src++;
    }

    return ret;
}
```

です。

Calling Conventionでは、

```text
rdi = dst
rsi = src
```

です。

コピーは概念的に、

```asm
mov dl, byte [rsi]
mov byte [rdi], dl
```

となります。

つまり、

```c
unsigned char temp = *src;
*dst = temp;
```

です。

---

## 13. ft_strcmpとmovzx

`strcmp`では文字を実質的に `unsigned char` として比較します。

そこで、

```asm
movzx eax, byte [rdi]
```

のような命令が有効です。

`movzx` は Move with Zero Extension です。

例えば `0xFF` という1byte値を32bit Registerへ読み込むと、

```text
0x000000FF
```

となります。

つまり符号付きの `-1` ではなく `255` として扱えます。

Cでは、

```c
(unsigned char)*s1
```

に近い考え方です。

概念的には、

```c
int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (unsigned char)*s1 == (unsigned char)*s2)
    {
        s1++;
        s2++;
    }

    return (unsigned char)*s1 - (unsigned char)*s2;
}
```

となります。

重要なのは、`strcmp` が必ず `-1 / 0 / 1` を返す必要はないことです。

必要なのは、

```text
< 0
= 0
> 0
```

という符号の意味です。

---

## 14. ft_write

Cでは、

```c
ssize_t ft_write(int fd, const void *buf, size_t count);
```

です。

Linux x86-64のsystem callでは概念的に、

```text
rax = syscall number
rdi = fd
rsi = buf
rdx = count
```

として `syscall` を実行します。

成功時は、書き込んだbyte数が `rax` に返ります。

失敗時は、Libcの `write` と同様に、

```text
return = -1
errno = error
```

となるよう処理する必要があります。

---

## 15. ft_read

`read`も同じ考え方です。

```c
ssize_t ft_read(int fd, void *buf, size_t count);
```

Registerは、

```text
rdi = fd
rsi = buf
rdx = count
```

です。

成功時、

```text
rax = 読み込んだbyte数
```

EOFでは、

```text
rax = 0
```

となります。

Error時には、

```text
return = -1
errno = error
```

となるように処理します。

---

## 16. ft_strdup

Cでは概念的に、

```c
char *ft_strdup(const char *src)
{
    size_t len;
    char *dst;

    len = ft_strlen(src) + 1;
    dst = malloc(len);

    if (dst == NULL)
        return NULL;

    ft_strcpy(dst, src);
    return dst;
}
```

です。

Assemblyでは、

```asm
call ft_strlen
call malloc
call ft_strcpy
```

のように別関数を呼ぶことがあります。

ここで重要なのが、

- Calling Convention
- Register preservation
- Stack alignment

です。

例えば `src` が最初 `rdi` に入っていても、`call malloc` の後も `rdi` が同じ値である保証はありません。

`rdi`はCaller-saved Registerだからです。

そのため、後でも必要な値はstackやcallee-saved registerなどに保存する必要があります。

---

## 17. Caller-saved / Callee-saved Registers

代表的なCaller-saved Register：

```text
rax
rcx
rdx
rsi
rdi
r8
r9
r10
r11
```

別関数を `call` した後、これらの値は変わっている可能性があります。

代表的なCallee-saved Register：

```text
rbx
rbp
r12
r13
r14
r15
```

これらを自分の関数内で変更した場合は、return前に元の値へ戻す必要があります。

---

## 18. Stack Alignment

`malloc` のような外部C関数を `call` する時はStack alignmentも重要です。

`push` の回数などによって `rsp` のalignmentが変わるため、外部関数を呼ぶ直前のstack状態を確認する必要があります。

`ft_strlen` のようなleaf functionより、`ft_strdup` や `ft_calloc` のように別関数を呼ぶ関数の方がABIを意識する必要があります。

---

## 19. ft_calloc

Subject Version 6.0でMandatoryに追加された関数です。

Cでは概念的に、

```c
void *ft_calloc(size_t nmemb, size_t size)
{
    size_t total;
    void *ptr;

    if (multiplication_overflows(nmemb, size))
        return NULL;

    total = nmemb * size;

    ptr = malloc(total);

    if (ptr == NULL)
        return NULL;

    memset(ptr, 0, total);

    return ptr;
}
```

となります。

重要なのは、

```c
nmemb * size
```

のoverflowです。

---

## 20. callocでoverflow確認が必要な理由

64bitの `size_t` の最大値を `SIZE_MAX` とすると、

```c
nmemb = SIZE_MAX;
size = 2;
```

のようなケースでは、数学的には64bitに収まらない値になります。

その結果がwrap aroundすると、本来必要なサイズより小さい値を `malloc` に渡してしまう可能性があります。

そのため、`malloc` を呼ぶ前にoverflowを検出する必要があります。

---

## 21. ft_callocのoverflow検出

Cでは例えば、

```c
if (nmemb != 0 && size > SIZE_MAX / nmemb)
    return NULL;
```

のように確認できます。

Assemblyではunsigned multiplicationのoverflowを利用する方法もあります。

概念的に、

```asm
mov rax, nmemb
mul size
```

では、結果が `RDX:RAX` に入ります。

```text
RDX:RAX = RAX * size
```

上位64bitである `RDX` が0でなければ、64bitの `size_t` に収まっていないためoverflowと判断できます。

実装によっては `CF` / `OF` flagを利用する方法もあります。

---

## 22. ft_callocのzero initialization

`calloc`は確保したMemoryを0で初期化します。

Cでは、

```c
for (size_t i = 0; i < total; i++)
    ptr[i] = 0;
```

のように表現できます。

Assemblyでは概念的に、

```asm
xor rcx, rcx

.zero_loop:
    cmp rcx, total
    je .done

    mov byte [ptr + rcx], 0

    inc rcx
    jmp .zero_loop
```

のような形です。

重要なのは、`total` bytesの範囲内だけを書き込むことです。

---

## 23. zero-size calloc

例えば、

```c
calloc(0, 10);
calloc(10, 0);
calloc(0, 0);
```

のようなケースがあります。

この場合、必ず `NULL` を返さなければならないとは限りません。

そのため、zero-size allocationについて特定のpointer値を前提にしないことが重要です。

---

## 24. cmp と test

例えば、

```asm
cmp rax, 0
```

は `rax` と0を比較してflagを更新します。

一方、

```asm
test rax, rax
```

もpointerがNULLかどうかの確認によく使われます。

```asm
test rax, rax
je .error
```

はC風に書くと、

```c
if (ptr == NULL)
```

です。

---

## 25. Assemblyでは「型」より「何bit操作するか」

Cでは、

```c
char
short
int
long
size_t
```

のような型があります。

Assemblyでは、

```text
8 bit
16 bit
32 bit
64 bit
```

というCPU上のサイズが中心です。

そのため、

```asm
mov al, ...
mov eax, ...
mov rax, ...
```

はすべて `mov` ですが、扱うサイズが異なります。

---

## 26. CとAssemblyの対応まとめ

| C | Assemblyでの考え方 |
|---|---|
| variable | register / memory |
| pointer | address stored in register/memory |
| `*ptr` | `[register]` |
| assignment | `mov` |
| `if` | `cmp/test` + conditional jump |
| `while` | label + compare + jump |
| `i++` | `inc` / `add` |
| return | `rax` + `ret` |
| function argument | mainly registers |
| function call | `call` |
| malloc | external function call |
| syscall | register setup + `syscall` |

---

## 27. Defenseで聞かれそうな質問

### Q1. AssemblyとMachine Codeは同じですか？

完全に同じではありません。

Assemblyは人間が読めるsymbolic representationで、AssemblerがMachine Codeへ変換します。

### Q2. `[rsi]` は何ですか？

`rsi`というRegisterそのものではなく、`rsi`に格納されたアドレスが指しているMemoryです。

Cでは `*src` に近い意味です。

### Q3. なぜ `mov [rdi], [rsi]` と書かないのですか？

通常のx86 `mov` は一般的なMemory-to-Memory転送をサポートしていないため、一度Registerへ読み込みます。

```asm
mov dl, [rsi]
mov [rdi], dl
```

### Q4. `movzx` は何のためですか？

小さい値を大きいRegisterへコピーしながら上位bitを0で埋めます。

`strcmp` でbyteを `unsigned char` として扱うために有効です。

### Q5. `xor rax, rax` は何をしていますか？

`rax`を0にしています。

`A XOR A = 0` の性質を利用しています。

### Q6. `.loop` はbooleanですか？

違います。

`.loop` はコード上のLabel、つまりJump先の位置です。

### Q7. `je` はいつJumpしますか？

直前の `cmp` や `test` の結果によってZero Flagが1になった場合です。

### Q8. `call malloc` に引数が見えないのはなぜですか？

System V AMD64 ABIでは引数をRegisterで渡すためです。

最初の引数であれば通常 `rdi` に設定してから `call malloc` を実行します。

### Q9. `ft_strdup` でRegister保存が重要なのはなぜですか？

`malloc` など別関数を `call` するとCaller-saved Registerの内容が変わる可能性があるからです。

後で必要な値は保存しておく必要があります。

### Q10. `ft_calloc` でoverflowをmallocより先に確認する理由は？

`nmemb * size` が64bitを超えると値がwrapし、本来より小さな値を `malloc` に渡す可能性があるからです。

そのためallocation前にoverflowを検出します。

---

## 28. 最後に

Libasmで重要なのは、Assemblyコードを暗記することではありません。

Cの処理を、

```text
Cの処理
   ↓
どのRegisterに何を入れるか
   ↓
どのMemoryを読む/書くか
   ↓
どのFlagを見るか
   ↓
どこへJumpするか
```

というCPUレベルの処理へ分解して理解することが重要です。

例えばCでは、

```c
while (*src)
    *dst++ = *src++;
```

のように短く書ける処理も、Assemblyでは、

```text
addressを読む
byteを読む
byteを書く
NULか比較する
pointerを進める
jumpする
```

という小さな操作に分解されます。

この対応関係を理解していれば、Defenseでもコードを暗記するのではなく、
「なぜこの命令を使っているのか」を自分の言葉で説明できるようになります。
