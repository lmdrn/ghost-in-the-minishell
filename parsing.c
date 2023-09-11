/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:04:16 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/11 14:18:27 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_count(char const *str, char c)
{
	int		i;
	int		wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			wc++;
		while (str[i] && str[i] != c)
		{
			if (str[i] == '\"')
				c = '\"';
			i++;
		}
	}
	return (wc);
}

void	ft_free(char **tab, int j)
{
	if (tab[j] == NULL)
	{
		while (j-- > 0)
			free(tab[j]);
		free(tab);
		tab = NULL;
		return ;
	}
}

void	ft_second_floor(char const *s, char c, char **tab, int i)
{
	int	j;
	int	k;
	int	count;

	j = 0;
	while (j < (check_quotes(s, c)))
	{
		count = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			count++;
			i++;
		}
		tab[j] = malloc(sizeof(char) * (count + 1));
		ft_free(tab, j);
		i -= count;
		k = 0;
		while (s[i] != c && s[i] != '\0')
			tab[j][k++] = s[i++];
	tab[j][k] = '\0';
	j++;
	}
	tab[j] = 0;
}

char	**ft_parsing_split(char const *s, char c)
{
	int		i;
	char	**tab;

	i = 0;
	tab = malloc(sizeof(char *) * (check_quotes(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	tab[check_quotes(s, c)] = 0;
	ft_second_floor(s, c, tab, i);
	return (tab);
}
