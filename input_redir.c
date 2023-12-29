/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:26:02 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/29 16:10:50 by lmedrano         ###   ########.fr       */
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
		error_without_exit(1, "Permission denied\n", 0);
		close(fd);
		return (-1);
	}
	if (curr_cmd->fdin != 0)
		close(curr_cmd->fdin);
	curr_cmd->fdin = fd;
	return (fd);
}

void	init_input(t_commande *curr_cmd, t_commande *cmd)
{
	char	*filename;

	filename = find_filename(curr_cmd);
	create_input_redir(filename, cmd);
}
