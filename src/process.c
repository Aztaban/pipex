/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:11:12 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 00:41:26 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_exec(char *cmd_path, char **cmd_args, char **envp)
{
	execve(cmd_path, cmd_args, envp);
	free(cmd_path);
	free_char_arr(cmd_args);
	error_exit("execve failed", 1);
}

static void	handle_invalid_cmd(char **cmd_args)
{
	write(STDERR_FILENO, "pipex: Command not found: ", 26);
	write(STDERR_FILENO, cmd_args[0], ft_strlen(cmd_args[0]));
	write(STDERR_FILENO, "\n", 1);
	free_char_arr(cmd_args);
	_exit(127);
}

static void	exec_cmd(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args || !cmd_args[0])
	{
		free_char_arr(cmd_args);
		write(STDERR_FILENO, "pipex: invalid or empty command\n", 32);
		_exit(127);
	}
	if (ft_strchr(cmd_args[0], '/'))
	{
		if (access(cmd_args[0], X_OK) != 0)
		{
			perror("pipex");
			free_char_arr(cmd_args);
			_exit(126);
		}
		cmd_path = ft_strdup(cmd_args[0]);
	}
	else
		cmd_path = find_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
		handle_invalid_cmd(cmd_args);
	handle_exec(cmd_path, cmd_args, envp);
}

void	infile_process(char *infile, char *cmd, int *pipefd, char **envp)
{
	int		fd_input;

	fd_input = open(infile, O_RDONLY);
	if (fd_input < 0)
		error_exit("open infile", 1);
	dup2(fd_input, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(fd_input);
	close(pipefd[0]);
	close(pipefd[1]);
	exec_cmd(cmd, envp);
}

void	outfile_process(char *outfile, char *cmd, int *pipefd, char **envp)
{
	int		fd_output;

	fd_output = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_output < 0)
		error_exit("open outfile", 1);
	dup2(fd_output, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(fd_output);
	close(pipefd[0]);
	close(pipefd[1]);
	exec_cmd(cmd, envp);
}
