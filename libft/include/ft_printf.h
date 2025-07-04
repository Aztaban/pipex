/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:47:35 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/13 01:48:36 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *input, ...);

int	ft_putchar_len(const char c);
int	ft_putstr_len(const char *str);
int	ft_putunsigned_len(unsigned int n);
int	ft_puthex_len(unsigned int n, int upper);
int	ft_putpointer_len(void *ptr);

#endif