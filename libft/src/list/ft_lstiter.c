/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:37:35 by mjusta            #+#    #+#             */
/*   Updated: 2025/05/29 12:59:46 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst && f)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*
void capitalize_string(void *content)
{
    char *str = (char *)content;
    while (*str)
	{
        *str = ft_toupper(*str);
		str++;
	}
}

#include <stdio.h>
int	main(void)
{
	t_list *node1 = ft_lstnew(ft_strdup("Hello"));
	t_list *node2 = ft_lstnew(ft_strdup("World"));
	t_list *node3 = ft_lstnew(ft_strdup("42Prague"));

	node1->next = node2;
	node2->next = node3;

	ft_lstiter(node1, capitalize_string);
	
	t_list	*lst = node1;
	while (lst)
    {
        printf("%s\n", (char *)lst->content);
        lst = lst->next;
    }
}*/