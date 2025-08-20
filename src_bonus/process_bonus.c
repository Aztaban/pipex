/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:11:12 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 01:57:27 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	pipe_child(char *cmd, int input_fd, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		error_exit("pipe", 1);
	pid = fork();
	if (pid == -1)
		error_exit("fork", 1);
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exec_cmd(cmd, envp);
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
		error_exit("fork", 1);
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		dup2(outfile_fd, STDOUT_FILENO);
		close(input_fd);
		close(outfile_fd);
		exec_cmd(cmd, envp);
	}
	close(input_fd);
	close(outfile_fd);
}

int	here_doc_input(char *limiter)
{
	int		pipefd[2];
	char	*line;
	size_t	len;

	if (pipe(pipefd) == -1)
		error_exit("pipe", 1);
	len = ft_strlen(limiter);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, len) && line[len] == '\n')
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}