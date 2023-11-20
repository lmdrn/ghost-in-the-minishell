/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:21:41 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/20 18:10:47 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	send_to_pipes(t_environment *env_copy,
		t_commande *cmd_lst)
{
	int		pipe_fds[2];
	int		cmd_index;
	pid_t	pid;
	char	*full_path;
	char	**argv;

	cmd_index = 0;
	while (cmd_lst != NULL)
	{
		if (pipe(pipe_fds) == -1)
		{
			printf("Pipe error\n");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		printf("fdin is:%d\n", cmd_lst->fdin);
		if (pid == -1)
		{
			printf("fork error\n");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (cmd_lst->fdin == STDIN_FILENO)
			{
				dup2(cmd_lst->fdin, STDIN_FILENO);
				close(cmd_lst->fdin);
			}
			if (cmd_lst->fdout == STDOUT_FILENO)
			{
				dup2(cmd_lst->fdout, STDOUT_FILENO);
				close(cmd_lst->fdout);
			}
			if (cmd_lst->next != NULL)
			{
				dup2(pipe_fds[0], STDIN_FILENO);
				close(pipe_fds[0]);
			}
			if (cmd_lst->next != NULL)
			{
				dup2(pipe_fds[1], STDOUT_FILENO);
				close(pipe_fds[1]);
			}
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			full_path = find_executable_path(cmd_lst->cmd, env_copy);
			argv = build_arg(cmd_lst, env_copy);
			if (full_path != NULL)
			{
				execve(full_path, argv, NULL);
				printf("Error executing %s\n", cmd_lst->cmd);
				free(full_path);
			}
			else
				printf("Executable not found for %s\n", cmd_lst->cmd);
		}
		else
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
		}
		cmd_lst = cmd_lst->next;
	}
}
