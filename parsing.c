/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:04:16 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/11 18:43:55 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_count(char const *str)
{
	int		i;
	int		wc;
	int		quotes;
	char	c;

	i = 0;
	wc = 0;
	quotes = 0;
	while (str[i])
	{
		c = str[i];
		if (c == '\"' || c == '\'')
		{
			if (quotes == 0)
			{
				if (c == '\'')
					quotes = 1;
				else if (c == '\"')
					quotes = 2;
			}
			else
			{
				if (c == '\'' && quotes == 1)
					quotes = 0;
				else if (c == '\"' && quotes == 2)
					quotes = 0;
			}
		}
		if (quotes == 0)
		{
			if (c == ' ' || c == '\t' || c == '\r')
				wc ++;
		}
		i++;
	}
	if (quotes == 0)
		wc++;
	return (wc);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}
