/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:19:27 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/19 14:58:22 by lmedrano         ###   ########.fr       */
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
		{
			return (file = curr_arg->next->arg);
			printf("file is %s\n", file);
		}
		else if (curr_arg->type == 9)
		{
			return (file = curr_arg->next->arg);
			printf("file is %s\n", file);
		}
		else if (curr_arg->type == 10)
		{
			return (file = curr_arg->next->arg);
			printf("file is %s\n", file);
		}
		else if (curr_arg->type == 11)
		{
			return (file = curr_arg->next->arg);
			printf("file is %s\n", file);
		}
		curr_arg = curr_arg->next;
	}
	return (NULL);
}

char	*create_filename(t_commande *cmd)
{
	char	*filename;

	filename = find_filename(cmd);
	if (filename != NULL)
		return (filename);
	else
		return (NULL);
}
