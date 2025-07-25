/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:11:12 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/25 14:19:29 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process1(char *infile, char *cmd, int *pipefd, char **envp)
{
	int		fd_input;
	char	**cmd_args;
	char	*cmd_path;

	fd_input = open(infile, O_RDONLY);
	if (fd_input < 0)
		error_exit("open infile");
	dup2(fd_input, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(fd_input);
	cmd_args = ft_split(cmd, ' ');
	cmd_path = find_command_path(cmd_args[0], envp);
	if (!cmd_path)
		error_exit("command not found");
	execve(cmd_path, cmd_args, envp);
	error_exit("execve failed");
}