/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:58:51 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/28 23:53:48 by mjusta           ###   ########.fr       */
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

void	infile_process(char *infile, char *cmd, int pipefd[2], char **envp);
void	outfile_process(char *outfile, char *cmd, int pipefd[2], char **envp);

void	error_exit(const char *msg);
char	*find_cmd_path(char *cmd, char **envp);
char	*join_path_cmd(char *path, char *cmd);

#endif