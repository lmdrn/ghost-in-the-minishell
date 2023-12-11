/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:21:41 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/11 18:04:57 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_fds(t_commande *cmd, int *fd)
{
	cmd->fdin = 0;
	while (cmd->next != NULL)
	{
		pipe(fd);
		cmd->fdout = fd[1];
		cmd->next->fdin = fd[0];
		cmd = cmd->next;
	}
	cmd->fdout = STDOUT_FILENO;
}

void	close_fds(t_commande *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->fdin != STDIN_FILENO)
			close(cmd->fdin);
		if (cmd->fdout != STDOUT_FILENO)
			close(cmd->fdout);
		cmd = cmd->next;
	}
}

void	wait_for_children(t_commande *cmd)
{
	int	wstatus;

	while (cmd != NULL)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &wstatus, 0);
		}
		cmd = cmd->next;
	}
}

int	has_output(t_commande *cmd)
{
	while (cmd != NULL)
	{
		while (cmd->args != NULL)
		{
			if (cmd->args->type == 9)
			{
				return (cmd->args->type);
			}
			cmd->args = cmd->args->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

char	*find_output_file_name(t_args *curr_arg)
{
	char		*last_word;
	char		*output_redir;
	char		*file;

	last_word = NULL;
	output_redir = ft_strchr(curr_arg->arg, '>');
	printf("outputredir is %s\n", output_redir);
	if (output_redir != NULL && curr_arg->type == 9)
	{
		file = curr_arg->next->arg;
		printf("file is %s\n", file);
		while (*file == ' ')
			file++;
		if (*file != '\0' && ft_strchr(" \t\n\r", *file) == NULL)
			last_word = ft_strdup(file);
	}
	else
		return (NULL);
	return (last_word);
}

char	*assign_redir(t_commande *cmd, char *file, int input, int output)
{
	(void)input;
	printf("file is %s\n", file);
	printf("output is %d\n", output);
	if (output == 9)
	{
		cmd->fdout = creat(file, 0644);
		if (cmd->fdout == -1)
		{
			printf("Error creating file\n");
			exit(EXIT_FAILURE);
		}
		if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
		{
			perror("Dup out did not work\n");
			exit(EXIT_FAILURE);
		}
		close(cmd->fdout);
	}
	return (file);
}

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

void	redirect_output_to_file(int output_file)
{
	if (dup2(output_file, STDOUT_FILENO) == 1)
	{
		perror("Error Dup fd\n");
		exit(EXIT_FAILURE);
	}
}

void	execute_redir(t_commande *cmd, t_environment *env_copy)
{
	int		output_file;
	int		pipe_fd[2];
	pid_t	pid;
	char	buffer[256];
	size_t	bytes_read;
	char	*filename;

	filename = find_filename(cmd);
	output_file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_file == -1)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("Error creating pipe");
		close(output_file);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error forking");
		close(output_file);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
        // Child process
		close(pipe_fd[0]);  // Close read end of the pipe
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("Error dup fd\n");
			close(output_file);
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[1]);
		if (cmd->fdin != STDIN_FILENO)
		{
			dup2(cmd->fdin, STDIN_FILENO);
			close(cmd->fdin);
		}
        // Command and arguments for ls
		/* char *args[] = {"ls", NULL}; */
		/* execve("/bin/ls", args, NULL); */
		char	*full_path = find_executable_path(cmd->cmd, env_copy);
		if (!full_path)
			ft_error(cmd->cmd);
		char	**argv = build_arg(cmd, env_copy);
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
		/* (void)env_copy; */
		/* execute_basic_cmd(cmd, env_copy); */
		// If execve fails
		close(output_file);
		exit(EXIT_FAILURE);
	}
	else
	{
        // Parent process
		close(pipe_fd[1]);  // Close write end of the pipe
		bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
		while (bytes_read > 0)
		{
			write(output_file, buffer, bytes_read);
			bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
		}
		close(output_file);
		close(pipe_fd[0]);
		waitpid(pid, NULL, 0);  // Wait for the child process to complete
	}
}

void	execute_pipeline(t_commande *cmd_lst, t_environment *env_copy)
{
	int			fd[2];
	int			pid;

	assign_fds(cmd_lst, fd);
	while (cmd_lst != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmd_lst->fdin != STDIN_FILENO)
			{
				dup2(cmd_lst->fdin, STDIN_FILENO);
				close(cmd_lst->fdin);
			}
			if (cmd_lst->fdout != STDOUT_FILENO)
			{
				dup2(cmd_lst->fdout, STDOUT_FILENO);
				close(cmd_lst->fdin);
			}
			execute_basic_cmd(cmd_lst, env_copy);
		}
		else
		{
			if (cmd_lst->fdin != STDIN_FILENO)
				close(cmd_lst->fdin);
			if (cmd_lst->fdout != STDOUT_FILENO)
				close(cmd_lst->fdout);
			waitpid(pid, NULL, 0);
		}
		cmd_lst = cmd_lst->next;
	}
}

/* char	**env_list_to_array(t_environment *env_copy) */
/* { */
/* 	int 			count; */
/* 	t_environment	*tmp; */
/* 	char			**env_array; */
/* 	int				i; */
/* 	int				key_len; */
/* 	int				value_len; */

/* 	count = 0; */
/* 	tmp = env_copy; */
/* 	i = 0; */
/* 	while (tmp[i].key != NULL) */
/* 	{ */
/* 		count++; */
/* 		i++; */
/* 	} */
/* 	printf("count is %d\n", count); */
/* 	env_array = (char **)malloc(sizeof(char *) * (count + 1)); */
/* 	if (env_array == NULL) */
/* 	{ */
/* 		printf("Malloc failure\n"); */
/* 		exit(EXIT_FAILURE); */
/* 	} */
/* 	tmp = env_copy; */
/* 	i = 0; */
/* 	while (tmp[i].key != NULL) */
/* 	{ */
/* 		key_len = ft_strlen(tmp[i].key); */
/* 		/1* printf("len is %d\n", key_len); *1/ */
/* 		value_len = ft_strlen(tmp[i].value); */
/* 		env_array[i] = (char *)malloc(key_len + value_len + 2); */
/* 		if (env_array[i] == NULL) */
/* 		{ */
/* 			printf("Malloc failure\n"); */
/* 			exit(EXIT_FAILURE); */
/* 		} */
/* 		ft_strcpy(env_array[i], tmp[i].key); */
/* 		env_array[i][key_len] = '='; */
/* 		ft_strcpy(env_array[i] + key_len + 1, tmp[i].value); */
/* 		i++; */
/* 	} */
/* 	env_array[count] = NULL; */
/* 	/1* i = 0; *1/ */
/* 	/1* while (env_array[i] != NULL) *1/ */
/* 	/1* { *1/ */
/* 	/1* 	printf("env var is %s\n", env_array[i]); *1/ */
/* 	/1* 	i++; *1/ */
/* 	/1* } *1/ */
/* 	return (env_array); */
/* } */
