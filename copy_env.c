/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:06:47 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/26 14:36:30 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int copy_env(char **envp)
{
    int     env_count;
    int     i;
    char    **new_env;

    env_count = 0;
    i = 0;
    while(envp[env_count] != NULL)
        env_count++;
    new_env = malloc(sizeof(char *) * (env_count + 1));
    if (new_env == NULL)
    {
        printf("Env malloc failed\n");
        return (1);
    }
    while (i < env_count)
    {
        new_env[i] = ft_strdup(envp[i]);
        if (new_env[i] == NULL)
        {
            printf("Error duplicating envp\n");
            return (1);
        }
    }
    new_env[env_count] = NULL;
    i = 0;
    while (i < env_count)
        free(new_env[i]);
    free(new_env);
    return (0);
}


