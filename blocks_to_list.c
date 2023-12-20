/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:13:54 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/20 19:10:24 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_full_path(char *dir, char *node)
{
	char	*full_path;
	char	*tmp;

	full_path = concat_str(dir, "/");
	if (!full_path)
		return (NULL);
	tmp = concat_str(full_path, node);
	free(full_path);
	return (tmp);
}

int	check_access(char *path)
{
	if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
		return (1);
	return (0);
}

char	**retrieve_path_variable(void)
{
	char	*path_env;
	char	**dirs;

	path_env = getenv("PATH");
	if (path_env == NULL)
	{
		printf("Path not found\n");
		return (NULL);
	}
	dirs = ft_split(path_env, ':');
	if (dirs == NULL)
	{
		printf("Split did not work\n");
		return (NULL);
	}
	return (dirs);
}

//fct that search in path if command exists and can be executed with execve
//1. get path
//2. split path with :
//3. take each block and add command name to it
//4. go to location and see it exists + is executable
int	is_executable_command(char *node)
{
	char	**dirs;
	char	*full_path;
	int		i;

	dirs = retrieve_path_variable();
	if (dirs == NULL)
		return (1);
	i = 0;
	while (dirs[i])
	{
		full_path = full_path_check(dirs, i, node);
		if (full_path == NULL)
			return (1);
		if (check_access(full_path))
		{
			free_string_array(dirs);
			free(full_path);
			return (0);
		}
		free(full_path);
		i++;
	}
	free_string_array(dirs);
	return (1);
}
