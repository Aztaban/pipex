/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:43:35 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/04 22:07:01 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		infile_fd;
	int		outfile_fd;
	int		prev_fd;

	if (argc < 5)
		return (write(2, "Use: ./pipex infile cmd1 ... cmdn outfile\n", 39), 1);
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd < 0)
		error_exit("infile");
	prev_fd = infile_fd;
	i = 2;
	while (i < argc - 2)
	{
		prev_fd = pipe_child(argv[i], prev_fd, envp);
		i++;
	}
	outfile_fd = open(argv[argc -1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile_fd < 0)
		error_exit("outfile");
	last_child(argv[argc - 2], prev_fd, outfile_fd, envp);
	while (wait(NULL) > 0)
		;
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