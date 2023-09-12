/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:04:16 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/12 15:46:21 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	block_count(char const *s, int i, int sep)
{
	int		len;

	len = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		while (s[i] != sep && s[i])
		{
			len++;
			i++;
		}
		i++;
	}
	return (len);
}

void	ft_free(char **tab, int j)
{
	if (tab)
	{
		while (j >= 0)
		{
			free(tab[j]);
			j--;
		}
		free(tab);
	}
}

void	ft_blocks(char *s, char c, char **block, int i)
{
	int		len;
	int		wc;
	int		j;
	int		k;

	j = 0;
	(void)c;
	wc = word_count(s);
	printf("word count is : %d\n", wc);
	while (j < wc)
	{
		len = block_count(s, i, ' ');
		printf("word len is : %d\n", len);
		block[j] = malloc(sizeof(char) * (len + 1));
		if (block[j] == NULL)
		{
			ft_free(block, j - 1);
			free(block);
			return ;
		}
		k = 0;
		while (s[i])
			block[j][k++] = s[i++];
		block[j][k] = '\0';
		j++;
	}
	block[j] = 0;
}

char	**ft_parsing_split(char *input)
{
	int		i;
	int		len;
	char	**res;

	i = 0;
	len = word_count(input);
	res = malloc(sizeof(char *) * (len + 1));
	if (res == NULL)
		return (NULL);
	res[len] = 0;
	ft_blocks(input, ' ', res, i);
	return (res);
}
