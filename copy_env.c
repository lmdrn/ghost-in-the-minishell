/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:49:26 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/14 14:15:57 by lmedrano         ###   ########.fr       */
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

void	populate_env_struct(char **envp,
		t_environment *new_env, int i)
{
	char			*delimiter;
	int				key;
	int				value;

	delimiter = ft_strchr(envp[i], '=');
	if (delimiter != NULL)
	{
		key = delimiter - envp[i];
		new_env[i].key = malloc(key + 1);
		ft_strncpy(new_env[i].key, envp[i], key);
		new_env[i].key[key] = '\0';
		value = ft_strlen(delimiter + 1);
		new_env[i].value = malloc(value + 1);
		ft_strcpy(new_env[i].value, delimiter + 1);
		new_env[i].value[value] = '\0';
	}
	else
	{
		new_env[i].key = NULL;
		new_env[i].value = NULL;
	}
}

t_environment	*copy_env(char **envp)
{
	t_environment	*new_env;
	int				count;
	int				i;

	if (!envp)
	{
		printf("env is empty\n");
		exit(EXIT_FAILURE);
	}
	count = env_count(envp);
	new_env = malloc(sizeof(t_environment) * (count + 1));
	if (new_env == NULL)
	{
		printf("Malloc failed\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < count)
	{
		populate_env_struct(envp, new_env, i);
		i++;
	}
	new_env[count].key = NULL;
	new_env[count].value = NULL;
	return (new_env);
}

void	free_env_struct(t_environment *env_struct)
{
	int	i;

	i = 0;
	while (env_struct[i].key != NULL)
	{
		free(env_struct[i].key);
		free(env_struct[i].value);
		i++;
	}
	free(env_struct);
}
