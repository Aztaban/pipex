/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:47:27 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/20 23:46:03 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_len(const char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_len(const char *str)
{
	int	count;

	if (!str)
		return (ft_putstr_len("(null)"));
	count = 0;
	while (*str)
		count += ft_putchar_len(*str++);
	return (count);
}

static int	ft_putnbr_len(int n)
{
	long	num;
	int		count;

	count = 0;
	num = n;
	if (num < 0)
	{
		count += ft_putchar_len('-');
		num = -num;
	}
	if (num >= 10)
		count += ft_putnbr_len(num / 10);
	count += ft_putchar_len(num % 10 + '0');
	return (count);
}

static int	handle_conversion(char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_putchar_len(va_arg(args, int)));
	else if (specifier == 's')
		return (ft_putstr_len(va_arg(args, char *)));
	else if (specifier == 'p')
		return (ft_putpointer_len(va_arg(args, void *)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr_len(va_arg(args, int)));
	else if (specifier == 'u')
		return (ft_putunsigned_len(va_arg(args, int)));
	else if (specifier == 'x')
		return (ft_puthex_len(va_arg(args, int), 0));
	else if (specifier == 'X')
		return (ft_puthex_len(va_arg(args, int), 1));
	else if (specifier == '%')
		return (ft_putchar_len('%'));
	else
		return (0);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		count;

	if (!input)
		return (1);
	va_start(args, input);
	count = 0;
	while (*input)
	{
		if (*input == '%' && *(input + 1))
			count += handle_conversion(*(++input), args);
		else if (*input == '%')
			break ;
		else
			count += ft_putchar_len(*input);
		input++;
	}
	va_end(args);
	return (count);
}

/* #include <stdio.h>
#include <stddef.h>
#include <limits.h> 
int main(void)
{
	int ft1 = ft_printf("Hello 42\n");
	int og1 = printf("Hello 42\n");
	printf("ft length is %i!\n", ft1);
	printf("og length is %i!\n\n", og1);
	
	int ft2 = ft_printf("Hello %c 42\n", 'A');
	int og2 = printf("Hello %c 42\n", 'A');
	printf("ft length is %i!\n", ft2);
	printf("og length is %i!\n\n", og2);
	
	int ft3 = ft_printf("Hello 42 %s\n", "Prague");
	int og3 = printf("Hello 42 %s\n", "Prague");
	printf("ft length is %i!\n", ft3);
	printf("og length is %i!\n\n", og3);
	
	int ft4 = ft_printf("Hello %d Prague, I like n %i\n", 42, (int)-2147483648);
	int og4 = printf("Hello %d Prague, I like n %i\n", 42, (int)-2147483648);
	printf("ft length is %i!\n", ft4);
	printf("og length is %i!\n\n", og4);
	
	int ft5 = ft_printf("Hello %u Prague, I like n %u\n", 42u, 2147483648u);
	int og5 = printf("Hello %u Prague, I like n %u\n", 42u, 2147483648u);
	printf("ft length is %i!\n", ft5);
	printf("og length is %i!\n\n", og5);
	
	int ft6 = ft_printf("Hello %x Prague, I like n %x\n", 42u, 3147483648u);
	int og6 = printf("Hello %x Prague, I like n %x\n", 42u, 3147483648u);
	printf("ft length is %i!\n", ft6);
	printf("og length is %i!\n\n", og6);
	
	int ft7 = ft_printf("Hello %X Prague, I like n %X\n", 42u, 3147483648u);
	int og7 = printf("Hello %X Prague, I like n %X\n", 42u, 3147483648u);
	printf("ft length is %i!\n", ft7);
	printf("og length is %i!\n\n", og7);
	 
	//char *str = "test";
	int ft8 = ft_printf("pointer %p\n", (void *)LONG_MAX);
	int og8 = printf("pointer %p\n", (void *)LONG_MAX);
	printf("ft length is %i!\n", ft8);
	printf("og length is %i!\n\n", og8); 
 
	char *str = NULL;
	int ft9 = ft_printf("NULL %s NULL\n", str);
	int og9 = printf("NULL %s NULL\n", str);
	printf("ft length is %i!\n", ft9);
	printf("og length is %i!\n\n", og9); 
} */
