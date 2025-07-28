/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:11:12 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/29 01:43:05 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	infile_process(char *infile, char *cmd, int *pipefd, char **envp)
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
	cmd_path = find_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_char_arr(cmd_args);
		error_exit("command not found");
	}
	execve(cmd_path, cmd_args, envp);
	free(cmd_path);
	free_char_arr(cmd_args);
	error_exit("execve failed");
}

void	outfile_process(char *outfile, char *cmd, int *pipefd, char **envp)
{
	int		fd_output;
	char	**cmd_args;
	char	*cmd_path;

	fd_output = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_output < 0)
		error_exit("open outfile");
	dup2(fd_output, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	close(fd_output);
	cmd_args = ft_split(cmd, ' ');
	cmd_path = find_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_char_arr(cmd_args);
		error_exit("command not found");
	}
	execve(cmd_path, cmd_args, envp);
	free(cmd_path);
	free_char_arr(cmd_args);
	error_exit("execve failed");
}
