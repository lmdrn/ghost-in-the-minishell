/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_cmd_or_builtin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:48:59 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/07 18:52:45 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_exec_cmd(t_type *node)
{
	node->type = cmd;
	printf("%s type is: %d\n", node->text, node->type);
	printf("\n");
}

void	assign_builtin(t_type *node)
{
	node->type = builtin;
	printf("%s type is: %d\n", node->text, node->type);
	printf("\n");
}

void	assign_else(t_type *node)
{
	// here should check for single or double quotes
	int	dbl;

	dbl = 0;
	int	len;
	char	first;
	char	last;

	first = node->text[0];
	len = ft_strlen(node->text);
	last = node->text[len - 1];
	if (first == '\"' && last == '\"')
		node->type = dbl_q;	
	else if (first == '\'' && last == '\'')
		node->type = s_q;	
	else
		node->type = args;
	printf("First letter is %c\n", first);
	printf("Last letter is %c\n", last);
	printf("%s type is: %d\n", node->text, node->type);
	printf("\n");
}
