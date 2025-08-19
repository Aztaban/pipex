/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:12:26 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 00:33:49 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_children(pid_t pid2)
{
	int	status;
	int	exit_code = 0;
	pid_t	pid;

	while ((pid = wait(&status)) > 0)
	{
		if (pid == pid2)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
	}
	return (exit_code);
}

void	error_exit(const char *msg, int exit_code)
{
	perror(msg);
	exit(exit_code);
}