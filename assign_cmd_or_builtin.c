/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_cmd_or_builtin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:48:59 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/06 14:24:57 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_exec_cmd(t_type *node)
{
	node->type = cmd;
	/* printf("%s type is: %d\n", node->text, node->type); */
	/* printf("\n"); */
}

void	assign_builtin(t_type *node)
{
	node->type = builtin;
	/* printf("%s type is: %d\n", node->text, node->type); */
	/* printf("\n"); */
}
