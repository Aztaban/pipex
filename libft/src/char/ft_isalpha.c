/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:43:30 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/13 02:05:45 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_char.h"

static int	ft_islower(int c)
{
	return (c >= 97 && c <= 122);
}

static int	ft_isupper(int c)
{
	return (c >= 65 && c <= 90);
}

int	ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}
