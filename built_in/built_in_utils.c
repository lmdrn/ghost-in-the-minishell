/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:58:36 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/02 13:58:13 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_is_in_env(t_environment *env_copy, char *var)
{
	t_environment	*current;

	current = env_copy;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, var) == 0)
			return (SUCCESS);
		current = current->next;
	}
	return (ERROR);
}

void	print_value(t_environment *env_copy, char *key)
{
	t_environment	*current;

	current = env_copy;
	while (current->key != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			printf("Key: %s, Value: %s\n", current->key, current->value);
		current = current->next;
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
