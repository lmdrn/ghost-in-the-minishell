/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:21:29 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/13 18:22:50 by lmedrano         ###   ########.fr       */
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
		while (*end_position != '\0' && !ft_isspace(*end_position)
			&& *end_position != '\"' && *end_position != '\'')
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

char	*replace_env_value(t_type *node, char *env_value)
{
	char	*start_pos;
	char	*new_text;
	int		env_len;
	int		prefix;
	int		suffix;

	start_pos = ft_strnstr(node->text, "$", ft_strlen(node->text));
	if (start_pos != NULL)
	{
		prefix = start_pos - node->text;
		suffix = ft_strlen(start_pos + 1);
		if (env_value != NULL)
			env_len = ft_strlen(env_value);
		else
			env_len = 0;
		new_text = malloc(prefix + suffix + env_len + 1);
		if (new_text == NULL)
		{
			printf("Error: malloc failed\n");
			exit(1);
		}
		ft_strncpy(new_text, node->text, prefix);
		new_text[prefix] = '\0';
		if (env_value != NULL)
			ft_strcat(new_text, env_value);
		ft_memmove(new_text + prefix + env_len, start_pos + 1, suffix);
	}
	else
		new_text = ft_strdup(node->text);
	return (new_text);
}
