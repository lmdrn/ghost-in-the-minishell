/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:21:41 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/14 14:39:47 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_fds(t_commande *cmd, int *fd)
{
	cmd->fdin = 0;
	while (cmd->next != NULL)
	{
		pipe(fd);
		cmd->fdout = fd[1];
		cmd->next->fdin = fd[0];
		cmd = cmd->next;
	}
	cmd->fdout = STDOUT_FILENO;
}

void	close_fds(t_commande *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->fdin != STDIN_FILENO)
			close(cmd->fdin);
		if (cmd->fdout != STDOUT_FILENO)
			close(cmd->fdout);
		cmd = cmd->next;
	}
}

int	has_output(t_commande *cmd)
{
	while (cmd != NULL)
	{
		while (cmd->args != NULL)
		{
			if (cmd->args->type == 9)
			{
				return (cmd->args->type);
			}
			cmd->args = cmd->args->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

void	execute_pipeline(t_commande *cmd_lst, t_environment *env_copy)
{
	int			fd[2];
	int			pid;

	assign_fds(cmd_lst, fd);
	while (cmd_lst != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmd_lst->fdin != STDIN_FILENO)
			{
				dup2(cmd_lst->fdin, STDIN_FILENO);
				close(cmd_lst->fdin);
			}
			if (cmd_lst->fdout != STDOUT_FILENO)
			{
				dup2(cmd_lst->fdout, STDOUT_FILENO);
				close(cmd_lst->fdin);
			}
			execute_basic_cmd(cmd_lst, env_copy);
		}
		else
		{
			if (cmd_lst->fdin != STDIN_FILENO)
				close(cmd_lst->fdin);
			if (cmd_lst->fdout != STDOUT_FILENO)
				close(cmd_lst->fdout);
			waitpid(pid, NULL, 0);
		}
		cmd_lst = cmd_lst->next;
	}
}
