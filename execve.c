/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:06:44 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/06 21:47:14 by lmedrano         ###   ########.fr       */
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
	char	*ret;

	copy_the_path(env_copy, &epi);
	while (epi.tok_s != NULL)
	{
		epi.tok_e = ft_strchr(epi.tok_s, ':');
		if (epi.tok_e != NULL)
		{
			ret = find_exec_access(&epi, cmd);
			if (ret)
				return (ret);
		}
		else
		{
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
	if (!argv[0])
		return (NULL);
	create_args(argv, cmd);
	return (argv);
}

int	execute_basic_cmd(t_commande *cmd, t_environment *env_copy)
{
	if (access(cmd->cmd, F_OK | X_OK) == 0)
		execute_absolute_cmd(cmd, env_list_to_array(env_copy));
	else
		execute_command(cmd, env_copy);
	return (g_status);
}
