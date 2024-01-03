/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:31:24 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/03 21:31:52 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(t_args *args)
{
	t_args	*temp;

	while (args != NULL)
	{
		temp = args;
		args = args->next;
		free(temp->arg);
		free(temp);
	}
}

// Function to free the memory occupied by the t_commande nodes
void	free_commande_list(t_commande *head)
{
	t_commande	*current;
	t_commande	*tmp;

	current = head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp->cmd);
		free_args(tmp->args);
		free(tmp);
	}
}

void	clear_commande_list(t_commande **lst)
{
	t_commande	*current;
	t_commande	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free(current->cmd);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	print_commande_list(t_commande *head)
{
	t_commande	*current;
	t_args		*args_current;

	current = head;
	while (current != NULL)
	{
		printf("Command: %s ", current->cmd);
		printf("has arguments: ");
		args_current = current->args;
		while (args_current != NULL)
		{
			printf("%s ", args_current->arg);
			args_current = args_current->next;
		}
		printf("Input File: %d ", current->fdin);
		printf("Output File: %d ", current->fdout);
		printf("\n");
		current = current->next;
	}
}

int	count_list(t_commande *cmd)
{
	int			i;
	t_commande	*curr;

	i = 0;
	curr = cmd;
	while (curr != NULL)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}
