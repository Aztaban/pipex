/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:58:51 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 01:55:12 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>

int		pipe_child(char *cmd, int input_fd, char **envp);
void	last_child(char *cmd, int input_fd, int outfile_fd, char **envp);

int		handle_children(pid_t pid);
void	handle_exec(char *cmd_path, char **cmd_args, char **envp);
void	handle_invalid_cmd(char **cmd_args);
void	error_exit(const char *msg, int error_code);
char	*find_cmd_path(char *cmd, char **envp);
int		here_doc_input(char *limiter);

#endif