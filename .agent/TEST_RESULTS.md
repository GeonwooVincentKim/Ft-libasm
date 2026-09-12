# Test results

## TASK 00 — Environment audit probes

Date: 2026-09-12

### Command

```text
nasm -v
nasm -f elf64 -o .agent/_smoke.o .agent/_smoke.s
gcc -o .agent/_smoke .agent/_smoke.c .agent/_smoke.o
./.agent/_smoke
readelf -h .agent/_smoke
```

Probe sources were deleted after the run. They are not part of the project.

### Environment

- OS: Ubuntu 24.04.4 LTS (Noble), x86_64
- Kernel: 6.12.94+
- gcc: 13.3.0 (Ubuntu 13.3.0-6ubuntu2~24.04.1), default PIE (`__PIE__=2`)
- NASM: 2.16.01 (installed this session; was absent from the snapshot)
- glibc: 2.39
- Make: GNU Make 4.3
- Subject: `en.subject(libasm).pdf` version 5.5, 12 pages
- Working tree HEAD at audit start: `628c086` (Add Libasm pdf)
- Branch: `cursor/libasm-development-process-510c`

### Test scope

Environment only. No mandatory Libasm function tests.

Checks:

1. NASM is installable and reports 2.16.01
2. Intel-syntax `.s` assembles to ELF64
3. Link succeeds without `-no-pie`
4. Resulting binary is ELF64 PIE (`DYN`)
5. Trivial length loop matches libc `strlen` on `"hello"`
6. glibc exports `__errno_location` and `malloc`
7. x86-64 `unistd_64.h` defines `__NR_read 0` and `__NR_write 1`

### PASS/FAIL

PASS (environment probes)

Mandatory function suite: not executed (no implementation)

### Relevant output

```text
NASM version 2.16.01
smoke=5 libc=5
Class: ELF64
Type:  DYN (Position-Independent Executable file)
Machine: Advanced Micro Devices X86-64
```

Linker note (non-blocking):

```text
missing .note.GNU-stack section implies executable stack
```

`nm -D libc.so.6` includes:

- `__errno_location@@GLIBC_2.2.5`
- `malloc@@GLIBC_2.2.5`

### Failure explanation

None for the environment probes.

Man pages are absent on this minimized image (`unminimize` not run). Prototypes confirmed from headers:

- `size_t strlen(const char *)`
- `char *strcpy(char *restrict, const char *restrict)`
- `int strcmp(const char *, const char *)`
- `ssize_t write(int, const void *, size_t)`
- `ssize_t read(int, void *, size_t)`
- `char *strdup(const char *)`
- `void *malloc(size_t)`
