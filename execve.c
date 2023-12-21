/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:06:44 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/21 12:21:23 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_path_cmd(char *path, char *cmd)
{
	int		path_len;
	int		cmd_len;
	char	*res;

	path_len = strlen(path);
	cmd_len = strlen(cmd);
	res = malloc(path_len + cmd_len + 2);
	if (res == NULL)
	{
		printf("Malloc failed\n");
		exit(EXIT_FAILURE);
		return (NULL);
	}
	else
	{
		ft_strcpy(res, path);
		ft_strcat(res, "/");
		ft_strcat(res, cmd);
		return (res);
	}
}

char	*find_executable_path(char *cmd, t_environment *env_copy)
{
	t_epi	epi;

	copy_the_path(env_copy, &epi);
	while (epi.tok_s != NULL)
	{
		epi.tok_e = ft_strchr(epi.tok_s, ':');
		if (epi.tok_e != NULL)
		{
			epi.seg = segment_malloc_copy(epi.seg, epi.tok_s, epi.tok_e);
			epi.cmd_path = concat_path_cmd(epi.seg, cmd);
			free(epi.seg);
			if (access(epi.cmd_path, F_OK) == 0)
			{
				free(epi.path);
				return (epi.cmd_path);
			}
			free(epi.cmd_path);
			epi.tok_s = epi.tok_e + 1;
		}
		else
			epi.cmd_path = concat_cmd(epi.cmd_path, epi.path, epi.tok_s, cmd);
	}
	free(epi.path);
	return (NULL);
}

void	create_args(char **argv, t_commande *cmd)
{
	int		i;
	t_args	*arg;

	i = 1;
	arg = cmd->args;
	while (arg)
	{
		if (arg->type == 8 || arg->type == 9
			|| arg->type == 10 || arg->type == 11)
			break ;
		else
		{
			/* printf("Arg: %s\n", arg->arg); */
			argv[i] = ft_strdup(arg->arg);
			if (!argv[i])
			{
				perror("malloc error\n");
				free_argv(argv);
				return ;
			}
			i++;
		}
		arg = arg->next;
	}
	argv[i] = NULL;
}

char	**build_arg(t_commande *cmd, t_environment *env_copy)
{
	int		argc;
	char	**argv;

	argc = count_args(cmd->args);
	argv = malloc(sizeof(char *) * (argc + 2));
	if (!argv)
		return (NULL);
	argv[0] = find_executable_path(cmd->cmd, env_copy);
	/* printf("argv0 is %s\n", argv[0]); */
	if (!argv[0])
		return (NULL);
	create_args(argv, cmd);
	return (argv);
}

int	execute_basic_cmd(t_commande *cmd, t_environment *env_copy)
{
	char		*full_path;
	char		**argv;

	full_path = find_executable_path(cmd->cmd, env_copy);
	if (!full_path)
		ft_error(cmd->cmd);
	argv = build_arg(cmd, env_copy);
	if (!argv)
	{
		printf("Malloc error\n");
		return (1);
	}
	// TODO create a list_to_array
	if (execve(full_path, argv, NULL) == -1)
		ft_error(cmd->cmd);
	free_argv(argv);
	free(full_path);
	return (0);
}
