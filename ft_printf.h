#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_tpye_control(char c, va_list arg);
int		ft_printf(const char *str, ...);
int		ft_itoa_base(long long n, char *base);

#endif
