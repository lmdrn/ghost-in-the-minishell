/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:08:35 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/06 11:52:58 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_builtin_or_cmd(t_type *node, t_environment *env)
{
	clean_cmd_type(node);
	if (is_builtin(node->text) == 0)
		node->type = builtin;
	else if (is_executable_command(node->text, env) == 0)
		node->type = cmd;
	else if (is_abs_exec(node->text) == 1)
		node->type = abs_cmd;
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

	env_var = NULL;
	env_value = NULL;
	new_node = NULL;
	end_position = NULL;
	variable = NULL;
	if (count_word_node(node) == 1 && (node->type == 0 || node->type == 1
			|| node->type == 14))
		quote_builtin_or_cmd(node, env_cpy);
	else
	{
		node->type = args;
		new_node = clean_cmd_type(node);
		ft_strlcpy(node->text, new_node, ft_strlen(new_node) + 1);
		env_var = find_env_variable(node, end_position, variable);
		free(new_node);
		new_node = replace_with_expand_var(env_var, env_value, node, env_cpy);
		reassign_new_node(node, new_node);
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

	env_var = NULL;
	env_value = NULL;
	new_node = NULL;
	end_position = NULL;
	variable = NULL;
	node->type = args;
	// new_node = clean_cmd_type(node);
	// new_node = remove_xtra_spaces(new_node);
	env_var = find_env_variable(node, end_position, variable);
	if (env_var != NULL)
		env_value = retrieve_env_variable(env_var, env_cpy);
	if (ft_strncmp(node->text, "$?", 2) == 0)
		new_node = replace_exit_status(node->text);
	else
		new_node = replace_env_value(node, env_value);
	ft_strlcpy(node->text, new_node, ft_strlen(new_node) + 1);
	free(new_node);
	new_node = NULL;
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
	if (first == '\"' && last == '\"')
		block_has_dbl_quotes(node, env_cpy);
	else if (first == '\'' && last == '\'')
		block_has_s_quotes(node, env_cpy);
	else
	{
		block_has_no_quotes(node, env_cpy);
		node->flag = 1;
	}
}
