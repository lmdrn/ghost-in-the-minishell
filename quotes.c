/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:10:01 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/11 13:50:38 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_single_quotes(char const *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			flag++;
		i++;
	}
	return (flag);
}

int	check_double_quotes(char const *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			flag++;
		i++;
	}
	return (flag);
}

int	check_quotes(char const *str, char c)
{
	int		s_flag;
	int		d_flag;

	s_flag = check_single_quotes(str);
	d_flag = check_double_quotes(str);
	if (s_flag % 2 != 0 || d_flag % 2 != 0)
	{
		printf("\033[0;31m Error: Odd number of quotes!\n");
		exit(1);
	}
	else
		return (word_count(str, c));
}
