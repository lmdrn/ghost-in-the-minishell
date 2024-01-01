/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:54:02 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/01 17:50:53 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_args_pwd(t_commande *cmd_lst)
{
	t_commande	*current;

	current = cmd_lst;
	if (cmd_lst != NULL && cmd_lst->next == NULL)
	{
		if (cmd_lst->args == NULL )
		{
			while (current->args != NULL && ((current->args->arg[0] == ' ')
					|| (current->args->arg[0] == '\t')))
			{
				current->args = current->args->next;
			}
			if (current->args == NULL)
				return (SUCCESS);
			else
				return (ERROR);
		}
		else
		{
			printf("Erreur :no options and no arguments.\n");
			return (ERROR);
		}
	}
	printf("Erreur : pas suivie d'autres commandes.\n");
	return (ERROR);
}

/* print direct depuis getcwd ou lire la liste..?*/

int	builtin_pwd( t_commande *cmd_lst)
{
	char	*actual_pwd;

	actual_pwd = getcwd(NULL, 0);
	if (actual_pwd != NULL)
	{
		if (check_args_pwd(cmd_lst) == SUCCESS)
		{
			printf("vous êtes ici : %s\n", actual_pwd);
			return (SUCCESS);
		}
		else
		{
			printf("error ici de pwd, trop de arg");
			return (ERROR);
		}
	}
	else
	{
		printf("error pas acces a pwd");
		return (ERROR);
	}
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

void	update_pwd_oldpwd(t_environment *env_copy, char *change_pwd)
{
	char			*current_pwd;
	char			*old_pwd;

	old_pwd = NULL;
	current_pwd = NULL;
	current_pwd = getcwd(NULL, 0);
	change_value(env_copy, "PWD", change_pwd, &old_pwd);
	change_value(env_copy, "OLDPWD", old_pwd, NULL);
	free(current_pwd);
}
