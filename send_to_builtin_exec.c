/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_builtin_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:38:58 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/02 23:12:28 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	which_builtin(t_commande *cmd_lst, t_environment *env_copy)
{
	if (ft_strncmp(cmd_lst->cmd, "cd", 2) == 0)
	{
		builtin_cd(cmd_lst, env_copy);
	}
	else if (ft_strncmp(cmd_lst->cmd, "export", 6) == 0)
		export_main(cmd_lst, &env_copy);
	else if (ft_strncmp(cmd_lst->cmd, "unset", 5) == 0)
		built_unset(&env_copy, cmd_lst);
	else
		return ;
}

void	which_builtin_exec(t_commande *cmd_lst, t_environment *env_copy)
{
	if (ft_strncmp(cmd_lst->cmd, "echo", 4) == 0)
		echo(cmd_lst, env_copy);
	else if (ft_strncmp(cmd_lst->cmd, "pwd", 3) == 0)
		builtin_pwd(cmd_lst);
	else if (ft_strncmp(cmd_lst->cmd, "env", 3) == 0)
		print_env_builtin(env_copy, cmd_lst);
	else
		return ;
}
