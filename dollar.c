/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:27:50 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 00:19:33 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to get the length of an integer when converted to a string
size_t	get_int_length(int value)
{
	size_t	len;
	int		tmp;

	tmp = value;
	len = 1;
	while (tmp / 10 != 0)
	{
		len++;
		tmp /= 10;
	}
	return (len);
}

// Function that determines the len of the str representation
// allocate mme for str
// and convert int into str

char	*int_to_string(int value)
{
	int		tmp;
	int		len;
	int		i;
	char	*res;

	tmp = value;
	len = 1;
	while (tmp / 10 != 0)
	{
		len++;
		tmp /= 10;
	}
	res = (char *)malloc(len + 1);
	if (res == NULL)
		ft_error("Error: mem alloc failed\n");
	tmp = value;
	res[len] = '\0';
	i = len - 1;
	while (i >= 0)
	{
		res[i] = '0' + (tmp % 10);
		tmp /= 10;
		i--;
	}
	return (res);
}

// Function to replace "$?" with the value of g_status
char	*replace_exit_status(char *text)
{
	char	*status_str;
	size_t	new_len;
	char	*new_text;

	status_str = int_to_string(g_status);
	new_len = strlen(status_str) + strlen(text + 2);
	new_text = (char *)malloc(new_len + 1);
	if (new_text == NULL)
		ft_error("Error: mem alloc failed\n");
	ft_strcpy(new_text, status_str);
	ft_strcat(new_text, text + 2);
	free(status_str);
	return (new_text);
}
