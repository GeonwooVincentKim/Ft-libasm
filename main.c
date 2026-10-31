#include "libasm.h"

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	g_pass;
static int	g_fail;

static void	expect(int ok, const char *name)
{
	if (ok)
	{
		g_pass++;
		printf("PASS  %s\n", name);
	}
	else
	{
		g_fail++;
		printf("FAIL  %s\n", name);
	}
}

static int	sign_of(int n)
{
	if (n < 0)
		return (-1);
	if (n > 0)
		return (1);
	return (0);
}

static void	test_strlen(void)
{
	const char	*empty = "";
	const char	*single = "A";
	const char	*normal = "42 Tokyo Libasm";
	char		long_str[4097];
	size_t		i;

	memset(long_str, 'x', 4096);
	long_str[4096] = '\0';
	expect(ft_strlen(empty) == strlen(empty), "strlen empty");
	expect(ft_strlen(single) == strlen(single), "strlen single");
	expect(ft_strlen(normal) == strlen(normal), "strlen normal");
	expect(ft_strlen(long_str) == strlen(long_str), "strlen long");
	i = 0;
	while (i < 256)
	{
		long_str[i] = (char)('a' + (i % 26));
		i++;
	}
	long_str[256] = '\0';
	expect(ft_strlen(long_str) == 256, "strlen 256");
}

static void	test_strcpy(void)
{
	char		dst[128];
	char		ref[128];
	const char	*empty = "";
	const char	*normal = "hello, libasm";
	char		*ret;

	memset(dst, 'Z', sizeof(dst));
	memset(ref, 'Z', sizeof(ref));
	ret = ft_strcpy(dst, empty);
	strcpy(ref, empty);
	expect(ret == dst, "strcpy empty returns dest");
	expect(strcmp(dst, ref) == 0, "strcpy empty content");
	expect(dst[0] == '\0', "strcpy empty NUL");

	memset(dst, 'Z', sizeof(dst));
	memset(ref, 'Z', sizeof(ref));
	ret = ft_strcpy(dst, normal);
	strcpy(ref, normal);
	expect(ret == dst, "strcpy normal returns dest");
	expect(strcmp(dst, ref) == 0, "strcpy normal content");
	expect(dst[strlen(normal)] == '\0', "strcpy normal NUL");
}

static void	test_strcmp(void)
{
	char	high[2];
	char	low[2];

	expect(sign_of(ft_strcmp("", "")) == sign_of(strcmp("", "")),
		"strcmp both empty");
	expect(sign_of(ft_strcmp("abc", "abc")) == sign_of(strcmp("abc", "abc")),
		"strcmp identical");
	expect(sign_of(ft_strcmp("abc", "abd")) == sign_of(strcmp("abc", "abd")),
		"strcmp first smaller");
	expect(sign_of(ft_strcmp("abd", "abc")) == sign_of(strcmp("abd", "abc")),
		"strcmp first larger");
	expect(sign_of(ft_strcmp("", "a")) == sign_of(strcmp("", "a")),
		"strcmp empty vs nonempty");
	expect(sign_of(ft_strcmp("a", "")) == sign_of(strcmp("a", "")),
		"strcmp nonempty vs empty");
	expect(sign_of(ft_strcmp("abc", "abcd")) == sign_of(strcmp("abc", "abcd")),
		"strcmp different lengths");
	expect(sign_of(ft_strcmp("abcd", "abc")) == sign_of(strcmp("abcd", "abc")),
		"strcmp prefix longer");
	high[0] = (char)0xFF;
	high[1] = '\0';
	low[0] = (char)0x01;
	low[1] = '\0';
	expect(sign_of(ft_strcmp(low, high)) == sign_of(strcmp(low, high)),
		"strcmp unsigned 0x01 vs 0xFF");
	expect(sign_of(ft_strcmp(high, low)) == sign_of(strcmp(high, low)),
		"strcmp unsigned 0xFF vs 0x01");
}

static int	write_pair(int fd, const void *buf, size_t n, ssize_t *ft_n,
		int *ft_err, ssize_t *lc_n, int *lc_err)
{
	errno = 0;
	*ft_n = ft_write(fd, buf, n);
	*ft_err = errno;
	errno = 0;
	*lc_n = write(fd, buf, n);
	*lc_err = errno;
	return (0);
}

static void	test_write(void)
{
	int		p[2];
	char	buf[64];
	ssize_t	ft_n;
	ssize_t	lc_n;
	int		ft_err;
	int		lc_err;
	ssize_t	got;

	expect(pipe(p) == 0, "write pipe create");
	write_pair(p[1], "hello", 5, &ft_n, &ft_err, &lc_n, &lc_err);
	expect(ft_n == 5 && lc_n == 5, "write success count");
	memset(buf, 0, sizeof(buf));
	got = read(p[0], buf, sizeof(buf));
	expect(got == 10 && memcmp(buf, "hellohello", 10) == 0,
		"write success content");
	write_pair(p[1], "x", 0, &ft_n, &ft_err, &lc_n, &lc_err);
	expect(ft_n == 0 && lc_n == 0, "write zero-length");
	close(p[0]);
	close(p[1]);

	write_pair(-1, "x", 1, &ft_n, &ft_err, &lc_n, &lc_err);
	expect(ft_n == -1 && lc_n == -1, "write invalid fd return");
	expect(ft_err == lc_err && ft_err == EBADF, "write invalid fd errno");
}

static void	test_read(void)
{
	int		p[2];
	int		fd;
	char	ft_buf[64];
	char	lc_buf[64];
	ssize_t	ft_n;
	ssize_t	lc_n;
	int		ft_err;
	int		lc_err;

	expect(pipe(p) == 0, "read pipe create");
	expect(write(p[1], "world", 5) == 5, "read pipe preload");
	memset(ft_buf, 0, sizeof(ft_buf));
	errno = 0;
	ft_n = ft_read(p[0], ft_buf, 5);
	ft_err = errno;
	expect(ft_n == 5 && memcmp(ft_buf, "world", 5) == 0, "read success");
	expect(ft_err == 0, "read success errno");

	errno = 0;
	ft_n = ft_read(p[0], ft_buf, 0);
	expect(ft_n == 0, "read zero-length");
	close(p[0]);
	close(p[1]);

	fd = open("/dev/null", O_RDONLY);
	expect(fd >= 0, "read /dev/null open");
	errno = 0;
	ft_n = ft_read(fd, ft_buf, 8);
	expect(ft_n == 0, "read EOF /dev/null");
	close(fd);

	memset(ft_buf, 0xAA, sizeof(ft_buf));
	memset(lc_buf, 0xAA, sizeof(lc_buf));
	errno = 0;
	ft_n = ft_read(-1, ft_buf, 4);
	ft_err = errno;
	errno = 0;
	lc_n = read(-1, lc_buf, 4);
	lc_err = errno;
	expect(ft_n == -1 && lc_n == -1, "read invalid fd return");
	expect(ft_err == lc_err && ft_err == EBADF, "read invalid fd errno");
}

static void	test_strdup(void)
{
	const char	*empty = "";
	const char	*normal = "strdup-check";
	char		long_str[1025];
	char		*ft_s;
	char		*lc_s;

	memset(long_str, 'Q', 1024);
	long_str[1024] = '\0';

	ft_s = ft_strdup(empty);
	lc_s = strdup(empty);
	expect(ft_s != NULL && lc_s != NULL, "strdup empty alloc");
	expect(ft_s && ft_s != empty && strcmp(ft_s, empty) == 0,
		"strdup empty copy");
	expect(ft_s && ft_s[0] == '\0', "strdup empty NUL");
	free(ft_s);
	free(lc_s);

	ft_s = ft_strdup(normal);
	lc_s = strdup(normal);
	expect(ft_s != NULL && lc_s != NULL, "strdup normal alloc");
	expect(ft_s && lc_s && ft_s != normal && strcmp(ft_s, lc_s) == 0,
		"strdup normal copy");
	expect(ft_s && ft_s[strlen(normal)] == '\0', "strdup normal NUL");
	free(ft_s);
	free(lc_s);

	ft_s = ft_strdup(long_str);
	lc_s = strdup(long_str);
	expect(ft_s != NULL && lc_s != NULL, "strdup long alloc");
	expect(ft_s && lc_s && ft_s != long_str && strcmp(ft_s, lc_s) == 0,
		"strdup long copy");
	free(ft_s);
	free(lc_s);
}

static int	all_zero(const unsigned char *p, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (p[i] != 0)
			return (0);
		i++;
	}
	return (1);
}

static void	test_calloc_zero_args(size_t nmemb, size_t size, const char *name)
{
	void	*ft_p;
	void	*lc_p;
	int		ft_err;
	int		lc_err;
	char	err_name[128];

	errno = 123;
	ft_p = ft_calloc(nmemb, size);
	ft_err = errno;
	errno = 123;
	lc_p = calloc(nmemb, size);
	lc_err = errno;
	expect((ft_p == NULL) == (lc_p == NULL), name);
	snprintf(err_name, sizeof(err_name), "%s errno", name);
	expect(ft_err == lc_err, err_name);
	free(ft_p);
	free(lc_p);
}

static void	test_calloc_overflow(size_t nmemb, size_t size, const char *name)
{
	void	*ft_p;
	void	*lc_p;
	int		ft_err;
	char	err_name[128];

	errno = 0;
	ft_p = ft_calloc(nmemb, size);
	ft_err = errno;
	lc_p = calloc(nmemb, size);
	expect(ft_p == NULL && lc_p == NULL, name);
	snprintf(err_name, sizeof(err_name), "%s errno", name);
	expect(ft_p == NULL && ft_err == ENOMEM, err_name);
}

static void	test_calloc(void)
{
	void			*ft_p;
	void			*lc_p;
	unsigned char	*b;
	int				*ints;
	size_t			n;
	int				i;

	ft_p = ft_calloc(1, 1);
	expect(ft_p != NULL, "calloc(1,1) alloc");
	b = ft_p;
	expect(ft_p && b[0] == 0, "calloc(1,1) zero");
	if (ft_p)
	{
		b[0] = 0xAB;
		expect(b[0] == 0xAB, "calloc(1,1) writable");
	}
	free(ft_p);

	n = 10 * sizeof(int);
	ft_p = ft_calloc(10, sizeof(int));
	lc_p = calloc(10, sizeof(int));
	expect(ft_p != NULL && lc_p != NULL, "calloc(10,int) alloc");
	expect(ft_p && all_zero(ft_p, n), "calloc(10,int) zeros");
	expect(ft_p && lc_p && memcmp(ft_p, lc_p, n) == 0,
		"calloc(10,int) matches libc");
	ints = ft_p;
	if (ints)
	{
		i = 0;
		while (i < 10)
		{
			ints[i] = i + 1;
			i++;
		}
		expect(ints[0] == 1 && ints[9] == 10, "calloc(10,int) writable");
	}
	free(ft_p);
	free(lc_p);

	test_calloc_zero_args(0, 0, "calloc(0,0) nullness");
	test_calloc_zero_args(0, 1, "calloc(0,1) nullness");
	test_calloc_zero_args(1, 0, "calloc(1,0) nullness");

	ft_p = ft_calloc(0, SIZE_MAX);
	expect(1, "calloc(0,SIZE_MAX) no crash");
	free(ft_p);

	test_calloc_overflow(SIZE_MAX, 2, "calloc overflow SIZE_MAX*2");
	test_calloc_overflow(2, SIZE_MAX, "calloc overflow 2*SIZE_MAX");
	test_calloc_overflow((SIZE_MAX / 2) + 1, 2,
		"calloc overflow (SIZE_MAX/2+1)*2");
	test_calloc_overflow((SIZE_MAX / 2) + 1, 3,
		"calloc overflow (SIZE_MAX/2+1)*3");
	test_calloc_overflow((SIZE_MAX / 3) + 1, (SIZE_MAX / 3) + 1,
		"calloc overflow large*large");

	n = 256 * 256;
	ft_p = ft_calloc(256, 256);
	expect(ft_p != NULL, "calloc below-overflow 256*256 alloc");
	expect(ft_p && all_zero(ft_p, n), "calloc below-overflow 256*256 zeros");
	free(ft_p);

	ft_p = ft_calloc(4096, 1);
	expect(ft_p != NULL, "calloc(4096,1) alloc");
	expect(ft_p && all_zero(ft_p, 4096), "calloc(4096,1) zeros");
	free(ft_p);
}

int	main(void)
{
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
	test_read();
	test_strdup();
	test_calloc();
	printf("\n%d passed, %d failed\n", g_pass, g_fail);
	return (g_fail != 0);
}
