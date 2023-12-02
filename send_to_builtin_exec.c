/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_builtin_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:38:58 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/02 17:51:10 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	which_builtin(t_commande *cmd_lst)
{
	if (ft_strncmp(cmd_lst->cmd, "echo", 4) == 0)
		echo(cmd_lst);
	else if (ft_strncmp(cmd_lst->cmd, "pwd", 3) == 0)
		printf("PWD function should happen here\n");
	else if (ft_strncmp(cmd_lst->cmd, "cd", 2) == 0)
		printf("CD function should happen here\n");
	else if (ft_strncmp(cmd_lst->cmd, "export", 6) == 0)
		printf("EXPORT function should happen here\n");
	else if (ft_strncmp(cmd_lst->cmd, "unset", 5) == 0)
		printf("UNSET function should happen here\n");
	else if (ft_strncmp(cmd_lst->cmd, "env", 3) == 0)
		printf("ENV function should happen here\n");
	else if (ft_strncmp(cmd_lst->cmd, "exit", 4) == 0)
		printf("EXIT function should happen here\n");
	else
		printf("error happened\n");
}
