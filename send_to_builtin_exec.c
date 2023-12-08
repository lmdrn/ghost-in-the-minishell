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

void print_env(t_environment    *env_copy)
{
	int                i;
	i = 0;
	if (env_copy!= NULL)
	{
		while (env_copy[i].key != NULL)
		{
			printf("Key: %s, Value: %s\n", env_copy[i].key, env_copy[i].value);
			i++;
		}
	} else
		return;

}
void	which_builtin(t_commande *cmd_lst, t_environment *env_copy)
{
	if (ft_strncmp(cmd_lst->cmd, "echo", 4) == 0)
		printf("ECHO function should happen here\n");
	else if (ft_strncmp(cmd_lst->cmd, "pwd", 3) == 0)
		builtin_pwd(cmd_lst);
	else if (ft_strncmp(cmd_lst->cmd, "cd", 2) == 0)
	{
		//printf("plop\n");
		//print_env(env_copy);
		printf("\n------------\n");

		builtin_cd(cmd_lst, env_copy);
	}

	else if (ft_strncmp(cmd_lst->cmd, "export", 6) == 0)
		builtin_export(cmd_lst, env_copy);
	else if (ft_strncmp(cmd_lst->cmd, "unset", 5) == 0)
		printf("UNSET function should happen here\n");
	else if (ft_strncmp(cmd_lst->cmd, "env", 3) == 0)
		print_env_builtin(env_copy);
	else if (ft_strncmp(cmd_lst->cmd, "exit", 4) == 0)
		printf("EXIT function should happen here\n");
	else
		printf("error happened\n");
}
