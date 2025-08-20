/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:55:47 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/20 18:27:06 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brieg Extracts the PATH enviroment variable.
 * 
 * Iterates over @p envp until it finds variable with "PATH="
 * 
 * @param envp Enviroment variables array.
 * @return Pointer to PATH string or NULL if missing.
 */
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

/**
 * @brief Joins a directory path with command name.
 * 
 * Allocates and returns a new string "path/cmd"
 * 
 * @param path Directory path
 * @param cmd Command name
 * @return "path/cmd" string (Malloc'ed) or NULL on allocation failure.
 */
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

/**
 * @brief Search for command in an array of paths.
 * 
 * For each directory in @p paths, build "dir/cmd" and checks whether
 * it is executable.
 * 
 * @param paths NULL terminated array of paths strings.
 * @param cmd Command name to search for.
 * @return Full path string (malloc'ed) if found or NULL.
 */
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

/**
 * @brief Resolves a command name into a full executable path.
 * 
 * - If @p cmd contains a '/' (absolute path), checks it directly with access(2).
 * 
 * - Otherwise, extracts PATH from enviroment and searches each path for an 
 *   executable matching @p cmd.
 * 
 * @param cmd Command name (absolute path or just a command)
 * @param envp Enviromental variables.
 * @return String with resolved path (Malloc'ed), or NULL if not found.
 */
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
