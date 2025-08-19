/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:43:35 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 00:28:57 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_pipex p;

	if (argc != 5)
		return (write(2, "Use: ./pipex infile cmd1 cmd2 outfile\n", 39), 1);
	if (pipe(p.pipefd) == -1)
		error_exit("pipe", 1);
	p.pid1 = fork();
	if (p.pid1 == -1)
		error_exit("fork", 1);
	if (p.pid1 == 0)
		infile_process(argv[1], argv[2], p.pipefd, envp);
	p.pid2 = fork();
	if (p.pid2 == -1)
		error_exit("fork 2", 1);
	if (p.pid2 == 0)
		outfile_process(argv[4], argv[3], p.pipefd, envp);
	close(p.pipefd[0]);
	close(p.pipefd[1]);
	return (handle_children(p.pid2));
}

/* int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	//char *str = find_cmd_path("wc", envp);
	int i = 0;
	while (envp[i])
	{	
		printf("%s\n", envp[i]);
		i++;
	}
	//ft_printf("%s\n", str);
	//free(str);
} */