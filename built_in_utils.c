/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:58:36 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/20 18:13:28 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_in_env(t_environment *env_copy, char *var)
{
	t_environment *current;

	current = env_copy;
	if (current != NULL)
	{
		while (current->key != NULL)
		{
			if (strcmp(current->key, var) == 0)
			{
//				printf("key found \n");
				return (SUCCESS);
			}
			current = current->next;
		}
		return (ERROR);
	}
	else
		return (ERROR);
}
//void print_command_list(t_commande *cmd_list)
//{
//	t_commande *current_cmd = cmd_list;
//	t_args *current_arg;
//
//	while (current_cmd != NULL)
//	{
//		printf("Command: %s\n", current_cmd->cmd);
//		printf("  fdin: %d, fdout: %d\n", current_cmd->fdin, current_cmd->fdout);
//		printf("  pid: %d, wait_status: %d\n", current_cmd->pid, current_cmd->wait_status);
//		// Ajoutez ici les impressions pour env_copy et tokens si nécessaire
//
//		current_arg = current_cmd->args;
//		if (current_arg == NULL)
//		{
//			printf("  Arg: est NUll\n");
//		}
//		while (current_arg != NULL)
//		{
//			printf("  Arg: %s, Type: %d\n", current_arg->arg, current_arg->type);
//			current_arg = current_arg->next;
//		}
//
//
//		current_cmd = current_cmd->next;
//	}
//}

void print_command_list(t_commande *cmd_list)
{
	t_commande *current_cmd = cmd_list;
	t_args *current_arg;

	while (current_cmd != NULL)
	{
		if (current_cmd == NULL || current_cmd->cmd == NULL)  {
			printf("skip la cmd\n");
			current_cmd = current_cmd->next;
			continue; // Passez à la commande suivante si cmd est nul
		}

		printf("Command: %s\n", current_cmd->cmd);
		//printf("  fdin: %d, fdout: %d\n", current_cmd->fdin, current_cmd->fdout);
		//printf("  pid: %d, wait_status: %d\n", current_cmd->pid, current_cmd->wait_status);
		// Ajoutez ici les impressions pour env_copy et tokens si nécessaire

		current_arg = current_cmd->args;
		if (current_arg == NULL) {
			printf("  Args: None\n");
		}
		while (current_arg != NULL)
		{
			if (current_arg->arg != NULL) {
				printf("  Arg: %s, Type: %d\n", current_arg->arg, current_arg->type);
			} else {
				printf("  Arg: NULL\n");
			}
			current_arg = current_arg->next;
		}

		current_cmd = current_cmd->next;
	}
}

void	print_value(t_environment *env_copy, char *key)
{
	t_environment *current;

	current = env_copy;
	while (current->key != NULL)
	{
		if (strcmp(current->key, key) == 0)
			printf("Key: %s, Value: %s\n", current->key, current->value);
		current = current->next;
	}
}

char	*get_env_value(t_environment *env_copy, char *env_key)
{
	t_environment	*current;

	current = env_copy;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, env_key) == 0)
			break ;
		current = current->next;
	}
	return (current->value);
}

int	check_path(char *path)
{
	if (access(path, F_OK) != -1)
		return (SUCCESS);
	else
	{
		printf("cd : no such file or directory :%s\n", path);
		return (ERROR);
	}
}

