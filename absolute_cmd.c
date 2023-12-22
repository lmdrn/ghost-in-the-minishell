/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:44:09 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/22 16:47:33 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**build_absolute_arg(t_commande *cmd)
{
	int		argc;
	char	**argv;

	argc = count_args(cmd->args);
	argv = malloc(sizeof(char *) * (argc + 2));
	if (!argv)
		return (NULL);
	argv[0] = cmd->cmd;
	/* printf("argv0 is %s\n", argv[0]); */
	if (!argv[0])
		return (NULL);
	create_args(argv, cmd);
	return (argv);
}

int	is_absolute_path(char *cmd)
{
	char	*node;

	node = cmd;
	/* printf("cmd is : %s\n", node); */
	/* printf("cmd[0] is : %c\n", node[0]); */
	if (node == NULL || *node == '\0')
		return (0);
	return (node[0]);
}

void	execute_absolute_cmd(char **argv, t_commande *cmd)
{
	argv = build_absolute_arg(cmd);
	if (!argv)
	{
		printf("Malloc error\n");
		exit(EXIT_FAILURE);
	}
	/* int	i = 0; */
	/* while (argv[i]) */
	/* { */
	/* 	printf("arg is %s\n", argv[i]); */
	/* 	i++; */	
	/* } */
	// TODO create a list_to_array
	if (execve(cmd->cmd, argv, NULL) == -1)
		ft_error(cmd->cmd);
	free_argv(argv);
}
