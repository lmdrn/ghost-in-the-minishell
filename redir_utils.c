/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:19:27 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/19 15:04:03 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_filename(t_commande *cmd)
{
	t_args		*curr_arg;
	char		*file;

	curr_arg = cmd->args;
	while (curr_arg != NULL)
	{
		if (curr_arg->type == 8)
			return (file = curr_arg->next->arg);
		else if (curr_arg->type == 9)
			return (file = curr_arg->next->arg);
		else if (curr_arg->type == 10)
			return (file = curr_arg->next->arg);
		else if (curr_arg->type == 11)
			return (file = curr_arg->next->arg);
		curr_arg = curr_arg->next;
	}
	return (NULL);
}
