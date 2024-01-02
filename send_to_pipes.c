/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:21:41 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/02 23:06:37 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_commande *curr_cmd, t_commande *cmd)
{
	if (curr_cmd->fdin != STDIN_FILENO)
		close(cmd->fdin);
	if (curr_cmd->fdout != STDOUT_FILENO)
		close(curr_cmd->fdout);
	wait_for_children(curr_cmd);
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

void	send_to_execution(t_commande *cmd, t_environment *env_copy)
{
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	curr_cmd->pid = fork();
	if (curr_cmd->pid == -1)
	{
		perror("did not fork\n");
		exit(EXIT_FAILURE);
	}
	if (curr_cmd->pid == 0)
	{
		if (curr_cmd->fdin != STDIN_FILENO)
			dup_and_close_fdin(curr_cmd);
		if (curr_cmd->fdout != STDOUT_FILENO)
			dup_and_close_fdout(curr_cmd);
		/* if (is_absolute_path(curr_cmd->cmd) == '/') */
		/* 	execute_absolute_cmd(curr_cmd, env_list_to_array(env_copy)); */
		/* else */
		if (is_builtin(cmd->cmd) == 0)
			which_builtin_exec(cmd, env_copy);
		else
			execute_basic_cmd(cmd, env_copy);
		g_status = errno;
		exit(EXIT_SUCCESS);
	}
	else
		close_fds(curr_cmd, cmd);
}

void	wait_for_children(t_commande *cmd)
{
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	/* printf("g status is %d\n", g_status); */
	while (curr_cmd != NULL)
	{
		if (curr_cmd->pid > 0)
		{
			if (waitpid(curr_cmd->pid, &curr_cmd->wait_status, 0) == -1)
			{
				perror("waitpid\n");
				exit(EXIT_FAILURE);
			}
			if (WIFSIGNALED(curr_cmd->wait_status))
				g_status = 128 + WTERMSIG(curr_cmd->wait_status);
			if (WIFEXITED(curr_cmd->wait_status))
			{
				g_status = WEXITSTATUS(curr_cmd->wait_status);
				/* printf("Child proccess exited with status %d\n", g_status); */
			}
		}
		curr_cmd = curr_cmd->next;
	}
}
