/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:06:44 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/21 11:17:35 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct {
	char	*path;
	char	*token_start;
	char	*token_end;
	char	*cmd_path;
	char	*segment;
} exec_path_info;

char *concat_path_cmd(char *path, char *cmd) {
    int path_len = strlen(path), cmd_len = strlen(cmd);
    char *res = malloc(path_len + cmd_len + 2);
    return (res == NULL) ? (printf("Malloc failed\n"), exit(EXIT_FAILURE), NULL) : (strcpy(res, path), strcat(res, "/"), strcat(res, cmd), res);
}

char *concat_cmd(char *cmd_path, char *path, char *token_start, char *command) {
    cmd_path = concat_path_cmd(token_start, command);
    return (cmd_path != NULL && access(cmd_path, F_OK) == 0) ? (free(path), cmd_path) : (free(cmd_path), NULL);
}

char *segment_malloc_copy(char *segment, char *token_start, char *token_end) {
    int segment_len = token_end - token_start;
    segment = malloc(segment_len + 1);
    return (segment == NULL) ? (printf("Malloc failed\n"), exit(EXIT_FAILURE), NULL) : (strncpy(segment, token_start, segment_len), segment[segment_len] = '\0', segment);
}

char *find_executable_path(char *command, t_environment *env_copy) {
    int i = 0;
    exec_path_info epi = {0};

    while (env_copy[i].key != NULL && strcmp(env_copy[i].key, "PATH") != 0) i++;

    epi.path = ft_strdup(env_copy[i].value);
    epi.token_start = epi.path;

    while (epi.token_start != NULL) {
        epi.token_end = ft_strchr(epi.token_start, ':');

        if (epi.token_end != NULL) {
            epi.segment = segment_malloc_copy(epi.segment, epi.token_start, epi.token_end);
            epi.cmd_path = concat_path_cmd(epi.segment, command);
            free(epi.segment);

            if (access(epi.cmd_path, F_OK) == 0) return free(epi.path), epi.cmd_path;

            free(epi.cmd_path);
            epi.token_start = epi.token_end + 1;
        } else epi.cmd_path = concat_cmd(epi.cmd_path, epi.path, epi.token_start, command);
    }

    return free(epi.path), NULL;
}


/* char	*find_executable_path(char *command, t_environment *env_copy) */
/* { */
/* 	char	*path; */
/* 	char	*token_start; */
/* 	char	*token_end; */
/* 	char	*cmd_path; */
/* 	char	*segment; */
/* 	int		i; */

/* 	i = 0; */
/* 	cmd_path = NULL; */
/* 	while (env_copy[i].key != NULL) */
/* 	{ */
/* 		if (strcmp(env_copy[i].key, "PATH") == 0) */
/* 		{ */
/* 			path = ft_strdup(env_copy[i].value); */
/* 			token_start = path; */
/* 			token_end = ft_strchr(path, ':'); */
/* 			while (token_start != NULL) */
/* 			{ */
/* 				if (token_end != NULL) */
/* 				{ */
/* 					segment = segment_malloc_copy(segment, token_start, token_end); */
/* 					cmd_path = concat_path_cmd(segment, command); */
/* 					free(segment); */
/* 					if (access(cmd_path, F_OK) == 0) */
/* 					{ */
/* 						free(path); */
/* 						return (cmd_path); */
/* 					} */
/* 					free(cmd_path); */
/* 					token_start = token_end + 1; */
/* 					token_end = ft_strchr(token_start, ':'); */
/* 				} */
/* 				else */
/* 					cmd_path = concat_cmd(cmd_path, path, token_start, command); */
/* 			} */
/* 			free(path); */
/* 			break ; */
/* 		} */
/* 		i++; */
/* 	} */
/* 	return (NULL); */
/* } */

int	count_args(t_args *args)
{
	int	count;

	count = 0;
	while (args != NULL)
	{
		count++;
		args = args->next;
	}
	return (count);
}

void	create_args(char **argv, t_commande *cmd)
{
	int		i;
	t_args	*arg;

	i = 1;
	arg = cmd->args;
	while (arg)
	{
		if (arg->type == 8 || arg->type == 9
			|| arg->type == 10 || arg->type == 11)
			break ;
		else
		{
			/* printf("Arg: %s\n", arg->arg); */
			argv[i] = ft_strdup(arg->arg);
			if (!argv[i])
			{
				perror("malloc error\n");
				free_argv(argv);
				return ;
			}
			i++;
		}
		arg = arg->next;
	}
	argv[i] = NULL;
}

char	**build_arg(t_commande *cmd, t_environment *env_copy)
{
	int		argc;
	char	**argv;

	argc = count_args(cmd->args);
	argv = malloc(sizeof(char *) * (argc + 2));
	if (!argv)
		return (NULL);
	argv[0] = find_executable_path(cmd->cmd, env_copy);
	/* printf("argv0 is %s\n", argv[0]); */
	if (!argv[0])
		return (NULL);
	create_args(argv, cmd);
	return (argv);
}

int	execute_basic_cmd(t_commande *cmd, t_environment *env_copy)
{
	char		*full_path;
	char		**argv;

	full_path = find_executable_path(cmd->cmd, env_copy);
	if (!full_path)
		ft_error(cmd->cmd);
	argv = build_arg(cmd, env_copy);
	if (!argv)
	{
		printf("Malloc error\n");
		return (1);
	}
	if (execve(full_path, argv, NULL) == -1)
		ft_error(cmd->cmd);
	free_argv(argv);
	free(full_path);
	return (0);
}
