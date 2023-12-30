/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:19:27 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/30 16:28:53 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_special(t_args *curr_arg)
{
	char		*file;
	const char	*prefix;

	prefix = "<<";
	if (curr_arg->arg != NULL
		&& ft_strncmp(curr_arg->arg, prefix, ft_strlen(prefix)) == 0
		&& (ft_strlen(curr_arg->arg) > ft_strlen(prefix)))
	{
		return (file = curr_arg->arg + 2);
	}
	else
		return (file = curr_arg->next->arg);
}

char	*find_filename(t_commande *cmd)
{
	t_args		*curr_arg;
	char		*file;

	curr_arg = cmd->args;
	while (curr_arg != NULL)
	{
		if (curr_arg->type == 8)
		{
			file = curr_arg->next->arg;
			printf("file is %s\n", file);
			return (file = curr_arg->next->arg);
		}
		else if (curr_arg->type == 9)
			return (file = curr_arg->next->arg);
		else if (curr_arg->type == 10)
		{
			file = heredoc_special(curr_arg);
			return (file);
		}
		else if (curr_arg->type == 11)
			return (file = curr_arg->next->arg);
		curr_arg = curr_arg->next;
	}
	return (NULL);
}
