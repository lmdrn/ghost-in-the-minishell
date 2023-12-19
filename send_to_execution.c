/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:44:25 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/19 14:49:23 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Function to check whether pipe number is odd or even
int	is_odd_or_even(int *pipe_count, int *cmd_count)
{
	if ((*pipe_count % 2 != 0) && (*cmd_count % 2 == 0))
	{
		printf("Odd pipes and even commands\n");
		printf("Send to execute_pipeline\n");
		return (1);
	}
	else if ((*pipe_count % 2 == 0) && (*cmd_count % 2 != 0)
		&& (*cmd_count > 1))
	{
		printf("Even pipes and odd commands\n");
		printf("Send to execute_pipeline\n");
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
	}
	return (0);
}
