/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:41:15 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/13 18:42:10 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define MAX_FD 1024

char	*get_next_line(int fd);
char	*get_next_line_multi_fd(int fd);

// helpers
void	*free_stash(char **stash);
void	ft_strjoin_free_stash(char **stash, char const *s2);
char	*extract_and_trim(char **stash);
void	fill_stash(int fd, char **stash, char *buffer);

#endif