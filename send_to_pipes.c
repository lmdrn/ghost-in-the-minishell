/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:21:41 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/03 19:04:01 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_commande *curr_cmd)
{
	t_commande	*cmd;

	cmd = curr_cmd;
	while (cmd)
	{
		if (cmd->fdin > 2)
			close(cmd->fdin);
		if (cmd->fdout > 2)
			close(cmd->fdout);
		cmd = cmd->next;
	}
}

void	dup_and_close_fdin(t_commande *curr_cmd)
{
	if (dup2(curr_cmd->fdin, STDIN_FILENO) == -1)
	{
		perror("fdin dup did not work\n");
		exit(EXIT_FAILURE);
	}
	close(curr_cmd->fdin);
}

void	dup_and_close_fdout(t_commande *curr_cmd)
{
	if (dup2(curr_cmd->fdout, STDOUT_FILENO) == -1)
	{
		perror("fdout dup did not work\n");
		exit(EXIT_FAILURE);
	}
	close(curr_cmd->fdout);
}

void	send_to_execution(t_commande *cmd, t_commande *head,
			t_environment *env_copy)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("did not fork\n");
		exit(EXIT_FAILURE);
	}
	if (cmd->pid == 0)
	{
		if (cmd->fdin > 2)
			dup2(cmd->fdin, STDIN_FILENO);
		if (cmd->fdout > 2)
			dup2(cmd->fdout, STDOUT_FILENO);
		close_fds(head);
		if (is_builtin(cmd->cmd) == 0)
			which_builtin_exec(cmd, env_copy);
		else
		{
			execute_basic_cmd(cmd, env_copy);
			g_status = errno;
		}
		exit(1);
	}
}

void	wait_for_children(t_commande *cmd)
{
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	while (curr_cmd != NULL)
	{
		if (curr_cmd->pid > 0)
		{
			if (waitpid(curr_cmd->pid, &curr_cmd->wait_status, 0) == -1)
				exit(EXIT_FAILURE);
			if (WIFSIGNALED(curr_cmd->wait_status))
				g_status = 128 + WTERMSIG(curr_cmd->wait_status);
			if (WIFEXITED(curr_cmd->wait_status))
				g_status = WEXITSTATUS(curr_cmd->wait_status);
		}
		curr_cmd = curr_cmd->next;
	}
}
