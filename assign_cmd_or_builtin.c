/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_cmd_or_builtin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:48:59 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/31 12:15:19 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_exec_cmd(t_type *node)
{
	node->type = cmd;
	/* printf("%s type is: %d\n", node->text, node->type); */
	/* printf("\n"); */
}

void	assign_abs_cmd(t_type *node)
{
	node->type = abs_cmd;
	/* printf("%s type is: %d\n", node->text, node->type); */
	/* printf("\n"); */
}

void	assign_builtin(t_type *node)
{
	node->type = builtin;
	/* printf("%s type is: %d\n", node->text, node->type); */
	/* printf("\n"); */
}

void	assign_args(t_type *node)
{
	node->type = args;
	/* printf("%s type is: %d\n", node->text, node->type); */
	/* printf("\n"); */
}
