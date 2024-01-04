/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:50:44 by angela            #+#    #+#             */
/*   Updated: 2024/01/04 11:52:55 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	no_arg_so_print_env_exports(t_environment **env_copy, int nb_args)
{
	t_environment	*copy;

	if (nb_args == 0)
	{
		copy = copy_env_list(*env_copy);
		bubble_sort_env(&copy);
		print_sorted_env(copy);
	}
}

int	if_exist_in_env(char *key, t_environment *env_origin)
{
	t_environment	*current;

	current = env_origin;
	if (key == NULL)
		return (ERROR);
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (SUCCESS);
		current = current->next;
	}
	return (-1);
}

int	fill_env(t_commande *cmd_lst, t_environment **env_copy, int nb_args)
{
	t_commande	*current;
	char		*key;
	char		*value;
	int			exist;

	current = cmd_lst;
	if (nb_args == 0)
	{
		return (SUCCESS);
	}
	while (nb_args != 0)
	{
		value = get_value_export(current->args->arg);
		key = get_key_export(current->args->arg);
		exist = if_exist_in_env(key, *env_copy);
		if (exist == -1)
			add_node(env_copy, key, value);
		else
			remplace_old_value(value, key, *env_copy);
		nb_args--;
		if (nb_args != 0)
			cmd_lst = cmd_lst->next;
	}
	return (ERROR);
}

int	export_main(t_commande *cmd_lst, t_environment **env_copy)
{
	int	nb_args;

	nb_args = count_args_export(cmd_lst);
	if (nb_args == -1)
	{
		printf("erreur nb_args\n");
		return (ERROR);
	}
	if (ft_strncmp(cmd_lst->cmd, "export=", 7) == 0)
		return (ERROR);
	no_arg_so_print_env_exports(env_copy, nb_args);
	fill_env(cmd_lst, env_copy, nb_args);
	return (SUCCESS);
}
