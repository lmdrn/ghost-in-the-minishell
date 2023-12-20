/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:46:07 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/20 22:59:11 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_word_node(t_type *node)
{
	int		wc;
	int		inside_word;
	char	*str;

	if (node == NULL || node->text == NULL)
		return (0);
	str = node->text;
	wc = 0;
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
	/* printf("without quotes is %s\n", new_str); */
	return (node);
}

char	*remove_xtra_spaces(char *input)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (ft_isspace(*input))
		input++;
	len = ft_strlen(input);
	while (len > 0 && ft_isspace(input[len - 1]))
		len--;
	i = 0;
	j = 0;
	while (i < len)
	{
		if (!ft_isspace(input[i]))
			input[j++] = input[i];
		else if (ft_isspace(input[i]) && !ft_isspace(input[i - 1]))
			input[j++] = input[i];
		i++;
	}
	input[j] = '\0';
	return (input);
}

int	between_quotes(char *str)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			double_quotes = !double_quotes;
		else if (str[i] == '\'')
			single_quotes = !single_quotes;
		if (single_quotes || double_quotes)
			return (1);
		i++;
	}
	return (0);
}
