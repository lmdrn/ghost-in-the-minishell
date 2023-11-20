/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:44:25 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/20 12:21:13 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Function to check whether pipe number is odd or even
int	is_odd_or_even(int *pipe_count, int *cmd_count)
{
	if ((*pipe_count % 2 != 0) && (*cmd_count % 2 == 0))
	{
		printf("Odd pipes and even commands\n");
		return (1);
	}
	else if ((*pipe_count % 2 == 0) && (*cmd_count % 2 != 0)
		&& (*cmd_count > 1))
	{
		printf("Even pipes and odd commands\n");
		return (2);
	}
	else if (!(*pipe_count) && *cmd_count == 1)
	{
		printf("One command and no pipes >> sending to exec\n");
		return (3);
	}
	else if (((*pipe_count % 2 == 0) && (*cmd_count % 2 == 0))
		|| (*pipe_count % 2 != 0 && *cmd_count % 2 != 0))
	{
		printf("Error: Not enough cmds or pipes\n");
		exit(1);
	}
	return (0);
}

//fucntion that forks process when cmd is found, then sends to execve
void	duplicate_process(t_commande *cmd_lst, t_environment *env_copy)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Woopsie, fork did not work...\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execute_basic_cmd(cmd_lst, env_copy);
	}
	else
	{
		wait(&g_status);
		printf("Waiting succesful, command has been executed\n");
	}
}
