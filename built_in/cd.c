/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:53:37 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/06 14:59:47 by lmedrano         ###   ########.fr       */
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
		if (i == 1)
			result = is_one_arg(i, cmd_lst);
		else
			result = (ticket_going_home(cmd_lst));
		return (result);
	}
	else
		return (ERROR);
}

int	ft_cd_error(char *input, int error)
{
	if (!input)	
		printf("cd: Failed to change directory\n");
	else
		printf("cd: %s No such file or directory\n", input);
	g_status = ERROR;
	return (ERROR);
}

int	ft_cd(t_environment *env_copy, char *path)
{
	char	*old_dir;
	char	*new_dir;

	if (check_path(path) == ERROR)
		ft_cd_error(path, ERROR);
	old_dir = getcwd(NULL, 0);
	if (chdir(path) != 0)
		ft_cd_error(NULL, ERROR);
	new_dir = getcwd(NULL, 0);
	if (check_is_in_env(env_copy, "PWD") != ERROR)
		update_pwd_oldpwd(env_copy, new_dir, 2);
	if (check_is_in_env(env_copy, "OLDPWD") != ERROR)
		update_pwd_oldpwd(env_copy, old_dir, 1);
	free(old_dir);
	free(new_dir);
	old_dir = NULL;
	new_dir = NULL;
	g_status = SUCCESS;
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

int	action_arg(int arg_check, char *home, \
t_environment *env_copy, t_commande *cmd_lst)
{
	if (arg_check == 1)
	{
		if (ft_cd(env_copy, home) == ERROR)
			return (ERROR);
		return (SUCCESS);
	}
	if (ft_cd(env_copy, cmd_lst->args->arg) == ERROR)
		return (ERROR);
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
