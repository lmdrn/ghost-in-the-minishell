/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:21:41 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/29 17:02:54 by lmedrano         ###   ########.fr       */
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

void	execute_pipeline(t_commande *cmd_lst, t_environment *env_copy, t_type *token)
{
	int	fd[2];
	int	pid;
    t_commande  *curr_cmd;
    t_args      *curr_arg;
    t_type      *curr_token;

	assign_fds(cmd_lst, fd);
    curr_cmd = cmd_lst;
    while (curr_cmd != NULL)
    {
		printf("cmd is %s\n", curr_cmd->cmd);
        curr_arg = curr_cmd->args;
		while (curr_arg != NULL)
		{
			printf("arg is is %s\n", curr_arg->arg);
            curr_token = token;
            while (curr_token != NULL)
            {
                if (curr_token->type == 9)
                {
			        printf("token is %d\n", curr_token->type);
                    break;
                }
                curr_token = curr_token->next;
            }
            curr_arg = curr_arg->next;
        }
		curr_cmd = curr_cmd->next;
    }
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

void    execute_pipeline(t_commande *cmd, t_environment *env_copy, int cmd_count)
{
    int ret;
    int tmp_in;
    int tmp_out;
    int i;
    int fds[2];
    char    *infile;
    char    *outfile;

    i = 0;
    tmp_in = dup(0);
    tmp_out = dup(1);
    if (is_input_redir(cmd) != NULL)
        infile = is_input_redir(cmd);
    if (infile != NULL)
    {
        cmd->fdin = open(infile, O_WRONLY | O_CREAT | O_TRUNC | 0666);
        if (cmd->fdin == -1)
            printf("Could not open infile\n");
    }
    else
        cmd->fdin = dup(tmp_in);
    while (i < cmd_count)
    {
        dup2(cmd->fdin, 0);
        close(cmd->fdin);
        if (i == (cmd_count - 1))
        {
            if (is_output_redir(cmd) != NULL)
                outfile = is_output_redir(cmd);
            if (outfile != NULL)
            {
                cmd->fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC | 0666);
                if (cmd->fdout == -1)
                    printf("Could not open outfile\n");
            }
            else
                cmd->fdout = dup(tmp_out);
        }
        else
        {
            pipe(fds);
            cmd->fdout = fds[1];
            cmd->fdin = fds[0];
        }
        dup2(cmd->fdout, 1);
        close(cmd->fdout);
        ret = fork();
        if (ret == 0)
        {
            execute_basic_cmd(cmd, env_copy);
            printf("Error executing cmd\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    dup2(tmp_in, 0);
    dup2(tmp_out, 1);
    close(tmp_in);
    close(tmp_out);
    waitpid(ret, &g_status, 0);
}

/* void	execute_pipeline(t_commande *cmd_lst, t_environment *env_copy, t_type *token) */
/* { */
/* 	int	fd[2]; */
/* 	int	pid; */
/*     t_commande  *curr_cmd; */
/*     t_args      *curr_arg; */
/*     t_type      *curr_token; */

/* 	assign_fds(cmd_lst, fd); */
/*     curr_cmd = cmd_lst; */
/*     while (curr_cmd != NULL) */
/*     { */
/* 		printf("cmd is %s\n", curr_cmd->cmd); */
/*         curr_arg = curr_cmd->args; */
/* 		while (curr_arg != NULL) */
/* 		{ */
/* 			printf("arg is is %s\n", curr_arg->arg); */
/*             curr_token = token; */
/*             while (curr_token != NULL) */
/*             { */
/*                 if (curr_token->type == 9) */
/*                 { */
/* 			        printf("token is %d\n", curr_token->type); */
/*                     break; */
/*                 } */
/*                 curr_token = curr_token->next; */
/*             } */
/*             curr_arg = curr_arg->next; */
/*         } */
/* 		curr_cmd = curr_cmd->next; */
/*     } */
/* 	while (cmd_lst != NULL) */
/* 	{ */
/* 		pid = fork(); */
/* 		if (pid == 0) */
/* 		{ */
/* 			if (cmd_lst->fdin != STDIN_FILENO) */
/* 			{ */
/* 				dup2(cmd_lst->fdin, STDIN_FILENO); */
/* 				close(cmd_lst->fdin); */
/* 			} */
/* 			if (cmd_lst->fdout != STDOUT_FILENO) */
/* 			{ */
/* 				dup2(cmd_lst->fdout, STDOUT_FILENO); */
/* 				close(cmd_lst->fdin); */
/* 			} */
/* 			//dup2(cmd_lst->fdin, STDIN_FILENO); */
/* 			//dup2(cmd_lst->fdout, STDOUT_FILENO); */
/* 			//close_fds(cmd_lst); */
/* 			execute_basic_cmd(cmd_lst, env_copy); */
/* 		} */
/* 		else */
/* 		{ */
/* 			if (cmd_lst->fdin != STDIN_FILENO) */
/* 				close(cmd_lst->fdin); */
/* 			if (cmd_lst->fdout != STDOUT_FILENO) */
/* 				close(cmd_lst->fdout); */
/* 		//	close_fds(cmd_lst); */
/* 			waitpid(pid, NULL, 0); */
/* 			//wait_for_children(cmd_lst); */
/* 		} */
/* 		cmd_lst = cmd_lst->next; */
/* 	} */
/* } */

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
