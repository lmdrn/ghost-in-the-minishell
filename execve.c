/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:06:44 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/31 12:18:25 by lmedrano         ###   ########.fr       */
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
	printf("TOKS %s\n", epi.tok_s);
	while (epi.tok_s != NULL)
	{
		epi.tok_e = ft_strchr(epi.tok_s, ':');
		printf("TOKE %s\n", epi.tok_e);
		if (epi.tok_e != NULL)
		{
			epi.seg = segment_malloc_copy(epi.seg, epi.tok_s, epi.tok_e);
			printf("SEGMENT %s\n", epi.seg);
			epi.cmd_path = concat_path_cmd(epi.seg, cmd);
			printf("CMDPATH %s\n", epi.cmd_path);
			free(epi.seg);
			if (access(epi.cmd_path, F_OK) == 0
				|| access(epi.cmd_path, X_OK) == 0)
			{
				free(epi.path);
				printf("ACCESS_OK\n");
				return (epi.cmd_path);
			}
			/* free(epi.cmd_path); */
			printf("I DID NOT GO INTO ACCESS\n");
			epi.tok_s = epi.tok_e + 1;
		}
		else
		{
			printf("ACCESS_NOTOK\n");
			epi.cmd_path = concat_cmd(epi.cmd_path, epi.path, epi.tok_s, cmd);
			epi.tok_s = NULL;
		}
	}
	free(epi.path);
	return (NULL);
}

void	create_args(char **argv, t_commande *cmd)
{
	int		i;
	t_args	*arg;
	t_args	*head;

	i = 1;
	arg = cmd->args;
	head = cmd->args;
	while (arg)
	{
		/* printf("arg->arg is %s\n", arg->arg); */
		if (arg == head && (arg->type == 8 || arg->type == 9
				|| arg->type == 10 || arg->type == 11))
			arg = arg->next;
		else if (arg->next != NULL && (arg->type == 8
				|| arg->type == 9 || arg->type == 10 || arg->type == 11))
			break ;
		else
			copy_argument(argv, &i, arg->arg);
		arg = arg->next;
	}
	argv[i] = NULL;
}

char	**build_arg(t_commande *cmd, char *full_path)
{
	int		argc;
	char	**argv;

	argc = count_args(cmd->args);
	argv = malloc(sizeof(char *) * (argc + 2));
	if (!argv)
		return (NULL);
	argv[0] = full_path;
	printf("argv0 is %s\n", argv[0]);
	if (!argv[0])
		return (NULL);
	create_args(argv, cmd);
	return (argv);
}

int	execute_basic_cmd(t_commande *cmd, t_environment *env_copy)
{
	execute_command(cmd, env_copy);
	return (g_status);
}
