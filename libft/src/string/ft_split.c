/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:42:22 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/13 02:29:44 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static void	free_split(char **result, size_t count)
{
	while (count > 0)
		free(result[--count]);
	free(result);
}

static int	fill_words(char **res, const char *s, char c)
{
	char	*word_start;
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			word_start = (char *)s;
			while (*s && *s != c)
				s++;
			res[i] = ft_substr(word_start, 0, s - word_start);
			if (!res[i])
			{
				free_split(res, i);
				return (0);
			}
			i++;
		}
	}
	res[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	if (!fill_words(result, s, c))
		return (NULL);
	return (result);
}
/*
#include <stdio.h>
int	main(void)
{
	int i = 0;
	char **arr = ft_split("a b  c", ' ');

	if (!arr)
	{
		printf("Split fail.");
		return (1);
	}
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		free(arr[i]);
		i++;	
	}
	free(arr);
	return (0);
}*/
