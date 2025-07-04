/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:15:23 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/13 01:43:08 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_base(unsigned long n, const char *base, unsigned int blen)
{
	int		count;

	count = 0;
	if (n >= blen)
		count += ft_putnbr_base(n / blen, base, blen);
	count += ft_putchar_len(base[n % blen]);
	return (count);
}

int	ft_putunsigned_len(unsigned int n)
{
	return (ft_putnbr_base(n, "0123456789", 10));
}

int	ft_puthex_len(unsigned int n, int upper)
{
	if (upper)
		return (ft_putnbr_base(n, "0123456789ABCDEF", 16));
	else
		return (ft_putnbr_base(n, "0123456789abcdef", 16));
}

int	ft_putpointer_len(void *ptr)
{
	unsigned long	address;
	int				count;

	count = 0;
	address = (unsigned long)ptr;
	if (!address)
		count += ft_putstr_len("(nil)");
	else
	{
		count += ft_putstr_len("0x");
		count += ft_putnbr_base(address, "0123456789abcdef", 16);
	}
	return (count);
}
