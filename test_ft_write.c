#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

ssize_t ft_write(int fd, const void *buf, size_t count);

static int test_pipe_write(void)
{
    int fd[2];
    char buf[128] = {0};
    const char *msg = "Hello from ft_write!";
    size_t len = strlen(msg);

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    errno = 0;
    ssize_t ret = ft_write(fd[1], msg, len);
    int saved_errno = errno;

    close(fd[1]);

    ssize_t n = read(fd[0], buf, sizeof(buf) - 1);
    close(fd[0]);

    if (n < 0)
    {
        perror("read");
        return 1;
    }

    printf("[pipe success]\n");
    printf("  return      : %zd (expected %zu)\n", ret, len);
    printf("  errno       : %d\n", saved_errno);
    printf("  received    : \"%s\"\n", buf);

    if (ret != (ssize_t)len || (size_t)n != len || memcmp(buf, msg, len) != 0)
    {
        printf("  RESULT      : FAIL\n\n");
        return 1;
    }

    printf("  RESULT      : PASS\n\n");
    return 0;
}

static int test_zero_length(void)
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    errno = 0;
    ssize_t ret = ft_write(fd[1], "X", 0);
    int saved_errno = errno;

    close(fd[0]);
    close(fd[1]);

    printf("[zero length]\n");
    printf("  return      : %zd (expected 0)\n", ret);
    printf("  errno       : %d\n", saved_errno);

    if (ret != 0)
    {
        printf("  RESULT      : FAIL\n\n");
        return 1;
    }

    printf("  RESULT      : PASS\n\n");
    return 0;
}

static int test_invalid_fd(void)
{
    errno = 0;
    ssize_t libc_ret = write(-1, "X", 1);
    int libc_errno = errno;

    errno = 0;
    ssize_t ft_ret = ft_write(-1, "X", 1);
    int ft_errno = errno;

    printf("[invalid fd]\n");
    printf("  libc return : %zd\n", libc_ret);
    printf("  ft return   : %zd\n", ft_ret);
    printf("  libc errno  : %d (%s)\n", libc_errno, strerror(libc_errno));
    printf("  ft errno    : %d (%s)\n", ft_errno, strerror(ft_errno));

    if (libc_ret != ft_ret || libc_errno != ft_errno)
    {
        printf("  RESULT      : FAIL\n\n");
        return 1;
    }

    printf("  RESULT      : PASS\n\n");
    return 0;
}

int main(void)
{
    int failed = 0;

    failed += test_pipe_write();
    failed += test_zero_length();
    failed += test_invalid_fd();

    if (failed)
    {
        printf("ft_write: FAIL (%d case(s))\n", failed);
        return 1;
    }

    printf("ft_write: ALL PASS\n");
    return 0;
}
