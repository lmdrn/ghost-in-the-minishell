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

void print_env(t_environment    *env_copy, int count) // besoin taille remplie
{
	int	i;
	i = 0;
	if (env_copy!= NULL )
	{
		while (i < count && env_copy[i].key != NULL)//env_copy[i].key != NULL
		{
			printf("Key: %s, Value: %s", env_copy[i].key, env_copy[i].value);
			if (i < count - 1 && env_copy[i + 1].key != NULL)
			{
				printf("\n");
			}
			i++;
		}
	}
	else
		printf("Env is empty or invalid.\n");

}

void which_builtin(t_commande *cmd_lst, t_environment *env_copy)
{

	//count_env->count_filled = env_count_env_copy(env_copy); // compte le nombre de case rempli

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
		export_main(cmd_lst, &env_copy);
	else if (ft_strncmp(cmd_lst->cmd, "unset", 5) == 0)
		printf("UNSET function should happen here\n");
	else if (ft_strncmp(cmd_lst->cmd, "env", 3) == 0)
		print_env_builtin(env_copy);
	else if (ft_strncmp(cmd_lst->cmd, "exit", 4) == 0)
		printf("EXIT function should happen here\n");
	else
		printf("error happened\n");
}
