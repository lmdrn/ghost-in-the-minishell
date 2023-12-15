/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:19:27 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/15 15:52:32 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_filename(t_commande *cmd)
{
	t_commande	*head;
	t_args		*curr_arg;
	char		*file;

	head = cmd;
	while (head != NULL)
	{
		curr_arg = head->args;
		while (curr_arg != NULL)
		{
			if (curr_arg->type == 9)
			{
				return (file = curr_arg->next->arg);
				printf("file is %s\n", file);
			}
			curr_arg = curr_arg->next;
		}
		head = head->next;
	}
	return (NULL);
}

char	*create_filename(t_commande *cmd)
{
	char	*filename;

	filename = find_filename(cmd);
	if (filename != NULL)
		return (filename);
	else
		return (NULL);
}

int	create_output_file(t_commande *cmd)
{
	char	*filename;
	int		output_file;

	filename = find_filename(cmd);
	printf("fileanme is %s\n", filename);
	if (filename != NULL)
	{
		output_file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_file == -1)
		{
			perror("Error opening output file");
			exit(EXIT_FAILURE);
		}
		return (output_file);
	}
	return (-1);
}

int	create_output_file2(char *filename)
{
	int		output_file;

	if (filename != NULL)
	{
		output_file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_file == -1)
		{
			perror("Error opening output file");
			exit(EXIT_FAILURE);
		}
		return (output_file);
	}
	return (-1);
}

void	dup_and_close(int *pipe_fd, t_commande *cmd, int output_file)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("Error dup fd1\n");
		close(output_file);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[1]);
	if (cmd->fdin != STDIN_FILENO)
	{
		dup2(cmd->fdin, STDIN_FILENO);
		close(cmd->fdin);
	}
	if (cmd->fdout != STDOUT_FILENO)
	{
		dup2(output_file, STDOUT_FILENO);
		close(cmd->fdout);
	}
}

void	close_fds_output(int output_file, int *pipe_fd)
{
	perror("Error forking");
	close(output_file);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(EXIT_FAILURE);
}

void	pipe_fd_output(int *pipe_fd, int output_file)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("Error creating pipe");
		close(output_file);
		exit(EXIT_FAILURE);
	}
}
