/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:33:36 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/02 14:12:52 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_fds(t_commande *cmd)
{
	int			fds[2];
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	curr_cmd->fdin = STDIN_FILENO;
	while (curr_cmd->next != NULL)
	{
		pipe(fds);
		curr_cmd->fdout = fds[1];
		curr_cmd->next->fdin = fds[0];
		curr_cmd = curr_cmd->next;
	}
	curr_cmd->fdout = STDOUT_FILENO;
}

int	which_token(t_commande *cmd, int token)
{
	t_args	*curr_cmd;

	curr_cmd = cmd->args;
	while (curr_cmd != NULL)
	{
		if (curr_cmd->type == token)
		{
			/* printf("curr arg type is %d\n", curr_cmd->type); */
			return (curr_cmd->type);
		}
		curr_cmd = curr_cmd->next;
	}
	return (-1);
}

void	assign_redir(t_commande *cmd)
{
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	while (curr_cmd != NULL)
	{
		if (which_token(curr_cmd, 8) == 8)
			init_input(curr_cmd, cmd);
		if (which_token(curr_cmd, 9) == 9)
			init_output(curr_cmd, cmd);
		if (which_token(curr_cmd, 10) == 10)
			init_heredoc(curr_cmd, cmd);
		if (which_token(curr_cmd, 11) == 11)
			init_append(curr_cmd, cmd);
		curr_cmd = curr_cmd->next;
	}
}
