/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:11:12 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 01:08:51 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*resolve_cmd_path(char **cmd_args, char **envp)
{
	char	*cmd_path;

	if (ft_strchr(cmd_args[0], '/'))
	{
		if (access(cmd_args[0], F_OK) != 0)
		{
			perror("pipex");
			free_char_arr(cmd_args);
			_exit(127);
		}
		else if (access(cmd_args[0], X_OK) != 0)
		{
			perror("pipex");
			free_char_arr(cmd_args);
			_exit(126);
		}
		cmd_path = ft_strdup(cmd_args[0]);
	}
	else
		cmd_path = find_cmd_path(cmd_args[0], envp);
	return (cmd_path);
}

static void	exec_cmd(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args || !cmd_args[0])
	{
		free_char_arr(cmd_args);
		write(STDERR_FILENO, "pipex: Command not found\n", 25);
		_exit(127);
	}
	cmd_path = resolve_cmd_path(cmd_args, envp);
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
