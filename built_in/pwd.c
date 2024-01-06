/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:54:02 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/06 13:59:43 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(void)
{
	char	*actual_pwd;

	actual_pwd = getcwd(NULL, 0);
	if (actual_pwd != NULL)
	{
		printf("%s\n", actual_pwd);
		return (SUCCESS);
	}
	free(actual_pwd);
	actual_pwd = NULL;
	return (ERROR);
}

void	change_value(t_environment *env_copy, char *key,
			char *value)
{
	t_environment	*current;

	current = env_copy;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = NULL;
			current->value = ft_strdup(value);
			break ;
		}
		current = current->next;
	}
}

void	update_pwd_oldpwd(t_environment *env_copy,
			char *change_pwd, int old_new)
{
	if (old_new == 2)
		change_value(env_copy, "PWD", change_pwd);
	if (old_new == 1)
		change_value(env_copy, "OLDPWD", change_pwd);
}
