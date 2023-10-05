/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:06:44 by lmedrano          #+#    #+#             */
/*   Updated: 2023/10/05 11:55:13 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_executable_path(const char *command)
{
	char	*path;
	char	*path_cpy;
	char	*dir;
	char	*end;
	char	*full_path;
	size_t	dir_len;

	path = getenv("PATH");
	if (path == NULL)
	{
		printf("Could not find PATH\n");
		return (NULL);
	}
	path_cpy = ft_strdup(path);
	if (path_cpy == NULL)
	{
		printf("Error: strdup did not work\n");
		return (NULL);
	}
	dir = path_cpy;
	while (*dir != '\0')
	{
		end = ft_strchr(dir, ':');
		if (end == NULL)
			end = dir + ft_strlen(dir);
		dir_len = end - dir;
		full_path = malloc(dir_len + 1 + ft_strlen(command) + 1);
		if (full_path == NULL)
		{
			printf("Malloc error\n");
			free(path_cpy);
			return (NULL);
		}
		ft_strncpy(full_path, dir, dir_len);
		full_path[dir_len] = '/';
		ft_strcpy(full_path + dir_len + 1, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_cpy);
			printf("full path is : %s\n", full_path);
			return (full_path);
		}
		free(full_path);
		if (*end == ':')
			dir = end + 1;
		else
			break ;
	}
	free(path_cpy);
	return (NULL);
}

int	count_args(t_args *args)
{
	int	count;

	count = 0;
	while (args != NULL)
	{
		count++;
		args = args->next;
	}
	return (count);
}

int	execute_basic_cmd(t_commande *cmd)
{
	char		*full_path;
	char		**argv;
	int			i;
	t_args		*arg;
	t_commande	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		full_path = find_executable_path(tmp->cmd);
		printf("after find path, full path is %s\n", full_path);
		if (full_path == NULL)
		{
			printf("coucou\n");
			printf("Error: %s is not an executable cmd\n", tmp->cmd);
			return (1);
		}
		argv = malloc(sizeof(char *) * (count_args(tmp->args) + 2));
		if (argv == NULL)
		{
			printf("Malloc error\n");
			free(full_path);
			return (1);
		}
		argv[0] = full_path;
		i = 1;
		arg = tmp->args;
		while (arg != NULL)
		{
			argv[i] = arg->arg;
			arg = arg->next;
			i++;
		}
		argv[i] = NULL;
		printf("full path before execve is : %s\n", full_path);
		if (execve(full_path, argv, NULL) == -1)
		{
			printf("Error: Could not execute cmd\n");
			free(full_path);
			free(argv);
			return (1);
		}
		free(argv);
		free(full_path);
		tmp = tmp->next;
	}
	return (0);
}
