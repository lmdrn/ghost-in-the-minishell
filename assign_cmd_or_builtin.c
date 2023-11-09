/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_cmd_or_builtin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:48:59 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/09 15:59:50 by lmedrano         ###   ########.fr       */
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

int	is_valid_char(char c)
{
	return (isalpha(c) || c == '\'' || c == '\"');
}

int	count_word_node(t_type *node)
{
	int		wc;
	int		i;
	int		inside_word;
	char	*str;

	if (node == NULL || node->text == NULL)
		return (0);
	str = node->text;
	wc = 0;
	i = 0;
	inside_word = 0;
	while (*str)
	{
		if (ft_isalpha(*str))
		{
			if (!inside_word)
			{
				wc++;
				inside_word = 1;
			}
		}
		else
			inside_word = 0;
		str++;
	}
	return (wc);
}

void	assign_quotes(t_type *node)
{
	int		len;
	char	first;
	char	last;

	first = node->text[0];
	len = ft_strlen(node->text);
	last = node->text[len - 1];
	printf("Node has %d words\n", count_word_node(node));
	if (first == '\"' && last == '\"')
	{
		if (count_word_node(node) == 1)
		{
			clean_cmd_type(node);
			if (is_builtin(node->text) == 0)
				node->type = builtin;
			else if (is_executable_command(node->text) == 0)
				node->type = cmd;
			else
				node->type = args;
		}
		else
		{
			printf("Error: command not found\n");
			exit(1);
		}
	}
	else if (first == '\'' && last == '\'')
	{
		if (count_word_node(node) == 1)
		{
			clean_cmd_type(node);
			if (is_builtin(node->text) == 0)
				node->type = builtin;
			else if (is_executable_command(node->text) == 0)
				node->type = cmd;
			else
				node->type = args;
		}
		else
		{
			printf("Error: command not found\n");
			exit(1);
		}
	}
	else
		node->type = args;
	printf("First letter is %c\n", first);
	printf("Last letter is %c\n", last);
	printf("%s type is: %d\n", node->text, node->type);
	printf("\n");
}
