/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:21:41 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/27 14:53:47 by lmedrano         ###   ########.fr       */
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
void	execute_pipeline(t_commande	*cmd_lst, t_environment *env_copy)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
	{
		printf("Error piping\n");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		printf("Error forking\n");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		//child process stuff to do 
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (execute_basic_cmd(cmd_lst, env_copy) == -1)
		{
			printf("Execution failure\n");
			exit(EXIT_FAILURE);
		}
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		printf("Error forking\n");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		//parent process stuff to do 
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (execute_basic_cmd(cmd_lst->next, env_copy) == -1)
		{
			printf("Execution failure\n");
			exit(EXIT_FAILURE);
		}
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
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

