#include <stdio.h>
#include <string.h>
#include <stddef.h>

size_t ft_strlen(const char *s);

static int test_case(const char *label, const char *s)
{
    size_t expected = strlen(s);
    size_t actual = ft_strlen(s);

    printf("[%s]\n", label);
    printf("  expected: %zu\n", expected);
    printf("  actual  : %zu\n", actual);

    if (expected != actual)
    {
        printf("  RESULT  : FAIL\n\n");
        return 1;
    }

    printf("  RESULT  : PASS\n\n");
    return 0;
}

int main(void)
{
    int failed = 0;

    failed += test_case("empty", "");
    failed += test_case("one char", "A");
    failed += test_case("normal", "Hello, Libasm!");
    failed += test_case("spaces", "   abc   ");
    failed += test_case(
        "long",
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
    );

    if (failed)
    {
        printf("ft_strlen: FAIL (%d case(s))\n", failed);
        return 1;
    }

    printf("ft_strlen: ALL PASS\n");
    return 0;
}
