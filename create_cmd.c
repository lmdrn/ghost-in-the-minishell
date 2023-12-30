/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:17:43 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/30 16:56:49 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commande	*create_cmd_node(char *name, t_environment *env_copy,
		t_type *tokens)
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

t_args	*create_new_arg(char *arg, int type)
{
	t_args	*new_arg;

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
	return (new_arg);
}

void	append_args(t_commande *command, char *arg, int type)
{
	t_args	*new_arg;
	t_args	*current;

	new_arg = create_new_arg(arg, type);
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

t_type	*process_command_args(t_commande *new_cmd, t_type *tokens)
{
	t_type	*current;
	t_type	*remaining;

	current = tokens;
	remaining = NULL;
	if (current != NULL && (current->type == cmd || current->type == builtin))
		current = current->next;
	while (current != NULL && is_args_or_redir(current) == 0
		&& current->type != is_pipe)
	{
		append_args(new_cmd, current->text, current->type);
		remaining = current->next;
		current = remaining;
	}
	if (current != NULL && current->type == is_pipe && current->text[0] == '|')
		remaining = current->next;
	new_cmd->tokens = remaining;
	return (remaining);
}

void	append_args_redir(t_args **args, char *arg, int type)
{
	t_args	*new_arg;
	t_args	*current;

	new_arg = create_new_arg(arg, type);
	if (*args == NULL)
		*args = new_arg;
	else
	{
		current = *args;
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

void	process_redir_args(t_type *tokens, t_commande **cmd_head, t_commande **cmd_current)
{
	t_type		*tmp;
	t_args		*args_lst;
	t_commande	*new_cmd;
	char		*is_cmd;

	tmp = tokens;
	args_lst = NULL;
	new_cmd = NULL;
	while (tmp != NULL)
	{
		if (tmp->type == cmd || tmp->type == builtin)
			is_cmd = tmp->text;
		else if (tmp->type != cmd)
			append_args_redir(&args_lst, tmp->text, tmp->type);
		tmp = tmp->next;
	}
	new_cmd = create_cmd_node(is_cmd, NULL, NULL);
	new_cmd->args = args_lst;
	args_lst = NULL;
	if (new_cmd != NULL)
	{
		if (*cmd_head == NULL)
		{
			*cmd_head = new_cmd;
			*cmd_current = new_cmd;
		}
		else
		{
			(*cmd_current)->next = new_cmd;
			*cmd_current = new_cmd;
		}
	}
	/* if (new_cmd != NULL) */
	/* { */
	/* 	printf("Command: %s\n", new_cmd->cmd); */
	/* 	t_args *temp = new_cmd->args; */
	/* 	while (temp != NULL) */
	/* 	{ */
	/* 		printf("Arg: %s\n", temp->arg); */
	/* 		temp = temp->next; */
	/* 	} */
	/* } */
}

t_commande	*command_list(t_type *tokens, t_environment *env_copy)
{
	t_commande	*cmd_head;
	t_commande	*cmd_current;
	t_commande	*new_cmd;
	t_type		*tmp;

	tmp = tokens;
	cmd_head = NULL;
	cmd_current = NULL;
	while (tokens != NULL)
	{
		if (is_redir(tokens) == 0)
		{
			process_redir_args(tokens, &cmd_head, &cmd_current);
			break ;
		}
		else if (tokens->type == cmd || tokens->type == builtin)
		{
			new_cmd = create_cmd_node(tokens->text, env_copy, tokens);
			tokens = process_command_args(new_cmd, tokens);
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
			break ;
		}
		else
			return (NULL);
		tokens = tokens->next;
	}
	return (cmd_head);
}
