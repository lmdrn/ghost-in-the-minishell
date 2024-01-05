/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:20:01 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 22:22:08 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_list_to_array(t_environment *env)
{
	t_environment	*env_lst;
	int				count;
	char			**envp;	

	env_lst = env;
	count = env_count_lst(env);
	envp = allocate_mem_x_env_array(count);
	copy_key_value_pair(env, count, envp);
	envp[count] = NULL;
	return (envp);
}
