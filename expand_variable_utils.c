/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:48:50 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/22 13:47:53 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_end_pos(char *end_position, char *dollar)
{
	end_position = dollar;
	while (*end_position != '\0' && !ft_isspace(*end_position)
		&& *end_position != '\"' && *end_position != '\'')
		end_position++;
	return (end_position);
}

char	*malloc_variable(int var_len)
{
	char	*variable;

	variable = malloc(sizeof(char *) * (var_len + 1));
	if (variable == NULL)
		return (NULL);
	return (variable);
}

void	get_current_pos(char *current_pos, char *end_position,
			char *variable, int i)
{
	while (current_pos < end_position)
	{
		if (*current_pos != '$')
			variable[i++] = *current_pos++;
	}
}
