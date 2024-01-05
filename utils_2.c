/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:53:48 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/04 22:05:45 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_char(char c)
{
	return (ft_isalpha(c) || c == '\'' || c == '\"');
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while ((*s1 == *s2) && *s1 != '\0')
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
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

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	dest_len;
	size_t	i;

	i = 0;
	dest_len = ft_strlen(dest);
	while (i < n && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}
