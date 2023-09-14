/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:04:16 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/14 09:00:52 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	block_count(char const *s, int i, int sep) */
/* { */
/* } */

/* void	ft_blocks(char *s, char c, char **block, int i) */
/* { */
/* } */

char	**ft_parsing_split(const char* str, char c, int* wc)
{
	int		count;
	int		i;
	int		start;
	int		block_index;
	int		block_len;
	int		last_block_len;
	char	**blocks;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	blocks = malloc(sizeof(char *) * (count + 1));
	if (blocks == NULL)
	{
		printf("1st mem alloc failed\n");
		exit(1);
	}
	start = 0;
	block_index = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			block_len = i - start;
			blocks[block_index] = malloc(sizeof(char) * (block_len + 1));
			if (blocks[block_index] == NULL)
			{
				printf("2nd mem alloc failed\n");
				exit(1);
			}
			strncpy(blocks[block_index], str + start, block_len);
			blocks[block_index][block_len] = '\0';
			start = i + 1;
			block_index++;
		}
		i++;
	}
	last_block_len = ft_strlen(str) - start;
	blocks[block_index] = malloc(sizeof(char) * (last_block_len + 1));
	if (blocks[block_index] == NULL)
	{
		printf("Last mem alloc failed\n");
		exit(1);
	}
	strncpy(blocks[block_index], str + start, last_block_len);
	blocks[block_index][last_block_len] = '\0';
	*wc = count + 1;
	return (blocks);
}
