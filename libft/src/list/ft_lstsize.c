/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:27:08 by mjusta            #+#    #+#             */
/*   Updated: 2025/05/28 19:02:08 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
/*
#include <stdio.h>
int	main(void)
{
	t_list	*a = ft_lstnew("first");
	t_list	*b = ft_lstnew("second");
	t_list	*c = ft_lstnew("third");

	ft_lstadd_front(&a, b);
	ft_lstadd_front(&b, c);

	printf("%i items in the list", ft_lstsize(c));

	t_list *tmp;
	while (c)
	{
		tmp = c->next;
		free(c);
		c = tmp;
	}
}*/