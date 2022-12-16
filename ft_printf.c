/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hece <hece@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:47:31 by hece              #+#    #+#             */
/*   Updated: 2022/12/16 17:07:15 by hece             ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str, int checker)
{
	int (count) = 0;
	if (!str || str == 0)
		return (0);
	if (checker == 1)
	{
		while (str[count] != '\0')
		{
			write(1, &str[count], 1);
			count++;
		}
	}
	else
	{
		write(1, &str[0], 1);
		return (1);
	}
	free (str);
	return (count);
}

unsigned int	ft_numsize(long long n, char *base)
{
	long long	temp;
	long long	base_len;
	long long	len;

	base_len = 0;
	while (base[base_len])
		base_len++;
	temp = n;
	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
	{
		len += 1;
		temp = -temp;
	}
	while (temp)
	{
		temp /= base_len;
		len++;
	}
	return (len);
}

int	ft_itoa_base(long long n, char *base)
{
	unsigned int (len) = ft_numsize(n, base);
	unsigned int (intbase) = 0;
	long long (num) = n;
	char *(str) = (char *)malloc(sizeof(char) * (len + 1));
	while (base[intbase])
		intbase++;
	if (str == NULL)
		return (0);
	if (n < 0)
	{
		str[0] = '-';
		num = -num;
	}
	if (num == 0)
		str[0] = '0';
	str[len] = '\0';
	while (num > 0)
	{
		str[len - 1] = base[num % intbase];
		num /= intbase;
		len--;
	}
	return (ft_putstr(str, 1));
}

int	ft_type_control(char c, va_list arg)
{
	char *(a);
	if (c == 's')
		return (ft_putstr(va_arg(arg, char *), 1));
	else if (c == 'c')
	{
		a = va_arg(arg, char *);
		return (ft_putstr(a, 0));
	}
	else if (c == 'd' || c == 'i')
		return (ft_itoa_base(va_arg(arg, int), "0123456789"));
	else if (c == 'p')
	{
		ft_putstr("0x", 1);
		return (ft_itoa_base(
				va_arg(arg, unsigned long), "0123456789abcdef") + 2);
	}
	else if (c == 'u')
		return (ft_itoa_base(va_arg(arg, unsigned int), "0123456789"));
	else if (c == '%')
		return (ft_putstr("%", 1));
	else if (c == 'x')
		return (ft_itoa_base(va_arg(arg, unsigned int), "0123456789abcdef"));
	else if (c == 'X')
		return (ft_itoa_base(va_arg(arg, unsigned int), "0123456789ABCDEF"));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		index;
	int		jndex;

	va_start(arg, str);
	index = 0;
	jndex = 0;
	while (str[index] != '\0')
	{
		if (str[index + 1] == '\0' && str[index] == '%')
			write(1, &str[index + 1], 1);
		else if (str[index] == '%')
		{
			jndex += ft_type_control(str[index + 1], arg);
			index++;
		}
		else
			jndex += write(1, &str[index], 1);
		index++;
	}
	va_end(arg);
	return (jndex);
}

/*
#include <stdio.h>
int	main(int argc, char *argv[])
{
	(void)argc;
	ft_printf("%c%c\n", argv[1], argv[2]);
}
*/
