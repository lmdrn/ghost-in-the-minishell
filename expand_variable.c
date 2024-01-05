/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:21:29 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 23:28:49 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// function that looks for a $ in the string
// and copies the word associated with the $

char	*find_env_variable(t_type *node, char *end_position, char *variable)
{
	char	*dollar;
	char	*current_pos;
	int		var_len;
	int		i;

	var_len = 0;
	dollar = ft_strnstr(node->text, "$", ft_strlen(node->text));
	current_pos = dollar;
	if (dollar != NULL)
	{
		end_position = get_end_pos(end_position, dollar);
		while (current_pos < end_position)
		{
			if (*current_pos != '$')
				var_len++;
			current_pos++;
		}
		variable = malloc_variable(var_len);
		i = 0;
		current_pos = dollar + 1;
		get_current_pos(current_pos, end_position, variable, i);
		variable[var_len] = '\0';
	}
	return (variable);
}

//function that takes the env variable found by find_env_variable()
//look in env if it exists
//go to the said variable and jump past the =
//then copies back the value of this variable
char	*retrieve_env_variable(char *env_var, t_environment *env)
{
	char	*value;

	if (env_var == NULL || env == NULL)
		return (NULL);
	while (env != NULL)
	{
		if (env->key != NULL && env->value != NULL)
		{
			if (ft_strcmp(env_var, env->key) == 0)
			{
				if (ft_strcmp(env_var, "SHLVL") == 0)
					value = decrement_and_convert_to_string(env->value);
				else
					value = ft_strdup(env->value);
				return (value);
			}
		}
		env = env->next;
	}
	return (NULL);
}

char	*create_new_value(int prefix, int suffix, t_type *node, int env_len)
{
	char	*new_text;

	new_text = malloc(prefix + env_len + suffix + 1);
	if (new_text == NULL)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	ft_strncpy(new_text, node->text, prefix);
	new_text[prefix] = '\0';
	return (new_text);
}

//function that takes expanded variable and for example:
//replaces $PATH by the current path from copied enn in current node
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
		new_text = create_new_value(prefix, suffix, node, env_len);
		if (env_value != NULL)
			ft_strcat(new_text, env_value);
	}
	else
		new_text = ft_strdup(node->text);
	free(env_value);
	env_value = NULL;
	return (new_text);
}
