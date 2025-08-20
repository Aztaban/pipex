/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:11:12 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 22:35:04 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * @brief Resolve a command into an executable path.
 *
 * If cmd_args[0] contains a '/', treat it as a direct path:
 *   - If the file does not exist -> exit 127 (command not found).
 *   - If the file is not executable -> exit 126 (permission denied).
 *   - Otherwise, return a strdup() of cmd_args[0].
 *
 * If cmd_args[0] has no '/', search PATH using find_cmd_path().
 *
 * @param cmd_args Argument vector for the command.
 * @param envp     Environment variables.
 * @return Newly allocated string with the command path, or NULL if not found.
 */
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

/**
 * @brief Split a command string, resolve its path, and execve().
 *
 * Splits @p cmd into argv (by spaces), resolves the executable path,
 * and executes it with execve(). On error:
 *  - If no command is given, prints "pipex: Command not found" and exits 127.
 *  - If the command cannot be resolved, calls handle_invalid_cmd().
 *  - On execve() failure, handle_exec() will exit with error.
 *
 * @param cmd  Command string (e.g., "ls -l").
 * @param envp Environment variables.
 */
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

/**
 * @brief Launch an intermediate pipeline stage: input_fd -> cmd -> new pipe.
 *
 * Creates a new pipe. In the child:
 *  - STDIN  <- input_fd
 *  - STDOUT -> pipefd[1]
 * Closes unused fds in both child and parent. Returns the read end (pipefd[0])
 * to be used as the next stage's input_fd by the caller.
 *
 * @param cmd      Command string (e.g., "grep foo").
 * @param input_fd Read end from previous stage (or infile fd).
 * @param envp     Environment.
 * @return Read end of the new pipe (>=0) for the next stage.
 */
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

/**
 * @brief Launch the final pipeline stage: input_fd -> cmd -> outfile_fd.
 *
 * In the child:
 *  - STDIN  <- input_fd
 *  - STDOUT -> outfile_fd
 * Closes unused fds in both child and parent. Returns the child's PID so the
 * caller can track and return the final command's exit status.
 *
 * @param cmd         Command string.
 * @param input_fd    Read end from previous stage (or infile fd).
 * @param outfile_fd  Output file descriptor (opened by caller).
 * @param envp        Environment.
 * @return PID of the last child.
 */
pid_t	last_child(char *cmd, int input_fd, int outfile_fd, char **envp)
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
	return (pid);
}

/**
 * @brief Read lines from stdin until LIMITER, providing here_doc input.
 *
 * Prompts the user with "heredoc> " and collects lines via get_next_line().
 * When a line equals LIMITER plus newline, stop and close the write end.
 * Returns the read end of an internal pipe that now contains the collected data.
 *
 * @param limiter Delimiter line (without newline).
 * @return Read end FD of the pipe containing the here_doc data.
 */
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
