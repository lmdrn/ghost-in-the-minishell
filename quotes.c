/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:08:35 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/10 12:56:18 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_valid_char(char c)
{
	return (ft_isalpha(c) || c == '\'' || c == '\"');
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
		// ici error dans le cas ou j'ai 2 mots et args et non une cmd!!
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

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	return (0);
}

t_type	*clean_cmd_type(t_type *node)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char *) * ft_strlen(node->text) + 1);
	if (new_str == NULL)
		return (NULL);
	while (node->text[i] != '\0')
	{
		if (node->text[i] != '\'' && node->text[i] != '\"'
			&& !ft_isspace(node->text[i]))
		{
			new_str[j] = node->text[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	node->text = new_str;
	printf("without quotes is %s\n", new_str);
	return (node);
}
