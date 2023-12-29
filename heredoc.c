/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:47:08 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/29 18:42:27 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_fd(char	*del)
{
	int		fd[2];
	char	*line;
	char	*tmp;

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!ft_strcmp(line, del))
		{
			free(line);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		printf("tmo is %s\n", tmp);
		write(fd[1], tmp, ft_strlen(tmp));
		free(tmp);
		free (line);
	}
	close(fd[1]);
	return (fd[0]);
}

t_commande	*is_last_cmd(t_commande *cmd)
{
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	while (curr_cmd->next != NULL)
		curr_cmd = curr_cmd->next;
	return (curr_cmd);
}

int	create_heredoc(char *filename, t_commande *cmd)
{
	int			fd;
	t_commande	*curr_cmd;

	curr_cmd = is_last_cmd(cmd);
	fd = heredoc_fd(filename);
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

void	init_heredoc(t_commande *curr_cmd, t_commande *cmd)
{
	char	*filename;

	filename = find_filename(curr_cmd);
	create_heredoc(filename, cmd);
}
