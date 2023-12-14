/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:06:44 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/14 14:34:57 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_path_cmd(char *path, char *cmd)
{
	int		path_len;
	int		cmd_len;
	char	*res;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	res = malloc(path_len + cmd_len + 2);
	if (res == NULL)
	{
		printf("Malloc failed\n");
		exit(EXIT_FAILURE);
	}
	ft_strcpy(res, path);
	ft_strcat(res, "/");
	ft_strcat(res, cmd);
	return (res);
}

char	*find_executable_path(char *command, t_environment *env_copy)
{
	char	*path;
	char	*token_start;
	char	*token_end;
	char	*cmd_path;
	char	*segment;
	int		i;
	int		segment_len;

	i = 0;
	cmd_path = NULL;
	while (env_copy[i].key != NULL)
	{
		if (strcmp(env_copy[i].key, "PATH") == 0)
		{
			path = ft_strdup(env_copy[i].value);
			token_start = path;
			token_end = ft_strchr(path, ':');
			while (token_start != NULL)
			{
				if (token_end != NULL)
				{
					segment_len = token_end - token_start;
					segment = malloc(segment_len + 1);
					if (segment == NULL)
					{
						printf("Malloc failed\n");
						exit(EXIT_FAILURE);
					}
					ft_strncpy(segment, token_start, segment_len);
					segment[segment_len] = '\0';
					cmd_path = concat_path_cmd(segment, command);
					free(segment);
					if (access(cmd_path, F_OK) == 0)
					{
						free(path);
						return (cmd_path);
					}
					free(cmd_path);
					token_start = token_end + 1;
					token_end = ft_strchr(token_start, ':');
				}
				else
				{
					cmd_path = concat_path_cmd(token_start, command);
					if (cmd_path != NULL && access(cmd_path, F_OK) == 0)
					{
						free(path);
						return (cmd_path);
					}
					free(cmd_path);
					token_start = NULL;
				}
			}
			free(path);
			break ;
		}
		i++;
	}
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

char	**build_arg(t_commande *cmd, t_environment *env_copy)
{
	int		argc;
	char	**argv;
	t_args	*arg;
	int		i;
	/* t_args	*head; */

	/* head = cmd->args; */
	argc = count_args(cmd->args);
	argv = malloc(sizeof(char *) * (argc + 2));
	if (!argv)
		return (NULL);
	argv[0] = find_executable_path(cmd->cmd, env_copy);
	printf("argv0 is %s\n", argv[0]);
	if (!argv[0])
		return (NULL);
	i = 1;
	arg = cmd->args;
	while (arg)
	{
		if (arg->type == 9)
		{
			break ;
		}
		else
		{
			printf("Arg: %s\n", arg->arg);
			argv[i] = ft_strdup(arg->arg);
			if (!argv[i])
			{
				perror("alloc error\n");
				free_argv(argv);
				return (NULL);
			}
			i++;
		}
		arg = arg->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	execute_basic_cmd(t_commande *cmd, t_environment *env_copy)
{
	char		*full_path;
	char		**argv;

	full_path = find_executable_path(cmd->cmd, env_copy);
	/* printf("FULL PATH IS %s\n", full_path); */
	if (!full_path)
		ft_error(cmd->cmd);
	argv = build_arg(cmd, env_copy);
	if (!argv)
	{
		printf("Malloc error\n");
		return (1);
	}
	/* int i = 0; */
	/* while (argv[i] != NULL) */
	/* { */
	/* 	printf("ARGV IS %s\n", argv[i]); */
	/* 	i++; */
	/* } */
	if (execve(full_path, argv, NULL) == -1)
		ft_error(cmd->cmd);
	free_argv(argv);
	free(full_path);
	return (0);
}
