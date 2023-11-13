/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:21:29 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/13 13:14:40 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// function that looks for a $ in the string
// and copies the word associated with the $
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
			if (*current_pos != '$')
				var_len++;
			current_pos++;
		}
		variable = malloc(sizeof(char *) * (var_len + 1));
		if (variable == NULL)
			return (NULL);
		i = 0;
		current_pos = dollar + 1;
		while (current_pos < end_position)
		{
			if (*current_pos != '$')
				variable[i++] = *current_pos++;
		}
		variable[var_len] = '\0';
	}
	return (variable);
}

//function that takes the env variable found by find_env_variable()
//look in env if it exists
//go to the said variable and jump past the =
//then copies back the value of this variable
char	*retrieve_env_variable(char *env_var)
{
	char	*value;
	char	*res;

	value = getenv(env_var);
	if (value != NULL)
	{
		res = malloc(sizeof(char *) * (ft_strlen(value) + 1));
		if (res == NULL)
			return (NULL);
		ft_strcpy(res, value);
		return (res);
	}
	else
	{
		return (NULL);
	}
}
