/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:58:51 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 00:49:53 by mjusta           ###   ########.fr       */
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

typedef struct s_pipex
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	int		exit_code;
}	t_pipex;

void	infile_process(char *infile, char *cmd, int *pipefd, char **envp);
void	outfile_process(char *outfile, char *cmd, int *pipefd, char **envp);

int		handle_children(pid_t pid2);
void	handle_exec(char *cmd_path, char **cmd_args, char **envp);
void	handle_invalid_cmd(char **cmd_args);
void	error_exit(const char *msg, int error_code);
char	*find_cmd_path(char *cmd, char **envp);

#endif