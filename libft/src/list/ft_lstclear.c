/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:59:43 by mjusta            #+#    #+#             */
/*   Updated: 2025/05/29 12:24:49 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}

/*
#include <stdio.h>
void	del_content(void *content)
{
	printf("Deleting content: %s\n", (char *)content);
	free(content);
}

int	main(void)
{
	t_list *node1 = ft_lstnew(ft_strdup("Hello"));
	t_list *node2 = ft_lstnew(ft_strdup("World"));
	t_list *node3 = ft_lstnew(ft_strdup("42Prague"));

	node1->next = node2;
	node2->next = node3;
	
	ft_lstclear(&node1, del_content);
	printf("Content deleted.");

	if (!node1)
        printf("List cleared successfully!\n");
    else
        printf("List not fully cleared!\n");
}*/