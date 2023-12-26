/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:53:55 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/20 18:19:26 by lmedrano         ###   ########.fr       */
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
