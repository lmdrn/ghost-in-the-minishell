/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:49:26 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/02 16:42:49 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_count(char **envp)
{
	int		env_count;

	env_count = 0;
	while (envp[env_count] != NULL)
		env_count++;
	return (env_count);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	dup_env(int count, char **new_env, char **envp)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
}

char	**copy_env(char **envp)
{
	char	**new_env;
	int		count;

	if (!envp)
	{
		printf("env is empty\n");
		exit(EXIT_FAILURE);
	}
	count = env_count(envp);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (new_env == NULL)
	{
		printf("Malloc failed\n");
		exit(EXIT_FAILURE);
	}
	dup_env(count, new_env, envp);
	if (count < (count + 1))
		new_env[count] = NULL;
	else
		printf("Error: Count exceeds allocated memory\n");
	return (new_env);
}
