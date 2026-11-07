#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ft_strdup(const char *s);

static int test_case(const char *label, const char *src)
{
    char *libc_copy = strdup(src);
    char *ft_copy = ft_strdup(src);

    printf("[%s]\n", label);
    printf("  src         : \"%s\"\n", src);

    if (!libc_copy || !ft_copy)
    {
        printf("  allocation  : FAIL\n\n");
        free(libc_copy);
        free(ft_copy);
        return 1;
    }

    int failed = 0;

    printf("  libc copy   : \"%s\"\n", libc_copy);
    printf("  ft copy     : \"%s\"\n", ft_copy);

    if (strcmp(libc_copy, ft_copy) != 0)
    {
        printf("  content     : FAIL\n");
        failed = 1;
    }
    else
        printf("  content     : PASS\n");

    if (ft_copy == src)
    {
        printf("  allocation  : FAIL (same pointer as source)\n");
        failed = 1;
    }
    else
        printf("  allocation  : PASS (independent pointer)\n");

    if (strlen(ft_copy) != strlen(src))
    {
        printf("  length      : FAIL\n");
        failed = 1;
    }
    else
        printf("  length      : PASS\n");

    if (strlen(src) > 0)
    {
        char original = src[0];
        ft_copy[0] = (ft_copy[0] == 'X') ? 'Y' : 'X';

        if (src[0] != original)
        {
            printf("  independence: FAIL\n");
            failed = 1;
        }
        else
            printf("  independence: PASS\n");
    }

    printf("  RESULT      : %s\n\n", failed ? "FAIL" : "PASS");

    free(libc_copy);
    free(ft_copy);
    return failed;
}

int main(void)
{
    int failed = 0;

    failed += test_case("empty", "");
    failed += test_case("one char", "A");
    failed += test_case("normal", "Hello, Libasm!");
    failed += test_case("spaces", "hello world with spaces");
    failed += test_case(
        "long",
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
    );

    if (failed)
    {
        printf("ft_strdup: FAIL (%d case(s))\n", failed);
        return 1;
    }

    printf("ft_strdup: ALL PASS\n");
    return 0;
}
