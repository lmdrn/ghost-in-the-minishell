/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_parsing_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:04:16 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 22:52:13 by lmedrano         ###   ########.fr       */
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

int	ft_block(const char *str, char **blocks, int start, int block_index)
{
	t_bparam	bparams;

	ft_memset(&bparams, 0, sizeof(bparams));
	while (str[bparams.i])
	{
		if (str[bparams.i] == '\'')
			bparams.in_sq = !bparams.in_sq;
		else if (str[bparams.i] == '\"')
			bparams.in_dq = !bparams.in_dq;
		else if (str[bparams.i] == ' ' && !bparams.in_sq && !bparams.in_dq)
		{
			bparams.block_len = block_malloc(bparams.i,
					start, blocks, block_index);
			ft_strncpy(blocks[block_index], str + start, bparams.block_len);
			blocks[block_index][bparams.block_len] = '\0';
			start = bparams.i + 1;
			block_index++;
		}
		bparams.i++;
	}
	add_last_block(str, blocks, block_index, start);
	if (quote_check(bparams.in_dq, bparams.in_sq) == -1)
		return (-1);
	return (0);
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
	if (ft_block(str, blocks, start, block_index) == -1)
		return (NULL);
	*wc = count + 1;
	return (blocks);
}
