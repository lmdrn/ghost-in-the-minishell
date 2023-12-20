/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:58:36 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/20 18:13:28 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_in_env(t_environment *env_copy, char *var)
{
	int	i;

	i = 0;
	if (env_copy != NULL)
	{
		while (env_copy[i].key != NULL)
		{
			if (strcmp(env_copy[i].key, var) == 0)
			{
				printf("key found \n");
				return (SUCCESS);
			}
			i++;
		}
		return (ERROR);
	}
	else
		return (ERROR);
}

void	print_value(t_environment *env_copy, char *key)
{
	int	i;

	i = 0;
	while (env_copy[i].key != NULL)
	{
		if (strcmp(env_copy[i].key, key) == 0)
			printf("Key: %s, Value: %s\n", env_copy[i].key, env_copy[i].value);
		i++;
	}
}

char	*get_env_value(t_environment *env_copy, char *env_key)
{
	t_environment	*current;

	current = env_copy;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, env_key) == 0)
			break ;
		current = current->next;
	}
	return (current->value);
}

int	check_path(char *path)
{
	if (access(path, F_OK) != -1)
		return (SUCCESS);
	else
	{
		printf("cd : no such file or directory :%s\n", path);
		return (ERROR);
	}
}

