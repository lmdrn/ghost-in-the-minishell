/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:21:41 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/18 09:58:52 by lmedrano         ###   ########.fr       */
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

void	execute_pipeline(t_commande *cmd_lst, t_environment *env_copy)
{
	int			fd[2];
	int			pid;
	int			output_file;
	char		*filename;

	assign_fds(cmd_lst, fd);
	while (cmd_lst != NULL)
	{
		filename = create_filename(cmd_lst);
		output_file = -1;
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
				close(cmd_lst->fdout);
			}
			if (filename != NULL)
			{
				output_file = create_output_file2(filename);
				printf("output file %d\n", output_file);
				redir_execution(cmd_lst, env_copy, output_file);
				exit(EXIT_SUCCESS);
			}
			else
			{
				execute_basic_cmd(cmd_lst, env_copy);
				exit(EXIT_SUCCESS);
			}
		}
		else
		{
			if (cmd_lst->fdin != STDIN_FILENO)
				close(cmd_lst->fdin);
			if (cmd_lst->fdout != STDOUT_FILENO)
				close(cmd_lst->fdout);
			if (filename != NULL)
				write_on_output(output_file, fd);
			waitpid(pid, NULL, 0);
		}
		cmd_lst = cmd_lst->next;
	}
}
