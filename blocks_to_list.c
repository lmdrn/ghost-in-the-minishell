/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:13:54 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/06 14:17:31 by lmedrano         ###   ########.fr       */
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

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

//fct that search in path if command exists and can be executed with execve
//1. get path
//2. split path with :
//3. take each block and add command name to it
//4. go to location and see it exists + is executable
int	is_executable_command(char *node)
{
	char	*path_env;
	char	**dirs;
	char	*full_path;
	int		i;

	(void)node;
	path_env = getenv("PATH");
	if (path_env == NULL)
	{
		printf("Path not found\n");
		return (1);
	}
	dirs = ft_split(path_env, ':');
	if (dirs == NULL)
	{
		printf("Split did not work\n");
		return (1);
	}
	i = 0;
	while (dirs[i])
	{
		full_path = get_full_path(dirs[i], node);
		if (!full_path)
		{
			free_string_array(dirs);
			return (1);
		}
		if (check_access(full_path))
		{
			free_string_array(dirs);
			free(full_path);
			/* printf("%s exists and is executable\n", node); */
			return (0);
		}
		free(full_path);
		i++;
	}
	free_string_array(dirs);
	/* ft_putendl_fd("CMD does NOT exist OR is NOT executable", 1); */
	return (1);
}
