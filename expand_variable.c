/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:21:29 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/13 12:19:55 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//use ft_strnstr()
//

char	*find_env_variable(t_type *node)
{
	char	*dollar;
	char	*end_position;
	char	*variable;
	char	*current_pos;
	int		var_len;
	int		i;

	var_len = 0;
	variable = NULL;
	dollar = ft_strnstr(node->text, "$", ft_strlen(node->text));
	current_pos = dollar;
	if (dollar != NULL)
	{
		end_position = dollar;
		while (*end_position != '\0' && !ft_isspace(*end_position))
			end_position++;
		while (current_pos < end_position)
		{
			var_len++;
			current_pos++;
		}
		variable = malloc(sizeof(char *) * (var_len + 1));
		if (variable == NULL)
			return (NULL);
		i = 0;
		while (dollar < end_position)
			variable[i++] = *dollar++;
		variable[var_len] = '\0';
	}
	return (variable);
}
