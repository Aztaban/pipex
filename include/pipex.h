/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:58:51 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/18 16:40:03 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>

void	infile_process(char *infile, char *cmd, int *pipefd, char **envp);
void	outfile_process(char *outfile, char *cmd, int *pipefd, char **envp);

void	error_exit(const char *msg, int error_code);
char	*find_cmd_path(char *cmd, char **envp);

#endif