/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:08:35 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 16:32:43 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_builtin_or_cmd(t_type *node, t_environment *env)
{
	clean_cmd_type(node);
	printf("hello\n");
	if (is_builtin(node->text) == 0)
		node->type = builtin;
	else if (is_executable_command(node->text, env) == 0)
		node->type = cmd;
	else if (is_abs_exec(node->text) == 1)
	{
		printf("hello\n");
		node->type = abs_cmd;
	}
	else
		node->type = args;
}

char	*trick_quote(char *new_node)
{
	char	*tmp;

	if (new_node[0] == '\'')
	{
		if (new_node && new_node[0] != '\0'
			&& new_node[ft_strlen(new_node) - 1] != '\'')
		{
			tmp = malloc(sizeof(char) * (ft_strlen(new_node) + 2));
			if (tmp)
			{
				strcpy(tmp, new_node);
				tmp[ft_strlen(new_node)] = '\'';
				tmp[ft_strlen(new_node) + 1] = '\0';
				free(new_node);
				new_node = tmp;
			}
		}
	}
	return (new_node);
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
	if (count_word_node(node) == 1 && (node->type == 0 || node->type == 1
			|| node->type == 14))
		quote_builtin_or_cmd(node, env_cpy);
	else
	{
		node->type = args;
		new_node = clean_cmd_type(node);
		ft_strlcpy(node->text, new_node, ft_strlen(new_node) + 1);
		env_var = find_env_variable(node, end_position, variable);
		/* printf("Env var is %s\n", env_var); */
		if (env_var != NULL)
			env_value = retrieve_env_variable(env_var, env_cpy);
		if (ft_strncmp(node->text, "$?", 2) == 0)
		{
			free(new_node);
			new_node = replace_exit_status(node->text);
		}
		else
		{
			new_node = replace_env_value(node, env_value);
			/* new_node = trick_quote(new_node); */
		}
		ft_strlcpy(node->text, new_node, ft_strlen(new_node) + 1);
		free(new_node);
		new_node = NULL;
		/*printf("Env value is %s\n", env_value); */
		/* printf("New str with environment_value is %s\n", new_node); */
	}
}

void	block_has_s_quotes(t_type *node, t_environment *env)
{
	int		quotes;
	char	*new_node;

	quotes = 0;
	if (count_word_node(node) == 1)
	{
		new_node = clean_cmd_type(node);
		if (is_builtin(node->text) == 0)
			node->type = builtin;
		else if (is_executable_command(node->text, env) == 0)
			node->type = cmd;
	}
	else
	{
		new_node = clean_cmd_type(node);
		node->type = args;
	}
	ft_strlcpy(node->text, new_node, ft_strlen(new_node) + 1);
	free(new_node);
	new_node = NULL;
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
	new_node = remove_xtra_spaces(new_node);
	env_var = find_env_variable(node, end_position, variable);
	/* printf("Env var is %s\n", env_var); */
	if (env_var != NULL)
		env_value = retrieve_env_variable(env_var, env_cpy);
	if (ft_strncmp(node->text, "$?", 2) == 0)
		new_node = replace_exit_status(node->text);
	else
	{
		new_node = replace_env_value(node, env_value);
	}
	ft_strlcpy(node->text, new_node, ft_strlen(new_node) + 1);
	free(new_node);
	new_node = NULL;
	/* printf("Env value is %s\n", env_value); */
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
	last = 0;
	first = node->text[0];
	len = ft_strlen(node->text);
	if (first > 0)
		last = node->text[len - 1];
	/* printf("Node has %d words\n", count_word_node(node)); */
	if (first == '\"' && last == '\"')
		block_has_dbl_quotes(node, env_cpy);
	else if (first == '\'' && last == '\'')
		block_has_s_quotes(node, env_cpy);
	else
	{
		block_has_no_quotes(node, env_cpy);
		node->flag = 1;
	}
	//TESTS VARIABLES//
	/* printf("First letter is %c\n", first); */
	/* printf("Last letter is %c\n", last); */
	/* printf("%s type is: %d\n", node->text, node->type); */
	/* printf("Env var is %s\n", env_var); */
	/* printf("Env value is %s\n", env_value); */
	/* printf("\n"); */
}
