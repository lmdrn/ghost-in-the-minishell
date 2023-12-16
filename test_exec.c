/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:33:36 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/16 15:57:08 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_fds2(t_commande *cmd)
{
	int			fds[2];
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	curr_cmd->fdin = STDIN_FILENO;
	while (curr_cmd->next != NULL)
	{
		pipe(fds);
		curr_cmd->fdout = fds[1];
		curr_cmd->next->fdin = fds[0];
		curr_cmd = curr_cmd->next;
	}
	curr_cmd->fdout = STDOUT_FILENO;
}

int	which_token(t_commande *cmd, int token)
{
	t_args	*curr_cmd;

	curr_cmd = cmd->args;
	while (curr_cmd != NULL)
	{
		if (curr_cmd->type == token)
		{
			printf("curr arg type is %d\n", curr_cmd->type);
			return (curr_cmd->type);
		}
		curr_cmd = curr_cmd->next;
	}
	return (-1);
}

void	assign_redir(t_commande *cmd)
{
	t_commande	*curr_cmd;
	char		*filename;

	curr_cmd = cmd;
	while (curr_cmd != NULL)
	{
		if (which_token(curr_cmd, 8) == 8)
		{
			filename = find_filename(curr_cmd);
			printf("filename is %s\n", filename);
			create_input_redir(filename, cmd);
		}
		if (which_token(curr_cmd, 9) == 9)
		{
			filename = find_filename(curr_cmd);
			printf("filename is %s\n", filename);
			create_output_redir(filename, cmd);
		}
		if (which_token(curr_cmd, 10) == 10)
		{
			filename = find_filename(curr_cmd);
			printf("filename is %s\n", filename);
			create_heredoc(filename, cmd);
		}
		if (which_token(curr_cmd, 11) == 11)
		{
			filename = find_filename(curr_cmd);
			printf("filename is %s\n", filename);
			create_append(filename, cmd);
		}
		curr_cmd = curr_cmd->next;
	}
}

t_commande	*is_last_cmd(t_commande *cmd)
{
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	while (curr_cmd->next != NULL)
		curr_cmd = curr_cmd->next;
	return (curr_cmd);
}

int	create_output_redir(char *filename, t_commande *cmd)
{
	int			fd;
	t_commande	*curr_cmd;

	curr_cmd = is_last_cmd(cmd);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (curr_cmd->fdout > 2)
		close(curr_cmd->fdout);
	curr_cmd->fdout = fd;
	return (fd);
}

int	create_input_redir(char *filename, t_commande *cmd)
{
	int			fd;
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (curr_cmd->fdout != 0)
		close(curr_cmd->fdin);
	curr_cmd->fdin = fd;
	return (fd);
}

int	create_append(char *filename, t_commande *cmd)
{
	int			fd;
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (curr_cmd->fdout > 2)
		close(curr_cmd->fdout);
	curr_cmd->fdout = fd;
	return (fd);
}

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
		(void)del;
		if (line == NULL && !ft_strcmp(line, "EOF"))
		{
			free(line);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		write(fd[1], tmp, ft_strlen(tmp));
		free(tmp);
		free (line);
	}
	close(fd[1]);
	return (fd[0]);
}

int	create_heredoc(char *filename, t_commande *cmd)
{
	int			fd;
	t_commande	*curr_cmd;

	curr_cmd = is_last_cmd(cmd);
	fd = heredoc_fd(filename);
	if (fd == -1)
	{
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (curr_cmd->fdout != 0)
		close(curr_cmd->fdin);
	curr_cmd->fdin = fd;
	return (fd);
}

void	close_fds2(t_commande *cmd)
{
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	while (curr_cmd != NULL)
	{
		if (curr_cmd->fdin > 2)
			close(curr_cmd->fdin);
		if (curr_cmd->fdout > 2)
			close(curr_cmd->fdout);
		curr_cmd = curr_cmd->next;
	}
}

void	wait_for_children2(t_commande *cmd)
{
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	while (curr_cmd != NULL)
	{
		if (curr_cmd->pid > 0)
		{
			waitpid(curr_cmd->pid, &curr_cmd->wait_status, 0);
			if (WIFSIGNALED(curr_cmd->wait_status))
				g_status = 128 + WTERMSIG(curr_cmd->wait_status);
			if (WIFEXITED(curr_cmd->wait_status))
				g_status = WIFEXITED(curr_cmd->wait_status);
		}
		curr_cmd = curr_cmd->next;
	}
}

void	fork_it2(t_commande *cmd, t_environment *env_copy)
{
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	curr_cmd->pid = fork();
	if (curr_cmd->pid == 0)
	{
		if (curr_cmd->fdin > 2)
			dup2(curr_cmd->fdin, STDIN_FILENO);
		if (curr_cmd->fdout > 2)
			dup2(curr_cmd->fdout, STDOUT_FILENO);
		close_fds2(cmd);
		execute_basic_cmd(cmd, env_copy);
		g_status = errno;
	}
}

void	send_to_execution2(t_commande *cmd, t_environment *env_copy)
{
	t_commande	*curr_cmd;

	curr_cmd = cmd;
	while (curr_cmd != NULL)
	{
		fork_it2(cmd, env_copy);
		curr_cmd = curr_cmd->next;
	}
	close_fds2(cmd);
	wait_for_children2(cmd);
}
