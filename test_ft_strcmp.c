#include <stdio.h>
#include <string.h>

int ft_strcmp(const char *s1, const char *s2);

static int sign_of(int x)
{
    return (x > 0) - (x < 0);
}

static int test_case(const char *label, const char *s1, const char *s2)
{
    int expected = strcmp(s1, s2);
    int actual = ft_strcmp(s1, s2);

    printf("[%s]\n", label);
    printf("  s1      : \"%s\"\n", s1);
    printf("  s2      : \"%s\"\n", s2);
    printf("  libc    : %d\n", expected);
    printf("  ft      : %d\n", actual);

    if (sign_of(expected) != sign_of(actual))
    {
        printf("  RESULT  : FAIL (sign mismatch)\n\n");
        return 1;
    }

    printf("  RESULT  : PASS\n\n");
    return 0;
}

int main(void)
{
    int failed = 0;

    failed += test_case("equal empty", "", "");
    failed += test_case("equal normal", "abc", "abc");
    failed += test_case("first smaller", "abc", "abd");
    failed += test_case("first larger", "abd", "abc");
    failed += test_case("shorter", "abc", "abcd");
    failed += test_case("longer", "abcd", "abc");
    failed += test_case("empty vs nonempty", "", "a");
    failed += test_case("nonempty vs empty", "a", "");

    {
        const char s1[] = {(char)0xFF, '\0'};
        const char s2[] = {(char)0x01, '\0'};
        int expected = strcmp(s1, s2);
        int actual = ft_strcmp(s1, s2);

        printf("[unsigned byte: 0xFF vs 0x01]\n");
        printf("  libc    : %d\n", expected);
        printf("  ft      : %d\n", actual);

        if (sign_of(expected) != sign_of(actual))
        {
            printf("  RESULT  : FAIL\n\n");
            failed++;
        }
        else
            printf("  RESULT  : PASS\n\n");
    }

    if (failed)
    {
        printf("ft_strcmp: FAIL (%d case(s))\n", failed);
        return 1;
    }

    printf("ft_strcmp: ALL PASS\n");
    return 0;
}
