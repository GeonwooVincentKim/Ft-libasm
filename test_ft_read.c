#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

ssize_t ft_read(int fd, void *buf, size_t count);

static int test_pipe_read(void)
{
    int fd[2];
    const char *msg = "Hello from ft_read!";
    size_t len = strlen(msg);
    char buf[128] = {0};

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    if (write(fd[1], msg, len) != (ssize_t)len)
    {
        perror("write");
        close(fd[0]);
        close(fd[1]);
        return 1;
    }

    close(fd[1]);

    errno = 0;
    ssize_t ret = ft_read(fd[0], buf, len);
    int saved_errno = errno;
    close(fd[0]);

    printf("[pipe success]\n");
    printf("  return      : %zd (expected %zu)\n", ret, len);
    printf("  errno       : %d\n", saved_errno);
    printf("  received    : \"%s\"\n", buf);

    if (ret != (ssize_t)len || memcmp(buf, msg, len) != 0)
    {
        printf("  RESULT      : FAIL\n\n");
        return 1;
    }

    printf("  RESULT      : PASS\n\n");
    return 0;
}

static int test_eof(void)
{
    int fd[2];
    char buf[8] = {0};

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    close(fd[1]);

    errno = 0;
    ssize_t ret = ft_read(fd[0], buf, sizeof(buf));
    int saved_errno = errno;
    close(fd[0]);

    printf("[EOF]\n");
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

static int test_zero_length(void)
{
    int fd[2];
    char buf[8] = {0};

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    errno = 0;
    ssize_t ret = ft_read(fd[0], buf, 0);
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
    char libc_buf[8] = {0};
    char ft_buf[8] = {0};

    errno = 0;
    ssize_t libc_ret = read(-1, libc_buf, sizeof(libc_buf));
    int libc_errno = errno;

    errno = 0;
    ssize_t ft_ret = ft_read(-1, ft_buf, sizeof(ft_buf));
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

    failed += test_pipe_read();
    failed += test_eof();
    failed += test_zero_length();
    failed += test_invalid_fd();

    if (failed)
    {
        printf("ft_read: FAIL (%d case(s))\n", failed);
        return 1;
    }

    printf("ft_read: ALL PASS\n");
    return 0;
}
