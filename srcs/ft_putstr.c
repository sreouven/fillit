#include "libft.h"
#include "fillit.h"

void	ft_putchar(const char c)
{
		write(1, &c, 1);
}

void	ft_putstr(const char *str)
{
		while(*str)
				ft_putchar(*str++);
}
