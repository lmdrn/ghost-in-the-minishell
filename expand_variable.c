/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:21:29 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/21 14:50:55 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// function that looks for a $ in the string
// and copies the word associated with the $
char	*find_env_variable(t_type *node, char *end_position)
{
	char	*dollar;
	char	*variable;
	char	*current_pos;
	int		var_len;
	int		i;

	var_len = 0;
	dollar = ft_strnstr(node->text, "$", ft_strlen(node->text));
	current_pos = dollar;
	if (dollar != NULL)
	{
		end_position = get_env_position(dollar);
		get_current_pos(current_pos, var_len, end_position);
		variable = malloc_variable(var_len);
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
char	*retrieve_env_variable(char *env_var, t_environment *env)
{
	if (env_var == NULL || env == NULL)
		return (NULL);

	t_environment *cur = env;
	while (cur)
	{
		if (cur->key != NULL && cur->value != NULL)
			if (!ft_strcmp(env_var, cur->key))
				return (ft_strdup(cur->value));
		cur = cur->next;
	}
	return (NULL);
}

char	*init_new_text(int prefix, int suffix, int env_len, t_type *node)
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
		new_text = init_new_text(prefix, suffix, env_len, node);
		if (env_value != NULL)
			ft_strcat(new_text, env_value);
		ft_strcat(new_text, start_pos + 1);
	}
	else
		new_text = ft_strdup(node->text);
	return (new_text);
}
