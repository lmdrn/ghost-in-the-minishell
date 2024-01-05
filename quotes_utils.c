/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:33:22 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 23:33:53 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reassign_new_node(t_type *node, char *new_node)
{
	ft_strlcpy(node->text, new_node, ft_strlen(new_node) + 1);
	free(new_node);
	new_node = NULL;
}

char	*replace_with_expand_var(char *env_var, char *env_value,
			t_type *node, t_environment *env_cpy)
{
	char	*ret;

	if (env_var != NULL)
		env_value = retrieve_env_variable(env_var, env_cpy);
	if (ft_strncmp(node->text, "$?", 2) == 0)
		ret = replace_exit_status(node->text);
	else
		ret = replace_env_value(node, env_value);
	return (ret);
}
