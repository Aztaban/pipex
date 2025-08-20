/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:12:26 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 18:12:16 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Wait for all children and return the exit status of second child
 * 
 * Reaps every child process with wait(2) and tracks the status of the child
 * identified by @p pid2. If that child exits normally, returns its exit status.
 * 
 * If the child terminates with signal, return 128 + signal_number
 * 
 * @param pid2 PID of the "second" child whose status should determine exit code.
 * @return Exit code for the parent process.
 */
int	handle_children(pid_t pid2)
{
	int		status;
	int		exit_code;
	pid_t	pid;

	exit_code = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == pid2)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
	return (exit_code);
}

/**
 * @brief Replace current process image with a command, or exit on failure.
 * 
 * Calls execve(2) with resolved @p cmd_path and arguments. On succes this 
 * function never returns. If execve fails, all allocated resources are freed
 * and exits process with an error.
 * 
 * @param cmd_path path to the executabe (malloc'ed).
 * @param cmd_args NULL-terminated arguments array (malloc'ed).
 * @param envp Enviroment variables array.
 */
void	handle_exec(char *cmd_path, char **cmd_args, char **envp)
{
	execve(cmd_path, cmd_args, envp);
	free(cmd_path);
	free_char_arr(cmd_args);
	error_exit("execve failed", 1);
}

/**
 * @brief Report "command not found" and exit with 127
 * 
 * Prints a shell-like error message to standard error output and exits the child
 * with code 127 (command not found);
 * 
 * @param cmd_args array containing command (cmd_args[0]) and its arguments.
 */
void	handle_invalid_cmd(char **cmd_args)
{
	ft_putstr_fd("pipex: Command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd_args[0], STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	free_char_arr(cmd_args);
	_exit(127);
}

/**
 * @brief Prints a perror message and exits with the given code.
 * 
 * Convenience function that uses perror(3) to include errno details and system 
 * error message.
 * 
 * @param msg string with error message passed to perror.
 * @param exit_code Process exit code returned to the OS.
 */
void	error_exit(const char *msg, int exit_code)
{
	perror(msg);
	exit(exit_code);
}
