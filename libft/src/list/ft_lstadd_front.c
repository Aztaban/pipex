/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:09:24 by mjusta            #+#    #+#             */
/*   Updated: 2025/05/28 17:57:42 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>
int	main(void)
{
	t_list *node1 = ft_lstnew("first");
	t_list *node2 = ft_lstnew("second");
	
	ft_lstadd_front(&node1, node2);
	printf("%s -> %s\n", (char *)node1->content, (char *)node1->next->content);

	free(node1->next);
	free(node1);
}*/