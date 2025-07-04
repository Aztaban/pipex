/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:29:01 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/22 14:20:08 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft_memory.h"
#include "libft_string.h"

void	*free_stash(char **stash)
{
	if (stash && *stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (NULL);
}

void	ft_strjoin_free_stash(char **stash, char const *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s2)
		return ;
	if (!*stash)
		*stash = ft_strdup("");
	if (!*stash)
		return ;
	len1 = ft_strlen(*stash);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return ((void)free_stash(stash));
	ft_memcpy(result, *stash, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	free_stash(stash);
	*stash = result;
}

char	*extract_and_trim(char **stash)
{
	size_t	len;
	char	*line;
	char	*new_stash;

	if (!*stash || **stash == '\0')
		return (NULL);
	len = 0;
	while ((*stash)[len] && (*stash)[len] != '\n')
		len++;
	if ((*stash)[len] == '\n')
		len++;
	line = ft_substr(*stash, 0, len);
	if (!line)
		return (free_stash(stash));
	new_stash = ft_strdup(*stash + len);
	free_stash(stash);
	if (!new_stash || *new_stash == '\0')
	{
		free_stash(&new_stash);
		return (line);
	}
	*stash = new_stash;
	return (line);
}

void	fill_stash(int fd, char **stash, char *buffer)
{
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && (!*stash || !ft_strchr(*stash, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free_stash(stash);
			return ;
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		ft_strjoin_free_stash(stash, buffer);
		if (!*stash)
			return ;
	}
}
