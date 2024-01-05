/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_builtin_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:38:58 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 00:20:08 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	which_builtin(t_commande *cmd_lst, t_environment *env_copy, int in_exec)
{
	if (ft_strncmp(cmd_lst->cmd, "cd", 3) == 0)
		builtin_cd(cmd_lst, env_copy);
	else if (ft_strncmp(cmd_lst->cmd, "export", 7) == 0)
		export_main(cmd_lst, &env_copy);
	else if (ft_strncmp(cmd_lst->cmd, "unset", 6) == 0)
		built_unset(&env_copy, cmd_lst);
	else if (ft_strncmp(cmd_lst->cmd, "echo", 6) == 0)
		echo(cmd_lst, env_copy);
	else if (ft_strncmp(cmd_lst->cmd, "pwd", 5) == 0)
		builtin_pwd();
	else if (ft_strncmp(cmd_lst->cmd, "env", 4) == 0)
		print_env_builtin(env_copy, cmd_lst);
	else if (ft_strncmp(cmd_lst->cmd, "exit", 4) == 0
		|| ft_strncmp(cmd_lst->cmd, "exit ", 5) == 0)
		builtin_exit(cmd_lst->cmd, in_exec);
	else
	{
		printf("Error: %s: command not found\n", cmd_lst->cmd);
		g_status = 127;
		return ;
	}
}
