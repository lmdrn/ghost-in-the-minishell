/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:50:12 by angela            #+#    #+#             */
/*   Updated: 2024/01/05 23:39:51 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	go_home(t_environment *env_copy, char *home)
{
	update_pwd_oldpwd(env_copy, home, 3);
	if (chdir(home) != 0)
	{
		printf("cd: Home no access ");
		return (ERROR);
	}
	else
		return (SUCCESS);
}

char	*get_home(t_environment *env_copy)
{
	t_environment	*current;

	current = env_copy;
	if (env_copy == NULL)
		return (NULL);
	while (current != NULL)
	{
		if (ft_strcmp(current->key, "HOME") == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	count_args_cd(t_commande *cmd_lst)
{
	t_commande	*current;
	t_args		*args;
	int			i;

	current = cmd_lst;
	i = 0;
	if (current != NULL)
	{
		args = current->args;
		while (args != NULL)
		{
			i++;
			args = args->next;
		}
		return (i);
	}
	return (ERROR);
}

char	*go_back_directories(char *path)
{
	char	*last_slash;
	char	*result;
	int		len;

	last_slash = ft_strrchr(path, '/');
	if (last_slash != NULL)
	{
		len = last_slash - path;
		result = ft_substr(path, 0, len);
		return (result);
	}
	else
	{
		return (ft_strdup(path));
	}
}

int	is_one_arg(int nb_args, t_commande *cmd_lst)
{
	if (nb_args == 1)
	{
		if (ft_strcmp(cmd_lst->args->arg, "~") == 0)
			return (1);
		else if (ft_strcmp(cmd_lst->args->arg, "..") == 0)
			return (2);
		else
			return (3);
	}
	else
		return (ERROR);
}
