/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:43:35 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 22:22:43 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * @brief Build an N-stage pipeline (supports here_doc) and run it.
 *
 * Behavior:
 * - If argv[1] == "here_doc", read from a heredoc delimited by argv[2] and
 *   append to the output file (O_APPEND). The first command is argv[3].
 * - Otherwise, read from infile argv[1] and truncate/create the output file.
 *   The first command is argv[2].
 *
 * The function chains intermediate commands with pipe_child(), then executes
 * the final stage with last_child(). It waits for all children and returns
 * the exit status of the *last* command.
 *
 * @param argc Argument count.
 * @param argv Arguments: either
 *             [infile, cmd1, ..., cmdN, outfile] or
 *             ["here_doc", LIMITER, cmd1, ..., cmdN, outfile]
 * @param envp Environment.
 * @return Exit code of the last command (0–255, or 128+signal).
 */
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
	last_pid = last_child(argv[argc - 2], prev_fd, output_fd, envp);
	return (handle_children(last_pid));
}

/**
 * @brief Entry point for the bonus pipex (multiple commands + here_doc).
 *
 * Usage:
 *   ./pipex infile cmd1 ... cmdN outfile
 *   ./pipex here_doc LIMITER cmd1 ... cmdN outfile
 *
 * Returns 1 and prints usage on stderr if too few arguments are provided.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param envp Environment.
 * @return Process exit code.
 */
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