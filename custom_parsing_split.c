/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_parsing_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:04:16 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/10 12:46:39 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	block_count(char const *str, char c)
{
	int	count;
	int	i;
	int	in_q;

	i = 0;
	count = 0;
	in_q = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			in_q = 1 - in_q;
		if (str[i] == c && !in_q)
			count++;
		i++;
	}
	return (count + 1);
}

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
	int		block_len;
	int		i;
	char	c;
	int		in_q;

	i = 0;
	c = ' ';
	in_q = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			in_q = 1 - in_q;
		else if (str[i] == c && !in_q)
		{
			block_len = i - start;
			blocks[block_index] = malloc(sizeof(char) * (block_len + 1));
			if (blocks[block_index] == NULL)
			{
				printf("2nd mem alloc failed\n");
				exit(1);
			}
			ft_strncpy(blocks[block_index], str + start, block_len);
			blocks[block_index][block_len] = '\0';
			start = i + 1;
			block_index++;
		}
		i++;
	}
	ft_last_block(str, blocks, block_index, start);
	blocks[block_index + 1] = NULL;
	if (in_q)
	{
		printf("\033[1;31mError! Odd number of quotes\e[0m\n");
		exit(1);
	}
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
	int	quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			quotes = !quotes;
		if (quotes)
			return (1);
		i++;
	}
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
	ft_block(str, blocks, start, block_index);
	*wc = count + 1;
	return (blocks);
}

void	ft_free_parsing_split(char **blocks)
{
	int	i;

	i = 0;
	while (blocks[i] != NULL)
	{
		free(blocks[i]);
		i++;
	}
	free(blocks);
}
