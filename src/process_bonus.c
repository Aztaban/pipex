/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:11:12 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/04 22:29:02 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_cmd(char *cmd_str, char **envp)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(cmd_str, ' ');
	if (!cmd || !cmd[0])
		error_exit("invalid command");
	cmd_path = find_cmd_path(cmd[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd[0], 2);
		exit(EXIT_FAILURE);
	}
	execve(cmd_path, cmd, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	pipe_child(char *cmd, int input_fd, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		error_exit("pipe");
	pid = fork();
	if (pid == -1)
		error_exit("fork");
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_cmd(cmd, envp);
	}
	close(pipefd[1]);
	close(input_fd);
	return (pipefd[0]);
}

void	last_child(char *cmd, int input_fd, int outfile_fd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit("fork");
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		dup2(outfile_fd, STDOUT_FILENO);
		close(input_fd);
		close(outfile_fd);
		execute_cmd(cmd, envp);
	}
	close(input_fd);
	close(outfile_fd); 
}


