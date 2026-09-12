# Official Libasm Subject Extract

Source: `en.subject(libasm).pdf`
Version: 5.5
Extracted: 2026-09-12
Authority: the PDF remains authoritative. This file is a working extract only.

## Common Instructions (mandatory-relevant)

- Functions must not quit unexpectedly (segfault, bus error, double free, etc.) except on undefined behavior.
- Makefile must contain at least `$(NAME)`, `all`, `clean`, `fclean`, and `re`.
- Makefile must recompile/relink only necessary files.
- 64-bit assembly. Beware of the calling convention.
- No inline ASM. Must use `.s` files.
- Compile assembly with NASM.
- Intel syntax, not AT&T.
- Forbidden compilation flag: `-no-pie`.

## Mandatory Part

- Library name: `libasm.a`
- Must submit a `main` that tests the functions and compiles with the library.
- Rewrite in assembly:

  - `ft_strlen` (man 3 strlen)
  - `ft_strcpy` (man 3 strcpy)
  - `ft_strcmp` (man 3 strcmp)
  - `ft_write` (man 2 write)
  - `ft_read` (man 2 read)
  - `ft_strdup` (man 3 strdup; may call `malloc`)

- Check for errors during syscalls and handle them properly when needed.
- Code must set `errno` properly.
- Allowed to call extern `___error` or `errno_location`.

## Bonus Part (OUT OF SCOPE)

Bonus functions exist (`ft_atoi_base`, list helpers) but MUST NOT be implemented unless explicitly authorized.

## Expected libc prototypes (Linux glibc, this host)

```c
size_t  strlen(const char *s);
char   *strcpy(char *dest, const char *src);
int     strcmp(const char *s1, const char *s2);
ssize_t write(int fd, const void *buf, size_t n);
ssize_t read(int fd, void *buf, size_t nbytes);
char   *strdup(const char *s);
int    *__errno_location(void);
```

Linux syscall numbers (x86-64): `read=0`, `write=1`.
