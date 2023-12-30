/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:51:57 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/30 11:41:02 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_args_or_redir(t_type *current)
{
	if (current->type == args || current->type == ch_d
		|| current->type == ch_g || current->type == dbl_ch_g
		|| current->type == dbl_ch_d)
		return (0);
	return (1);
}

int	is_redir(t_type *current)
{
	if (current->type == ch_d
		|| current->type == ch_g || current->type == dbl_ch_g
		|| current->type == dbl_ch_d)
		return (0);
	return (1);
}
