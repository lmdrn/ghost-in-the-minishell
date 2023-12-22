/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_builtin_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:38:58 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/20 10:12:08 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    print_nodes(t_environment *node)// print la liste, t_pushswap *ps
{
	t_environment *current_node;

	current_node = node;
	printf("Liste \n");
	if (current_node == NULL)
		printf("c'est vide\n");
	while (current_node!= NULL)//ici changer , avant current_node ->next
	{

		printf("key (%s)->value = %s\n",current_node->key , current_node->value);
		//printf ("adresse du node %p\n", current_node->next);
		current_node = current_node->next;
		//i++;
	}
}

void	which_builtin(t_commande *cmd_lst, t_environment *env_copy)
{
	if (ft_strncmp(cmd_lst->cmd, "echo", 4) == 0)
		echo(cmd_lst, env_copy);
	else if (ft_strncmp(cmd_lst->cmd, "pwd", 3) == 0)
		builtin_pwd(cmd_lst);
	else if (ft_strncmp(cmd_lst->cmd, "cd", 2) == 0)
	{
		print_command_list(cmd_lst);
		printf("\n");
		builtin_cd(cmd_lst, env_copy);
	}
	else if (ft_strncmp(cmd_lst->cmd, "export", 6) == 0)
		printf("EXPORT function should happen here\n");
	else if (ft_strncmp(cmd_lst->cmd, "unset", 5) == 0)
		printf("UNSET function should happen here\n");
	else if (ft_strncmp(cmd_lst->cmd, "env", 3) == 0)
		print_env_builtin(env_copy);
	else if (ft_strncmp(cmd_lst->cmd, "exit", 4) == 0)
		printf("EXIT function should happen here\n");
	else
		printf("error happened\n");
}
