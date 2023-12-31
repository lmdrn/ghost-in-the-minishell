/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:53:48 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/06 21:27:41 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	erase_node(char *key, t_environment **env_copy)
{
	t_environment	*tmp;
	t_environment	*prev;

	tmp = *env_copy;
	prev = NULL;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev == NULL)
				*env_copy = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	check_valid_key(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
		{
			i++;
			return (ERROR);
		}
		if (!ft_isalpha(arg[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	sanity_check(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
		{
			i++;
			break ;
		}
		if (!ft_isalpha(arg[i]))
			return (ERROR);
			i++;
	}
	while (arg[i] != '\0')
	{
		if (!ft_isprint(arg[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	count_args_unset(t_commande *cmd_lst)
{
	int		count;
	t_args	*current;

	count = 0;
	current = cmd_lst->args;
	while (current != NULL)
	{
		count++;
		if (sanity_check(current->arg) == ERROR)
			return (-1);
		current = current->next;
	}
	return (count);
}

int	built_unset(t_environment **env_copy, t_commande *cmd_lst)
{
	int		nb_args;
	t_args	*args;

	args = cmd_lst->args;
	nb_args = count_args_unset(cmd_lst);
	if (nb_args == -1 || nb_args == 0)
		return (ERROR);
	while (args && nb_args > 0)
	{
		if (!check_valid_key(args->arg))
		{
			printf("unset: `%s': not a valid identifier\n", args->arg);
			return (ERROR);
		}
		if (if_exist_in_env(args->arg, *env_copy) == SUCCESS)
			erase_node(args->arg, env_copy);
		nb_args--;
		args = args->next;
	}
	return (SUCCESS);
}
