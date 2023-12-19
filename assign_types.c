/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:36:03 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/06 14:23:17 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_pipe(t_type *node)
{
	node->type = is_pipe;
	/* printf("%s type is: %d\n", node->text, node->type); */
	/* printf("\n"); */
}

void	assign_dbl_ch_droit(t_type *node, t_type *lst, t_type *next_node)
{
	node->type = dbl_ch_d;
	/* printf("%s type is: %d\n", node->text, node->type); */
	/* printf("\n"); */
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
		/* printf("%s type is: %d\n", next_node->text, next_node->type); */
		/* printf("\n"); */
	}
}

void	assign_dbl_ch_gauche(t_type *node, t_type *lst, t_type *next_node)
{
	node->type = dbl_ch_g;
	/* printf("%s type is: %d\n", node->text, node->type); */
	/* printf("\n"); */
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
		/* printf("%s type is: %d\n", next_node->text, next_node->type); */
		/* printf("\n"); */
	}
}

void	assign_ch_gauche(t_type *node, t_type *lst, t_type *next_node)
{
	node->type = ch_g;
	/* printf("type is: %d\n", node->type); */
	/* printf("\n"); */
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
		/* printf(" %s type is: %d\n", next_node->text, next_node->type); */
		/* printf("\n"); */
	}
}

void	assign_ch_droit(t_type *node, t_type *lst, t_type *next_node)
{
	node->type = ch_d;
	/* printf("%s type is: %d\n", node->text, node->type); */
	/* printf("\n"); */
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
		/* printf("%s type is: %d\n", next_node->text, next_node->type); */
	}
}
