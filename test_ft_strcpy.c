#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *ft_strcpy(char *dst, const char *src);

static int test_case(const char *label, const char *src)
{
    size_t len = strlen(src);
    char *expected = malloc(len + 1);
    char *actual = malloc(len + 1);

    if (!expected || !actual)
    {
        perror("malloc");
        free(expected);
        free(actual);
        return 1;
    }

    memset(expected, 0xAA, len + 1);
    memset(actual, 0xBB, len + 1);

    char *expected_ret = strcpy(expected, src);
    char *actual_ret = ft_strcpy(actual, src);

    printf("[%s]\n", label);
    printf("  src         : \"%s\"\n", src);
    printf("  expected dst: \"%s\"\n", expected);
    printf("  actual dst  : \"%s\"\n", actual);

    int failed = 0;

    if (strcmp(expected, actual) != 0)
    {
        printf("  content     : FAIL\n");
        failed = 1;
    }
    else
        printf("  content     : PASS\n");

    if (actual_ret != actual)
    {
        printf("  return ptr  : FAIL\n");
        failed = 1;
    }
    else
        printf("  return ptr  : PASS\n");

    if (expected_ret != expected)
    {
        printf("  libc sanity : FAIL\n");
        failed = 1;
    }

    if (actual[len] != '\0')
    {
        printf("  NUL term    : FAIL\n");
        failed = 1;
    }
    else
        printf("  NUL term    : PASS\n");

    printf("  RESULT      : %s\n\n", failed ? "FAIL" : "PASS");

    free(expected);
    free(actual);
    return failed;
}

int main(void)
{
    int failed = 0;

    failed += test_case("empty", "");
    failed += test_case("one char", "A");
    failed += test_case("normal", "Hello, Libasm!");
    failed += test_case("spaces", "a b c");
    failed += test_case("long", "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    if (failed)
    {
        printf("ft_strcpy: FAIL (%d case(s))\n", failed);
        return 1;
    }

    printf("ft_strcpy: ALL PASS\n");
    return 0;
}
