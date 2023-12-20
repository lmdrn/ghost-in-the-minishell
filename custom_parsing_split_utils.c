/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_parsing_split_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:34:50 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/20 22:35:26 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	block_malloc(int i, int start, char **blocks, int block_index)
{
	int	block_len;

	block_len = i - start;
	blocks[block_index] = malloc(sizeof(char) * (block_len + 1));
	if (blocks[block_index] == NULL)
	{
		printf("2nd mem alloc failed\n");
		return (-1);
		exit(1);
	}
	return (block_len);
}

void	add_last_block(const char *str, char **blocks,
		int block_index, int start)
{
	ft_last_block(str, blocks, block_index, start);
	blocks[block_index + 1] = NULL;
}

void	quote_check(int in_dq, int in_sq)
{
	if (in_dq % 2 == 0 && in_sq % 2 != 0)
		printf("\033[1;31mUnclosed single quote in a double quote\e[0m\n");
	else if (in_dq % 2 != 0 && in_sq % 2 == 0)
		printf("\033[1;31mUnclosed double quote in a single quote\e[0m\n");
	else if (in_sq % 2 != 0 && in_dq == 0)
	{
		printf("\033[1;31mError! Odd number of single quotes\e[0m\n");
		exit(1);
	}
	else if (in_dq % 2 != 0 && in_sq == 0)
	{
		printf("\033[1;31mError! Odd number of double quotes\e[0m\n");
		exit(1);
	}
}

