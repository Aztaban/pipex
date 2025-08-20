/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:12:26 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 14:25:56 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	handle_children(pid_t last_pid)
{
	int		status;
	int		exit_code;
	pid_t	pid;

	exit_code = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
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

void	handle_exec(char *cmd_path, char **cmd_args, char **envp)
{
	execve(cmd_path, cmd_args, envp);
	free(cmd_path);
	free_char_arr(cmd_args);
	error_exit("execve failed", 1);
}

void	handle_invalid_cmd(char **cmd_args)
{
	write(STDERR_FILENO, "pipex: Command not found: ", 26);
	write(STDERR_FILENO, cmd_args[0], ft_strlen(cmd_args[0]));
	write(STDERR_FILENO, "\n", 1);
	free_char_arr(cmd_args);
	_exit(127);
}

void	error_exit(const char *msg, int exit_code)
{
	perror(msg);
	exit(exit_code);
}
