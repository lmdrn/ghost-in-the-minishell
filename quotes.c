/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:08:35 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/22 18:36:06 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_builtin_or_cmd(t_type *node)
{
	clean_cmd_type(node);
	//printf("Im here\n");
	if (is_builtin(node->text) == 0)
		node->type = builtin;
	else if (is_executable_command(node->text) == 0)
		node->type = cmd;
	else
		node->type = args;
}

void	block_has_dbl_quotes(t_type *node, t_environment *env_cpy)
{
	char	*env_var;
	char	*env_value;
	char	*new_node;
	char	*end_position;
	char	*variable;

	variable = NULL;
	env_var = NULL;
	env_value = NULL;
	new_node = NULL;
	end_position = NULL;
	if (count_word_node(node) == 1 && (node->type == 0 || node->type == 1))
		quote_builtin_or_cmd(node);
	else
	{
		node->type = args;
		new_node = clean_cmd_type(node);
		//printf("Im here1\n");
		/* printf("cleaned variable is %s\n", new_node); */
		env_var = find_env_variable(node, end_position, variable);
		/* printf("Env var is %s\n", env_var); */
		if (env_var != NULL)
		{
			env_value = retrieve_env_variable(env_var, env_cpy);
		}
		new_node = replace_env_value(node, env_value);
		node->text = new_node;
		/* printf("Env value is %s\n", env_value); */
		/* printf("New str with environment_value is %s\n", new_node); */
	}
}

void	block_has_s_quotes(t_type *node)
{
	if (count_word_node(node) == 1)
	{
		clean_cmd_type(node);
		//printf("Im here2\n");
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
	char	*end_position;
	char	*variable;

	variable = NULL;
	env_var = NULL;
	env_value = NULL;
	new_node = NULL;
	end_position = NULL;
	node->type = args;
	new_node = clean_cmd_type(node);
	//printf("Im here3\n");
	/* printf("cleaned variable is %s\n", new_node); */
	env_var = find_env_variable(node, end_position, variable);
	/* printf("Env var is %s\n", env_var); */
	if (env_var != NULL)
		env_value = retrieve_env_variable(env_var, env_cpy);
	new_node = replace_env_value(node, env_value);
	node->text = new_node;
	/* printf("Env value is %s\n", env_value); */
	/* printf("New str with environment_value is %s\n", new_node); */
}

void	assign_quotes(t_type *node, t_environment *env_cpy)
{
	int		len;
	char	first;
	char	last;
	//char	*env_var;
	//char	*env_value;

//	env_var = NULL;
//	env_value = NULL;
	first = node->text[0];
	len = ft_strlen(node->text);
	last = node->text[len - 1];
	/* printf("Node has %d words\n", count_word_node(node)); */
	if (first == '\"' && last == '\"')
	{
		block_has_dbl_quotes(node, env_cpy);
	}
	else if (first == '\'' && last == '\'')
	{
		block_has_s_quotes(node);
	}
	else
	{
		//printf("ici\n");
		block_has_no_quotes(node, env_cpy);
	}
	//TESTS VARIABLES//
//	printf("First letter is %c\n", first);
//	printf("Last letter is %c\n", last);
//	printf("%s type is: %d\n", node->text, node->type);
//	printf("Env var is %s\n", env_var);
//	printf("Env value is %s\n", env_value);
//	printf("\n");
}
