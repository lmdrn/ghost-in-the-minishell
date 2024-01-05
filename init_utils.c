/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:36:40 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 21:51:43 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_type *tokens)
{
	t_type	*tmp;

	while (tokens != NULL)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->text);
		tmp->text = NULL;
		free(tmp);
		tmp = NULL;
	}
	free(tokens);
}

int	if_cmd_is_null(t_type *tokens)
{
	int	fd;

	if (tokens->type == 8 && tokens->next)
	{
		fd = open(tokens->next->text, O_RDONLY);
		if (fd < 0)
		{
			printf("Error: %s: No such file or directory\n",
				tokens->next->text);
			return (1);
		}
		return (1);
	}
	g_status = 127;
	free_tokens(tokens);
	return (-1);
}

t_commande	*create_cmd_list(t_type *tokens, t_environment *env_copy)
{
	t_commande	*cmd_lst;

	cmd_lst = NULL;
	if (tokens->type == 0 || tokens->type == 1 || tokens->type == 14)
		cmd_lst = command_list(tokens, env_copy);
	else if (tokens->type == 8 || tokens->type == 9 || tokens->type == 10
		|| tokens->type == 11)
		cmd_lst = command_list_redir(tokens);
	return (cmd_lst);
}

int	execution_stuff(t_commande *new_cmd_lst, t_type *tokens,
	t_commande *cmd_lst, t_environment *env_copy)
{
	while (new_cmd_lst != NULL)
	{
		if (assign_redir(new_cmd_lst) == -1)
		{
			free_tokens(tokens);
			return (-1);
		}
		send_to_execution(new_cmd_lst, cmd_lst, env_copy);
		new_cmd_lst = new_cmd_lst->next;
	}
	close_fds(cmd_lst);
	wait_for_children(cmd_lst);
	clear_commande_list(&cmd_lst);
	return (0);
}

int	execute_single_cmd(t_commande *new_cmd_lst, t_type *tokens,
		t_environment *env_copy)
{
	if (assign_redir(new_cmd_lst) == -1)
	{
		free_tokens(tokens);
		return (-1);
	}
	which_builtin(new_cmd_lst, env_copy, 0);
	return (0);
}
