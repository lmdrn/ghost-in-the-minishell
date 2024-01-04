/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:53:55 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/02 13:48:54 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env_builtin(t_environment *env_copy, t_commande *cmd_lst)
{
	int	count_arg;

	count_arg = count_args_cd(cmd_lst);
	if (count_arg >= 1)
	{
		printf("env: %s: No such file or directory\n", cmd_lst->args->arg);
		return ;
	}
	if (env_copy != NULL)
		print_environment_variables(env_copy);
}

void	print_environment_variables(t_environment *env_copy)
{
	t_environment	*current;
	char			*shlvl_str;

	current = env_copy;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, "SHLVL") == 0)
		{
			shlvl_str = decrement_and_convert_to_string(current->value);
			printf("%s=%s", current->key, shlvl_str);
			free(shlvl_str);
		}
		else
			printf("%s=%s", current->key, current->value);
		printf("\n");
		current = current->next;
	}
}
