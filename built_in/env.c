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

void	print_env_builtin(t_environment *env_copy)
{
	t_environment	*current;

	current = env_copy;
	if (current != NULL)
	{
		while (current != NULL)
		{
			printf("%s=%s", current->key, current->value);
			printf("\n");
			current = current->next;
		}
	}
	else
		return ;
}
