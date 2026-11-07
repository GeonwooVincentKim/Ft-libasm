#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>

void *ft_calloc(size_t nmemb, size_t size);

static int check_all_zero(const unsigned char *p, size_t total)
{
    size_t i;

    for (i = 0; i < total; i++)
    {
        if (p[i] != 0)
            return 0;
    }
    return 1;
}

static int test_normal(const char *label, size_t nmemb, size_t size)
{
    size_t total;
    unsigned char *p;

    if (nmemb != 0 && size > SIZE_MAX / nmemb)
    {
        printf("[%s]\n", label);
        printf("  test setup  : invalid (overflow)\n");
        printf("  RESULT      : FAIL\n\n");
        return 1;
    }

    total = nmemb * size;

    errno = 0;
    p = ft_calloc(nmemb, size);

    printf("[%s]\n", label);
    printf("  nmemb       : %zu\n", nmemb);
    printf("  size        : %zu\n", size);
    printf("  total       : %zu\n", total);
    printf("  ptr         : %p\n", (void *)p);
    printf("  errno       : %d", errno);

    if (errno != 0)
        printf(" (%s)", strerror(errno));
    printf("\n");

    if (total != 0 && p == NULL)
    {
        printf("  allocation  : FAIL\n");
        printf("  RESULT      : FAIL\n\n");
        return 1;
    }

    /*
     * For zero-sized allocations, C does not require one exact pointer value.
     * NULL or a unique freeable pointer may both be valid depending on libc.
     */
    if (total == 0)
    {
        printf("  zero-size   : PASS (no fixed pointer value required)\n");
        free(p);
        printf("  RESULT      : PASS\n\n");
        return 0;
    }

    if (!check_all_zero(p, total))
    {
        printf("  zero init   : FAIL\n");
        free(p);
        printf("  RESULT      : FAIL\n\n");
        return 1;
    }

    printf("  zero init   : PASS\n");

    /*
     * Verify the memory can actually be written.
     */
    p[0] = 0x2A;
    p[total - 1] = 0x64;

    if (p[0] != 0x2A || p[total - 1] != 0x64)
    {
        printf("  writable    : FAIL\n");
        free(p);
        printf("  RESULT      : FAIL\n\n");
        return 1;
    }

    printf("  writable    : PASS\n");

    free(p);
    printf("  freeable    : PASS\n");
    printf("  RESULT      : PASS\n\n");
    return 0;
}

static int test_overflow(const char *label, size_t nmemb, size_t size)
{
    void *libc_ptr;
    void *ft_ptr;
    int libc_errno;
    int ft_errno;
    int failed = 0;

    /*
     * Call libc with runtime values rather than compile-time constants.
     * This avoids compiler diagnostics for obviously impossible allocations.
     */
    errno = 0;
    libc_ptr = calloc(nmemb, size);
    libc_errno = errno;

    errno = 0;
    ft_ptr = ft_calloc(nmemb, size);
    ft_errno = errno;

    printf("[%s]\n", label);
    printf("  nmemb       : %zu\n", nmemb);
    printf("  size        : %zu\n", size);
    printf("  libc ptr    : %p\n", libc_ptr);
    printf("  ft ptr      : %p\n", ft_ptr);
    printf("  libc errno  : %d", libc_errno);
    if (libc_errno != 0)
        printf(" (%s)", strerror(libc_errno));
    printf("\n");

    printf("  ft errno    : %d", ft_errno);
    if (ft_errno != 0)
        printf(" (%s)", strerror(ft_errno));
    printf("\n");

    /*
     * Subject v6.0 requires detecting nmemb * size overflow explicitly.
     * Therefore ft_calloc must not succeed with a wrapped allocation size.
     */
    if (ft_ptr != NULL)
    {
        printf("  overflow    : FAIL (ft_calloc returned non-NULL)\n");
        failed = 1;
    }
    else
        printf("  overflow    : PASS (NULL returned)\n");

    /*
     * Compare errno with libc when libc also reports failure.
     * On the normal Linux evaluator environment, calloc overflow should
     * typically produce ENOMEM.
     */
    if (libc_ptr == NULL && libc_errno != ft_errno)
    {
        printf("  errno match : FAIL\n");
        failed = 1;
    }
    else if (libc_ptr == NULL)
        printf("  errno match : PASS\n");
    else
        printf("  errno match : SKIP (libc unexpectedly returned non-NULL)\n");

    free(libc_ptr);
    free(ft_ptr);

    printf("  RESULT      : %s\n\n", failed ? "FAIL" : "PASS");
    return failed;
}

int main(void)
{
    int failed = 0;
    size_t half_plus_one = SIZE_MAX / 2 + 1;

    printf("========================================\n");
    printf("ft_calloc tests\n");
    printf("========================================\n\n");

    /*
     * Normal allocations
     */
    failed += test_normal("normal: 1 x 1", 1, 1);
    failed += test_normal("normal: 10 x 1", 10, 1);
    failed += test_normal("normal: 1 x 32", 1, 32);
    failed += test_normal("normal: 4 x sizeof(int)", 4, sizeof(int));
    failed += test_normal("normal: 16 x sizeof(long)", 16, sizeof(long));
    failed += test_normal("normal: 128 x 8", 128, 8);

    /*
     * Zero-sized allocations
     */
    failed += test_normal("zero-size: 0 x 0", 0, 0);
    failed += test_normal("zero-size: 0 x 1", 0, 1);
    failed += test_normal("zero-size: 1 x 0", 1, 0);
    failed += test_normal("zero-size: 0 x SIZE_MAX", 0, SIZE_MAX);

    /*
     * Overflow cases required for robust v6.0 validation
     */
    failed += test_overflow("overflow: SIZE_MAX x 2", SIZE_MAX, 2);
    failed += test_overflow("overflow: 2 x SIZE_MAX", 2, SIZE_MAX);
    failed += test_overflow("overflow: SIZE_MAX x SIZE_MAX", SIZE_MAX, SIZE_MAX);
    failed += test_overflow(
        "overflow: (SIZE_MAX / 2 + 1) x 2",
        half_plus_one,
        2
    );
    failed += test_overflow(
        "overflow: 2 x (SIZE_MAX / 2 + 1)",
        2,
        half_plus_one
    );

    printf("========================================\n");

    if (failed)
    {
        printf("ft_calloc: FAIL (%d case(s))\n", failed);
        return 1;
    }

    printf("ft_calloc: ALL PASS\n");
    return 0;
}
