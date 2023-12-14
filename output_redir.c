/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:36:47 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/14 14:44:52 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_execution(t_commande *cmd, t_environment *env_copy,
			int output_file)
{
	char	*full_path;
	char	**argv;

	full_path = find_executable_path(cmd->cmd, env_copy);
	if (!full_path)
		ft_error(cmd->cmd);
	argv = build_arg(cmd, env_copy);
	if (!argv)
	{
		printf("Malloc error\n");
		close(output_file);
		exit(EXIT_FAILURE);
	}
	if (execve(full_path, argv, NULL) == -1)
	{
		perror("Error executing cmd\n");
		ft_error(cmd->cmd);
	}
}

void	write_on_output(int output_file, int *pipe_fd)
{
	char	buffer[256];
	size_t	bytes_read;

	bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		write(output_file, buffer, bytes_read);
		bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
	}
}

void	execute_redir(t_commande *cmd, t_environment *env_copy)
{
	int		output_file;
	int		pipe_fd[2];
	pid_t	pid;

	output_file = create_output_file(cmd);
	pipe_fd_output(pipe_fd, output_file);
	pid = fork();
	if (pid == -1)
		close_fds_output(output_file, pipe_fd);
	if (pid == 0)
	{
		dup_and_close(pipe_fd, cmd, output_file);
		redir_execution(cmd, env_copy, output_file);
		close(output_file);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipe_fd[1]);
		write_on_output(output_file, pipe_fd);
		close(output_file);
		close(pipe_fd[0]);
		waitpid(pid, NULL, 0);
	}
}
