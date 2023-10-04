/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:06:44 by lmedrano          #+#    #+#             */
/*   Updated: 2023/10/04 17:42:08 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_args(t_args *args)
{
    int count;

    count = 0;
    while (args != NULL)
    {
        count++;
        args = args->next;
    }
    return (count);
}

int execute_basic_cmd(t_commande *cmd)
{
    char    *path;
    char    *env;
    char    *full_path;
    char    **argv;
    int     path_len;
    int     i;
    t_args      *arg;
    t_commande  *tmp;

    path = getenv("PATH");
    if (path == NULL)
    {
        printf("Error : PATH not found\n");
        return (1);
    }
    env = path;
    tmp = cmd;
    full_path = NULL;
    argv = NULL;
    while (tmp != NULL)
    {
        path_len = ft_strlen(env) + 1 + ft_strlen(tmp->cmd);
        full_path = malloc(path_len + 1);
        if (full_path == NULL)
        {
            printf("Malloc error\n");
            return (1);
        }
        ft_strcpy(full_path, env);
        ft_strcat(full_path, "/");
        ft_strcat(full_path, tmp->cmd);
        argv = malloc(sizeof(char *) * (count_args(tmp->args) + 2));
        if (argv == NULL)
        {
            printf("Malloc error\n");
            free(full_path);
            return (1);
        }
        argv[0] = full_path;

        i = 1;
        arg = tmp->args;
        while (arg != NULL)
        {
            argv[i] = arg->arg;
            arg = arg->next;
            i++;
        }
        argv[i] = NULL;
        if (execve(full_path, argv, NULL) == -1)
        {
            printf("Execve\n");
            free(full_path);
            free(argv);
            return (1);
        }
        free(full_path);
        free(argv);
        tmp = tmp->next;
    }
    return (0);
}
