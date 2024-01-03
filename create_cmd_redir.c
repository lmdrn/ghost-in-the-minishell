/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:46:55 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/30 20:53:49 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	process_token(t_type *token, char **is_cmd, t_args **args_lst)
{
	if (token->type == cmd || token->type == builtin)
		*is_cmd = token->text;
	else if (token->type != cmd)
		append_args_redir(args_lst, token->text, token->type);
}

void	update_command_list(t_commande **cmd_head,
		t_commande **cmd_current, t_commande *new_cmd)
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

void	process_redir_args(t_type *tokens,
		t_commande **cmd_head, t_commande **cmd_current)
{
	t_type		*tmp;
	t_args		*args_lst;
	t_commande	*new_cmd;
	char		*is_cmd;

	tmp = tokens;
	args_lst = NULL;
	new_cmd = NULL;
	is_cmd = NULL;
	while (tmp != NULL)
	{
		process_token(tmp, &is_cmd, &args_lst);
		tmp = tmp->next;
	}
	if (is_cmd == NULL)
		return ;
	new_cmd = create_cmd_node(is_cmd, NULL, NULL);
	new_cmd->args = args_lst;
	args_lst = NULL;
	if (new_cmd != NULL)
		update_command_list(cmd_head, cmd_current, new_cmd);
}

t_commande	*command_list_redir(t_type *tokens)
{
	t_commande	*cmd_head;
	t_commande	*cmd_current;

	cmd_head = NULL;
	cmd_current = NULL;
	while (tokens != NULL)
	{
		if (is_redir(tokens) == 0)
		{
			process_redir_args(tokens, &cmd_head, &cmd_current);
			break ;
		}
		else
			return (NULL);
		tokens = tokens->next;
	}
	return (cmd_head);
}
