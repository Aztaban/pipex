/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:11:12 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 22:31:44 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
 * @param cmd_args Argument vector for the command (argv-style, NULL-terminated).
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
		ft_putstr_fd("pipex: Command not found\n", STDERR_FILENO);
		_exit(127);
	}
	cmd_path = resolve_cmd_path(cmd_args, envp);
	if (!cmd_path)
		handle_invalid_cmd(cmd_args);
	handle_exec(cmd_path, cmd_args, envp);
}

/**
 * @brief Run the first stage of the pipeline: infile -> cmd -> pipe write end.
 *
 * Opens @p infile for reading, redirects STDIN to it, redirects STDOUT to
 * pipefd[1], closes unused FDs, then executes the command.
 *
 * @param infile Path to the input file.
 * @param cmd    Command string to execute.
 * @param pipefd Pipe file descriptors [read, write].
 * @param envp   Environment variables.
 */
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

/**
 * @brief Run the last stage of the pipeline: pipe read end -> cmd -> outfile.
 *
 * Opens/creates @p outfile for writing (truncate), redirects STDOUT to it,
 * redirects STDIN to pipefd[0], closes unused FDs, then executes the command.
 *
 * @param outfile Path to the output file.
 * @param cmd     Command string to execute.
 * @param pipefd  Pipe file descriptors [read, write].
 * @param envp    Environment variables.
 */
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
