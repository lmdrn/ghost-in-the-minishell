/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:53:55 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/01 17:50:35 by angela           ###   ########.fr       */
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
			if (current->next != NULL)
				printf("\n");
			current = current->next;
		}
	}
	else
		return ;
}
