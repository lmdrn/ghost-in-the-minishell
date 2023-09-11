/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:04:16 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/11 18:52:04 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_count(char const *s)
{
	int		i;
	int		wc;
	int		quotes;

	i = 0;
	wc = 0;
	quotes = 0;
	while (s[i])
	{
		if ((s[i] == '\"' || s[i] == '\'') && (quotes == 0 || quotes == s[i]))
		{
			if (quotes == 0)
				quotes = s[i];
			else
				quotes = 0;
		}
		if ((quotes == 0) && (s[i] == ' ' || s[i] == '\t' || s[i] == '\r'))
			wc++;
		i++;
	}
	if (quotes != 0)
		return (-1);
	else
		return (wc + 1);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}
