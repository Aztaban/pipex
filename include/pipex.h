/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:58:51 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/25 14:59:52 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

void	child_process1(char *infile, char *cmd, int pipefd[2], char **envp);
void	child_process2(char *outfile, char *cmd, int pipefd[2], char **envp);

void	error_exit(const char *msg);
char	*get_env_path(char **envp);
char	*join_path_cmd(char *path, char *cmd);

#endif