/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:21:41 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/06 18:14:49 by lmedrano         ###   ########.fr       */
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
	/* if (input == 8) */
	/* { */
	/* 	file = find_input_file_name(cmd); */
	/* 	printf("input file name is : %s\n", file); */
	/* 	cmd->fdin = open(file, O_RDONLY); */
	/* 	if (cmd->fdin == -1) */
	/* 	{ */
	/* 		printf("Error opening file \n"); */
	/* 		exit(EXIT_FAILURE); */
	/* 	} */
	/* 	dup2(cmd->fdin, STDIN_FILENO); */
	/* 	close(cmd->fdin); */
	/* } */
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
			printf("Dup out did not work\n");
			exit(EXIT_FAILURE);
		}
		close(cmd->fdout);
	}
	return (file);
}

//try and transform cmd into char * and args into array ?
void	execute_redir(t_commande *cmd, t_environment *env_copy)
{
	int			pid;
	t_args		*curr_arg;
	int			input;
	int			output;
	char		*file;

	input = 0;
	output = has_output(cmd);
	while (cmd != NULL)
	{
		curr_arg = cmd->args;
		while (curr_arg != NULL)
		{
			if (curr_arg->type == 9)
			{
				file = curr_arg->next->arg;
				printf("file is %s\n", file);
			}
			curr_arg = curr_arg->next;
		}
		cmd = cmd->next;
	}
	while (cmd != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (file != NULL)
				assign_redir(cmd, file, input, output);
			if (execute_basic_cmd(cmd, env_copy) == -1)
				printf("Error executing %s\n", cmd->cmd);
		}
		else
		{
			if (cmd->fdin != STDIN_FILENO)
				close(cmd->fdin);
			if (cmd->fdout != STDOUT_FILENO)
				close(cmd->fdout);
			waitpid(pid, NULL, 0);
		}
		cmd = cmd->next;
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
