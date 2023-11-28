/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:36:47 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/28 15:43:27 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_output_redir(t_commande *cmd, t_environment *env_copy)
{
	char *file;
	int	fdout;

	//add check arg after the redir
	file = cmd->args->arg;
	fdout = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fdout == -1)
	{
		printf("Error opening file\n");
		exit(EXIT_FAILURE);
	}
	if (dup2(fdout, STDOUT_FILENO) == -1)
	{
		printf("Error redirecting standard output\n");
		exit(EXIT_FAILURE);
	}
	close(fdout);
	execute_basic_cmd(cmd, env_copy);
	if (dup2(STDOUT_FILENO, fdout) == -1)
	{
		printf("Error restoring standard output\n");
		exit(EXIT_FAILURE);
	}
}
