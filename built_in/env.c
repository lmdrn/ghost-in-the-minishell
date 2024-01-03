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
	t_environment	*current;
	int count_arg;

	count_arg = count_args_cd(cmd_lst);
	if (count_arg >= 1)
	{
		printf("env: %s: No such file or directory\n", cmd_lst->args->arg);
		return;
	}
	current = env_copy;
	if (current != NULL)
	{
		while (current != NULL)
		{
			if (ft_strcmp(current->key, "SHLVL") == 0)
			{
				char *shlv = decrement_and_convert_to_string(current->value);
				printf("%s=%s", current->key, shlv);
			}
			else
				printf("%s=%s", current->key, current->value);

			printf("\n");
			current = current->next;
		}
	}
	else
		return ;
}
