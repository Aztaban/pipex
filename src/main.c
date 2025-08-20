/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:43:35 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 17:22:59 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Entry point for the pipex program
 * 
 * This program simulates shell piping with two commands:
 *    ./pipex infile cmd1 cmd2 outfile
 * 
 * - Opens the input file and redirects it to the first command.
 * 
 * - Pipes the output of the first command into the second.
 * 
 * - Redirects the output of the second command into the output file.
 *
 * @param argc Argument count (should be 5)
 * @param argv Argument vector: [infile, cmd1, cmd2, outfile]
 * @param envp Environment variables
 *
 * @return 0 on success, 1 on error
 */
int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	if (argc != 5)
	{
		ft_putstr_fd("Use: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (1);
	}
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
