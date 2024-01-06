/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:26:02 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/06 16:56:53 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_input_redir(char *filename, t_commande *cmd)
{
	int			fd;
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		g_status = 1;
		printf("Error: %s No such file or directory\n", filename);
		close(fd);
		return (-1);
	}
	if (curr_cmd->fdin != 0)
		close(curr_cmd->fdin);
	curr_cmd->fdin = fd;
	return (fd);
}

int	init_input(t_commande *curr_cmd, t_commande *cmd)
{
	char	*filename;
	t_args	*args;

	args = curr_cmd->args;
	while (args != NULL)
	{
		if (args->type == 8)
		{
			filename = find_filename(args);
			if (filename != NULL)
			{
				if (create_input_redir(filename, cmd) == -1)
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
