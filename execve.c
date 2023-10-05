/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:06:44 by lmedrano          #+#    #+#             */
/*   Updated: 2023/10/05 14:29:03 by lmedrano         ###   ########.fr       */
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

char	**build_arg(t_commande *cmd)
{
	int		argc;
	char	**argv;
	t_args	*arg;
	int		i;

	argc = count_args(cmd->args);
	argv = malloc(sizeof(char *) * (argc + 2));
	if (!argv)
		return (NULL);
	argv[0] = find_executable_path(cmd->cmd);
	if (!argv[0])
		return (NULL);
	i = 1;
	arg = cmd->args;
	while (arg)
	{
		argv[i++] = arg->arg;
		arg = arg->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	execute_basic_cmd(t_commande *cmd)
{
	char		*full_path;
	char		**argv;

	while (cmd)
	{
		full_path = find_executable_path(cmd->cmd);
		if (!full_path)
			ft_error(cmd->cmd);
		argv = build_arg(cmd);
		if (!argv)
		{
			printf("Malloc error\n");
			return (1);
		}
		if (execve(full_path, argv, NULL) == -1)
			ft_error(cmd->cmd);
		free_argv(argv);
		free(full_path);
		cmd = cmd->next;
	}
	return (0);
}
