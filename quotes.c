/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:08:35 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/06 14:18:35 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_word_node(t_type *node)
{
	int		wc;
	int		inside_word;
	char	*str;

	if (node == NULL || node->text == NULL)
		return (0);
	str = node->text;
	wc = 0;
	inside_word = 0;
	while (*str)
	{
		if (ft_isalpha(*str))
		{
			if (!inside_word)
			{
				wc++;
				inside_word = 1;
			}
		}
		else
			inside_word = 0;
		str++;
	}
	return (wc);
}

void	block_has_dbl_quotes(t_type *node, t_environment *env_cpy)
{
	char	*env_var;
	char	*env_value;
	char	*new_node;

	env_var = NULL;
	env_value = NULL;
	new_node = NULL;
	if (count_word_node(node) == 1)
	{
		clean_cmd_type(node);
		if (is_builtin(node->text) == 0)
			node->type = builtin;
		else if (is_executable_command(node->text) == 0)
			node->type = cmd;
		else
			node->type = args;
	}
	else
	{
		node->type = args;
		/* printf("NODE TYPE IS %d\n", node->type); */
		env_var = find_env_variable(node);
		if (env_var != NULL)
			env_value = retrieve_env_variable(env_var, env_cpy);
		new_node = replace_env_value(node, env_value);
		/* printf("New str with environment_value is %s\n", new_node); */
	}
}

void	block_has_s_quotes(t_type *node)
{
		if (count_word_node(node) == 1)
		{
			clean_cmd_type(node);
			if (is_builtin(node->text) == 0)
				node->type = builtin;
			else if (is_executable_command(node->text) == 0)
				node->type = cmd;
		}
		else
		{
			node->type = args;
		}
}

void	block_has_no_quotes(t_type *node, t_environment *env_cpy)
{
	char	*env_var;
	char	*env_value;
	char	*new_node;

	env_var = NULL;
	env_value = NULL;
	new_node = NULL;
	node->type = args;
	clean_cmd_type(node);
	env_var = find_env_variable(node);
	if (env_var != NULL)
		env_value = retrieve_env_variable(env_var, env_cpy);
	new_node = replace_env_value(node, env_value);
	/* printf("New str with environment_value is %s\n", new_node); */
}

void	assign_quotes(t_type *node, t_environment *env_cpy)
{
	int		len;
	char	first;
	char	last;
	char	*env_var;
	char	*env_value;

	env_var = NULL;
	env_value = NULL;
	first = node->text[0];
	len = ft_strlen(node->text);
	last = node->text[len - 1];
	/* printf("Node has %d words\n", count_word_node(node)); */
	if (first == '\"' && last == '\"')
		block_has_dbl_quotes(node, env_cpy);
	else if (first == '\'' && last == '\'')
		block_has_s_quotes(node);
	else
		block_has_no_quotes(node, env_cpy);
	//TESTS VARIABLES//
	/* printf("First letter is %c\n", first); */
	/* printf("Last letter is %c\n", last); */
	/* printf("%s type is: %d\n", node->text, node->type); */
	/* printf("Env var is %s\n", env_var); */
	/* printf("Env var value is %s\n", env_value); */
	/* printf("\n"); */
}

t_type	*clean_cmd_type(t_type *node)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char *) * ft_strlen(node->text) + 1);
	if (new_str == NULL)
		return (NULL);
	while (node->text[i] != '\0')
	{
		if (node->text[i] != '\'' && node->text[i] != '\"'
			&& !ft_isspace(node->text[i]))
		{
			new_str[j] = node->text[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	node->text = new_str;
	/* printf("without quotes is %s\n", new_str); */
	return (node);
}

char	*remove_xtra_spaces(char *input)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (ft_isspace(*input))
		input++;
	len = ft_strlen(input);
	while (len > 0 && ft_isspace(input[len - 1]))
		len--;
	i = 0;
	j = 0;
	while (i < len)
	{
		if (!ft_isspace(input[i]))
			input[j++] = input[i];
		else if (ft_isspace(input[i]) && !ft_isspace(input[i - 1]))
			input[j++] = input[i];
		i++;
	}
	input[j] = '\0';
	return (input);
}

int	between_quotes(char *str)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			double_quotes = !double_quotes;
		else if (str[i] == '\'')
			single_quotes = !single_quotes;
		if (single_quotes || double_quotes)
			return (1);
		i++;
	}
	return (0);
}
