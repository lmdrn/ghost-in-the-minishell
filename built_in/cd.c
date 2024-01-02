/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:53:37 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/02 13:50:28 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_args_cd(t_commande *cmd_lst)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	if (cmd_lst != NULL)
	{
		i = count_args_cd(cmd_lst);
		if (i > 1)
		{
			g_status = 1;
			printf("\ntrop d'argumetns\n");
			return (ERROR);
		}
		if (i == 1)
			result = is_one_arg(i, cmd_lst);
		else
			result = (ticket_going_home(cmd_lst));
		return (result);
	}
	else
		return (ERROR);
}

int	ft_cd(t_environment *env_copy, char *path, int path_back)
{
	if (check_path(path) == ERROR)
	{
		printf("error path\n");
		return (ERROR);
	}
	if (path_back == 1)
		path = go_back_directories(path);
	if (check_is_in_env(env_copy, "PWD") == ERROR)
		add_node(&env_copy, "PWD", NULL);
	if (check_is_in_env(env_copy, "OLDPWD") == ERROR)
		add_node(&env_copy, "OLDPWD", NULL);
	update_pwd_oldpwd(env_copy, path);
	if (chdir(path) != 0)
	{
		printf("cd: Failed to change directory");
		g_status = ERROR;
		return (ERROR);
	}
	return (SUCCESS);
}

int	ticket_going_home(t_commande *cmd_lst)
{
	t_commande	*current;

	current = cmd_lst;
	if (current->args == NULL || (ft_strcmp(current->args->arg, "~")))
		return (1);
	else
		return (ERROR);
}

/*
  * == 0 ERROR
  * > 1 erreurs trop d'arguments. -> sortie
  * == 1 , aucun argument ou tild, retour a Home
  * == 2 , ".." on recule de 1 repertoire
  * == 3, bien un seul argument ->execute
  */

int	action_arg(int arg_check, char *home, \
t_environment *env_copy, t_commande *cmd_lst)
{
	int	path_back;

	path_back = 0;
	if (arg_check <= 0)
	{
		printf("cd: too many arguments\n");
		return (ERROR);
	}
	else if (arg_check == 1)
	{
		if (go_home(env_copy, home) == ERROR)
		{
			printf("\n can't go home\n");
			return (ERROR);
		}
		return (SUCCESS);
	}
	else if (arg_check == 2)
		path_back = 1;
	if (ft_cd(env_copy, cmd_lst->args->arg, path_back) == ERROR)
	{
		printf("path to file doesn't exist");
		return (ERROR);
	}
	return (SUCCESS);
}

int	builtin_cd(t_commande *cmd_lst, t_environment *env_copy)
{
	char	*home;
	int		arg_check;
	int		args_treatment;

	args_treatment = 0;
	arg_check = 0;
	home = NULL;
	home = get_home(env_copy);
	if (home == NULL)
	{
		printf("cd: Home not set\n");
		return (ERROR);
	}
	arg_check = check_args_cd(cmd_lst);
	args_treatment = action_arg(arg_check, home, env_copy, cmd_lst);
	return (args_treatment);
}