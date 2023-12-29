/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:25:15 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/29 16:10:03 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_append(char *filename, t_commande *cmd)
{
	int			fd;
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		g_status = 1;
		error_without_exit(1, "Permisssiond denied\n", 0);
		close(fd);
		return (-1);
	}
	if (curr_cmd->fdout > 2)
		close(curr_cmd->fdout);
	curr_cmd->fdout = fd;
	return (fd);
}

void	init_append(t_commande *curr_cmd, t_commande *cmd)
{
	char	*filename;

	filename = find_filename(curr_cmd);
	create_append(filename, cmd);
}
