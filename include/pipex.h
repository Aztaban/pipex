/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:58:51 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 00:30:14 by mjusta           ###   ########.fr       */
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

void	error_exit(const char *msg, int error_code);
int		handle_children(pid_t pid2);
char	*find_cmd_path(char *cmd, char **envp);

#endif