/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:36:47 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 15:57:11 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_output_redir(char *filename, t_commande *cmd)
{
	int			fd;
	t_commande	*curr_cmd;

	curr_cmd = is_last_cmd(cmd);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		g_status = 1;
		error_without_exit(1, "File not found\n", 0);
		close(fd);
		return (-1);
	}
	if (curr_cmd->fdout > 2)
		close(curr_cmd->fdout);
	curr_cmd->fdout = fd;
	return (fd);
}

int	init_output(t_commande *curr_cmd, t_commande *cmd)
{
	char	*filename;
	t_args	*args;

	args = curr_cmd->args;
	while (args != NULL)
	{
		if (args->type == 9)
		{
			filename = find_filename(args);
			if (filename != NULL)
			{
				if (create_output_redir(filename, cmd) == -1)
				{
					g_status = 258;
					return (-1);
				}
			}
		}
		args = args->next;
	}
	return (0);
}
