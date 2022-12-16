#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	while (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[count] != '\0')
	{
		write (1, &str[count], 1);
		count++;
	}
	return (count);
}

int ft_numsize(long long n, char *base)
{
    int (count) = 0;
	int (intbase) = 0;
	while (base[intbase])
		intbase++;
	if (n <= 0)
		++count;
	while (n && ++count)
		n /= intbase;
	return (count);
}

static void	ft_calculate(char *str, char *base, size_t len, size_t num)
{
	unsigned int (intbase) = 0;
	while (base[intbase])
		intbase++;
	while (num > 0)
	{
		str[len - 1] = base[num % intbase];
		num /= intbase;
		len--;
	}
}

int	ft_itoa_base(long long n, char *base)
{
	unsigned int (len) = ft_numsize(n, base);
	long long (num) = n;
	unsigned int (res) = 0;
	char *(str) = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (0);
	if (n < 0)
	{
		str[0] = '-';
		num = -num;
	}
	if (num == 0)
		str[0] = '0';
	ft_calculate(str, base, len, num);
	str[len] = '\0';
	ft_putstr(str);
	while (str[res])
		res++;
	free(str);
	return (res);
}
