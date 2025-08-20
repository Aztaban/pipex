/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:43:35 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 14:24:40 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

static int	piper(int argc, char **argv, char **envp)
{
	int		prev_fd;
	int		output_fd;
	int		i;
	pid_t	last_pid;

	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		prev_fd = here_doc_input(argv[2]);
		output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		i = 3;
	}
	else
	{
		prev_fd = open(argv[1], O_RDONLY);
		output_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		i = 2;
	}
	if (prev_fd < 0 || output_fd < 0)
		error_exit("file error", 1);
	while (i < argc - 2)
		prev_fd = pipe_child(argv[i++], prev_fd, envp);
	last_child(argv[argc - 2], prev_fd, output_fd, envp);
	last_pid = wait(NULL);
	return (handle_children(last_pid));
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		write(2, "Usage: ./pipex [here_doc LIMITER] cmd1 ... cmdn outfile\n",
			57);
		return (1);
	}
	return (piper(argc, argv, envp));
}

/* int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *str = find_cmd_path("wc", envp);
	ft_printf("%s\n", str);
	free(str);
} */