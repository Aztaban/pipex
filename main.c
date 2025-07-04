/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:43:35 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/05 01:08:20 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	if (argc == 5)
	{
		ft_printf("%s\n", argv[1]);
		ft_printf("%s\n", argv[2]);
		ft_printf("%s\n", argv[3]);
		ft_printf("%s\n", argv[4]);
	}
}