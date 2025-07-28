/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:43:35 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/29 01:47:29 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (write(2, "Use: ./pipex infile cmd1 cmd2 outfile\n", 39), 1);
	if (pipe(pipefd) == -1)
		error_exit("pipe");
	pid1 = fork();
	if (pid1 == -1)
		error_exit("fork 1");
	if (pid1 == 0)
		infile_process(argv[1], argv[2], pipefd, envp);
	pid2 = fork();
	if (pid2 == -1)
		error_exit("fork 2");
	if (pid2 == 0)
		outfile_process(argv[4], argv[3], pipefd, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

/* int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *str = find_cmd_path("wc", envp);
	ft_printf("%s\n", str);
	free(str);
} */