/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:41:10 by mjusta            #+#    #+#             */
/*   Updated: 2025/05/29 12:28:37 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
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
	char *str = ft_strdup("Hello 42");
	t_list *node = ft_lstnew(str);
	
	printf("Before deletion: %s\n", (char *)node->content);
	ft_lstdelone(node, del_content);
	printf("Content deleted.");
}*/