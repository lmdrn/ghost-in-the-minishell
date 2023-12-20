/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_parsing_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:04:16 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/20 22:37:26 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_last_block(const char *str, char **blocks, int bi, int start)
{
	int	last_block_len;

	last_block_len = ft_strlen(str) - start;
	blocks[bi] = malloc(sizeof(char) * (last_block_len + 1));
	if (blocks[bi] == NULL)
	{
		printf("Last mem alloc failed\n");
		exit(1);
	}
	ft_strncpy(blocks[bi], str + start, last_block_len);
	blocks[bi][last_block_len] = '\0';
}

void	ft_block(const char *str, char **blocks, int start, int block_index)
{
	int		i;
	int		block_len;
	int		in_sq;
	int		in_dq;

	i = 0;
	in_sq = 0;
	in_dq = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			in_sq = !in_sq;
		else if (str[i] == '\"')
			in_dq = !in_dq;
		else if (str[i] == ' ' && !in_sq && !in_dq)
		{
			block_len = block_malloc(i, start, blocks, block_index);
			ft_strncpy(blocks[block_index], str + start, block_len);
			blocks[block_index][block_len] = '\0';
			start = i + 1;
			block_index++;
		}
		i++;
	}
	add_last_block(str, blocks, block_index, start);
	quote_check(in_dq, in_sq);
}

char	**ft_parsing_split(const char *str, char c, int *wc)
{
	int		count;
	int		start;
	int		block_index;
	char	**blocks;

	count = block_count(str, c);
	blocks = malloc(sizeof(char *) * (count + 1));
	if (blocks == NULL)
	{
		printf("1st mem alloc failed\n");
		exit(1);
	}
	start = 0;
	block_index = 0;
	ft_block(str, blocks, start, block_index);
	*wc = count + 1;
	return (blocks);
}
