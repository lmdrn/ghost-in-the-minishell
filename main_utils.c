/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:16:53 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/06 16:09:18 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_status(char *msg, int error)
{
	printf("Error: %s: command not found\n", msg);
	g_status = error;
}

// Function to extract a single word from a string enclosed in quotes
char	*one_word_with_quotes(const char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new_input;

	len = ft_strlen(str);
	i = 0;
	if (len < 2)
		return (NULL);
	while (str[i + 1] != '\0' && !ft_isspace(str[i + 1]))
		i++;
	if (str[i] != '\"' && str[i] != '\'')
		return (NULL);
	new_input = malloc(len - 2 + 1);
	j = 0;
	i = 1;
	while (i < len - 1)
		new_input[j++] = str[i++];
	new_input[j] = '\0';
	return (new_input);
}

int	quote_manager(char **input)
{
	if (ft_strlen(*input) == 2 && (*input[0] == '\'' || *input[0] == '\"'))
		error_status(*input, 127);
	if (*input[0] == '\"' || *input[0] == '\'')
		*input = one_word_with_quotes(*input);
	if (!*input)
		return (0);
	return (1);
}
