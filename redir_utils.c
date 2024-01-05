/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:19:27 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 15:12:57 by lmedrano         ###   ########.fr       */
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

char	*find_filename(t_args *args)
{
	t_args		*curr_arg;
	char		*file;

	curr_arg = args;
	if (curr_arg->type == 8)
		file = curr_arg->next->arg;
	else if (curr_arg->type == 9)
		file = curr_arg->next->arg;
	else if (curr_arg->type == 10)
		file = heredoc_special(curr_arg);
	else if (curr_arg->type == 11)
		file = curr_arg->next->arg;
	return (file);
}
