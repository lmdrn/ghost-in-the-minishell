/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:21:41 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/27 19:51:43 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TEST - 1 */
/* void	execute_pipeline(t_commande *cmd_lst, t_environment *env_copy) */
/* { */
/* 	int	fd[2]; */
/* 	int	pid; */
/* 	char	*ls[] = {"ls", NULL}; */
/* 	char	*grep[] = {"grep", "signal", NULL}; */
/* 	(void)cmd_lst; */
/* 	(void)env_copy; */

/* 	pipe(fd); */
/* 	pid = fork(); */
/* 	if (pid == 0) //child process */
/* 	{ */
/* 		dup2(fd[0], STDIN_FILENO); */
/* 		close(fd[1]); */
/* 		execvp("grep", grep); */
/* 		close(fd[0]); */
/* 	} */
/* 	else //parent process */
/* 	{ */
/* 		dup2(fd[1], STDOUT_FILENO); */
/* 		close(fd[0]); */
/* 		execvp("ls", ls); */
/* 	} */
/* } */

/* TEST 2 */
/* void	execute_pipeline(t_commande	*cmd_lst, t_environment *env_copy) */
/* { */
/* 	int	fd[2]; */
/* 	int	pid1; */
/* 	int	pid2; */

/* 	if (pipe(fd) == -1) */
/* 	{ */
/* 		printf("Error piping\n"); */
/* 		exit(EXIT_FAILURE); */
/* 	} */
/* 	pid1 = fork(); */
/* 	if (pid1 == -1) */
/* 	{ */
/* 		printf("Error forking\n"); */
/* 		exit(EXIT_FAILURE); */
/* 	} */
/* 	if (pid1 == 0) */
/* 	{ */
/* 		//child process stuff to do */ 
/* 		dup2(fd[1], STDOUT_FILENO); */
/* 		close(fd[0]); */
/* 		close(fd[1]); */
/* 		if (execute_basic_cmd(cmd_lst, env_copy) == -1) */
/* 		{ */
/* 			printf("Execution failure\n"); */
/* 			exit(EXIT_FAILURE); */
/* 		} */
/* 	} */
/* 	pid2 = fork(); */
/* 	if (pid2 == -1) */
/* 	{ */
/* 		printf("Error forking\n"); */
/* 		exit(EXIT_FAILURE); */
/* 	} */
/* 	if (pid2 == 0) */
/* 	{ */
/* 		//second child process stuff to do */ 
/* 		dup2(fd[0], STDIN_FILENO); */
/* 		close(fd[0]); */
/* 		close(fd[1]); */
/* 		if (execute_basic_cmd(cmd_lst->next, env_copy) == -1) */
/* 		{ */
/* 			printf("Execution failure\n"); */
/* 			exit(EXIT_FAILURE); */
/* 		} */
/* 	} */
/* 	close(fd[0]); */
/* 	close(fd[1]); */
/* 	waitpid(pid1, NULL, 0); */
/* 	waitpid(pid2, NULL, 0); */
/* } */

/* TEST 3 */
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

void	execute_pipeline(t_commande *cmd_lst, t_environment *env_copy)
{
	int	fd[2];

	assign_fds(cmd_lst, fd);
	while (cmd_lst != NULL)
	{
		int pid = fork();
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
			//dup2(cmd_lst->fdin, STDIN_FILENO);
			//dup2(cmd_lst->fdout, STDOUT_FILENO);
			//close_fds(cmd_lst);
			execute_basic_cmd(cmd_lst, env_copy);
		}
		else
		{
			if (cmd_lst->fdin != STDIN_FILENO)
				close(cmd_lst->fdin);
			if (cmd_lst->fdout != STDOUT_FILENO)
				close(cmd_lst->fdout);
		//	close_fds(cmd_lst);
			waitpid(pid, NULL, 0);
			//wait_for_children(cmd_lst);
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
