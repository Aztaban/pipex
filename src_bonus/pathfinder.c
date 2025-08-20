/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:55:47 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/18 16:19:40 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*get_full_path(char *path, char *cmd)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, cmd);
	free(temp);
	return (result);
}

static char	*search_in_path(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = get_full_path(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	*env_path;
	char	**paths;
	char	*res;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	env_path = get_env_path(envp);
	if (!env_path || !*env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	res = search_in_path(paths, cmd);
	free_char_arr(paths);
	return (res);
}
