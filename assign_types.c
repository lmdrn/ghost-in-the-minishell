/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:36:03 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 22:18:52 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_pipe(t_type *node)
{
	node->type = is_pipe;
}

void	assign_dbl_ch_droit(t_type *node, t_type *lst, t_type *next_node)
{
	node->type = dbl_ch_d;
	next_node = lst;
	while (next_node != NULL)
	{
		if (next_node == node)
			break ;
		next_node = next_node->next;
	}
	if (next_node != NULL && next_node->next != NULL)
	{
		next_node = next_node->next;
		next_node->type = fileout;
	}
}

void	assign_dbl_ch_gauche(t_type *node, t_type *lst, t_type *next_node)
{
	node->type = dbl_ch_g;
	next_node = lst;
	while (next_node != NULL)
	{
		if (next_node == node)
			break ;
		next_node = next_node->next;
	}
	if (next_node != NULL && next_node->next != NULL)
	{
		next_node = next_node->next;
		next_node->type = delimiter;
	}
}

void	assign_ch_gauche(t_type *node, t_type *lst, t_type *next_node)
{
	node->type = ch_g;
	next_node = lst;
	while (next_node != NULL)
	{
		if (next_node == node)
			break ;
		next_node = next_node->next;
	}
	if (next_node != NULL && next_node->next != NULL)
	{
		next_node = next_node->next;
		next_node->type = filein;
	}
}

void	assign_ch_droit(t_type *node, t_type *lst, t_type *next_node)
{
	node->type = ch_d;
	next_node = lst;
	while (next_node != NULL)
	{
		if (next_node == node)
			break ;
		next_node = next_node->next;
	}
	if (next_node != NULL && next_node->next != NULL)
	{
		next_node = next_node->next;
		next_node->type = fileout;
	}
}
