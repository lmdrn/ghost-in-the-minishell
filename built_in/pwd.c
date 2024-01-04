/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:54:02 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/02 13:47:44 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd( void)
{
	char	*actual_pwd;

	actual_pwd = getcwd(NULL, 0);
	if (actual_pwd != NULL)
	{
		printf("%s\n", actual_pwd);
		return (SUCCESS);
	}
	return (ERROR);
}

void	change_value(t_environment *env_copy, char *cmd, \
char *value, char **old_value_ptr)
{
	t_environment	*current;

	current = env_copy;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, cmd) == 0)
		{
			if (old_value_ptr != NULL)
				*old_value_ptr = ft_strdup(current->value);
			free(current->value);
			current->value = ft_strdup(value);
			break ;
		}
		current = current->next;
	}
}

void	update_pwd_oldpwd(t_environment *env_copy, \
char *change_pwd, int old_new)
{
	char			*current_pwd;
	char			*old_pwd;

	old_pwd = NULL;
	current_pwd = NULL;
	current_pwd = getcwd(NULL, 0);
	old_pwd = current_pwd;
	if (old_new == 2 || old_new == 3)
		change_value(env_copy, "PWD", change_pwd, &old_pwd);
	if (old_new == 1 || old_new == 3)
		change_value(env_copy, "OLDPWD", old_pwd, NULL);
	free(current_pwd);
}
