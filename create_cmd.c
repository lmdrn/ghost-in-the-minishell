/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:17:43 by lmedrano          #+#    #+#             */
/*   Updated: 2023/10/05 11:49:59 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//todo
//1. create a new List
//2. create and alloc mem for each node
//3. each node should be delimited by a |
//4. ur guuud to go mothafucka

t_commande	*create_cmd_node(char *name)
{
	t_commande	*node;

	node = malloc(sizeof(t_commande));
	if (node == NULL)
	{
		printf("Malloc error\n");
		exit(1);
	}
	node->cmd = ft_strdup(name);
	if (node->cmd == NULL)
	{
		printf("Duplicate error\n");
		exit(1);
	}
	node->args = NULL;
	node->fdin = NULL;
	node->fdout = NULL;
	node->next = NULL;
	return (node);
}

void	append_args(t_commande *command, char *arg)
{
	t_args	*new_arg;
	t_args	*current;

	new_arg = malloc(sizeof(t_args));
	if (new_arg == NULL)
	{
		printf("Malloc error\n");
		exit(1);
	}
	new_arg->arg = ft_strdup(arg);
	if (new_arg->arg == NULL)
	{
		printf("Duplicate error\n");
		exit(1);
	}
	new_arg->next = NULL;
	if (command->args == NULL)
		command->args = new_arg;
	else
	{
		current = command->args;
		if (current == NULL)
		{
			printf("Error command->args is NULL\n");
			exit(1);
		}
		while (current->next != NULL)
			current = current->next;
		current->next = new_arg;
	}
}

t_commande	*command_list(t_type *tokens, char del, int *pipe_count, int *cmd_count)
{
	t_commande	*cmd_head;
	t_commande	*cmd_current;
	t_commande	*new_cmd;
	t_type		*current;

	cmd_head = NULL;
	cmd_current = NULL;
	current = tokens;
	*pipe_count = 0;
	*cmd_count = 0;
	while (current != NULL)
	{
		if (current->type == cmd)
		{
			(*cmd_count)++;
			new_cmd = create_cmd_node(current->text);
			current = current->next;
			while (current != NULL && current->type == args)
			{
				append_args(new_cmd, current->text);
				current = current->next;
			}
			if (cmd_head == NULL)
			{
				cmd_head = new_cmd;
				cmd_current = new_cmd;
			}
			else
			{
				cmd_current->next = new_cmd;
				cmd_current = new_cmd;
			}
		}
		else if (current->type == is_pipe && current->text[0] == del)
		{
			(*pipe_count)++;
			current = current->next;
		}
		else
		{
			printf("Unexpected node type\n");
			exit(1);
		}
	}
	return (cmd_head);
}

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
		free(tmp->fdin);
		free(tmp->fdout);
		free(tmp);
	}
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
		printf("Input File: %s ", current->fdin);
		printf("Output File: %s ", current->fdout);
		printf("\n");
		current = current->next;
	}
}
