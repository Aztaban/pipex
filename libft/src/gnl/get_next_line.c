/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:41:24 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/22 14:21:08 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_stash(&stash));
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_stash(&stash));
	fill_stash(fd, &stash, buffer);
	free(buffer);
	if (!stash || *stash == '\0')
		return (free_stash(&stash));
	next_line = extract_and_trim(&stash);
	return (next_line);
}

char	*get_next_line_multi_fd(int fd)
{
	static char	*stash[MAX_FD];
	char		*buffer;
	char		*next_line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (free_stash(&stash[fd]));
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_stash(&stash[fd]));
	fill_stash(fd, &stash[fd], buffer);
	free(buffer);
	if (!stash[fd] || *stash[fd] == '\0')
		return (free_stash(&stash[fd]));
	next_line = extract_and_trim(&stash[fd]);
	return (next_line);
}

/* 
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	char *line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break;
    	printf("Line: %s", line);
    	free(line);	
	}
	
	close(fd);
	return (0);
} */

/* #include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int fd1 = open("test.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	int fd3 = open("test3.txt", O_RDONLY);
	
	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
		return (1);
	char *line1;
	char *line2;
	char *line3;
	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);
		if (line1)
			printf("Line 1: %s", line1);
		if (line2)
			printf("Line 2: %s", line2);
		if (line3)
			printf("Line 3: %s", line3);
		if (!line1 && !line2 && !line3)
			break;
		free(line1);	
		free(line2);	
		free(line3);	
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
} */
