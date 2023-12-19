/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:17:43 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/16 15:19:13 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commande	*create_cmd_node(char *name, t_environment *env_copy, t_type *tokens)
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
	node->fdin = STDIN_FILENO;
	node->fdout = STDOUT_FILENO;
	node->tokens = tokens;
	node->env_copy = env_copy;
	node->next = NULL;
	return (node);
}

void	append_args(t_commande *command, char *arg, int type)
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
	new_arg->type = type;
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

t_commande	*command_list(t_type *tokens, int *pipe_count,
			int *cmd_count, t_environment *env_copy)
{
	t_commande	*cmd_head;
	t_commande	*cmd_current;
	t_commande	*new_cmd;
	t_type		*current;
	char		del;

	del = '|';
	cmd_head = NULL;
	cmd_current = NULL;
	current = tokens;
	*pipe_count = 0;
	*cmd_count = 0;
	while (current != NULL)
	{
		if (current->type == cmd || current->type == builtin)
		{
			(*cmd_count)++;
			new_cmd = create_cmd_node(current->text, env_copy, tokens);
			current = current->next;
			while (current != NULL
				&& (current->type == args
					|| current->type == ch_d
					|| current->type == ch_g
					|| current->type == dbl_ch_g
					|| current->type == dbl_ch_d))
			{
				append_args(new_cmd, current->text, current->type);
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
			return (NULL);
		}
	}
	return (cmd_head);
}
