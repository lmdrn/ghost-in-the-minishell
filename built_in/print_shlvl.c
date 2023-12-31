/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shlvl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 02:20:49 by angela            #+#    #+#             */
/*   Updated: 2024/01/06 21:42:33 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_shlvl(t_environment *current)
{
	char	*shlvl;

	if (ft_strcmp(current->key, "SHLVL") == 0)
	{
		shlvl = decrement_and_convert_to_string(current->value);
		if (shlvl != NULL)
		{
			printf("%s=%s\n", current->key, shlvl);
			free(shlvl);
			return (SUCCESS);
		}
	}
	return (ERROR);
}

char	*decrement_and_convert_to_string(const char *str)
{
	int		value;
	char	*result;

	if (str == NULL)
		return (NULL);
	value = ft_atoi(str);
	if (value > 0)
		value--;
	result = ft_itoa(value);
	return (result);
}

void	increment_shlvl(t_environment **env_copy)
{
	char	*shlvl_str;
	int		shlvl;
	char	*shlvl_updated;

	shlvl_str = get_env_value(*env_copy, "SHLVL");
	if (shlvl_str != NULL)
		shlvl = ft_atoi(shlvl_str);
	else
		shlvl = 0;
	shlvl++;
	shlvl_updated = ft_itoa(shlvl);
	if (shlvl_updated == NULL)
		return ;
	remplace_old_value(shlvl_updated, "SHLVL", *env_copy);
	free(shlvl_updated);
}

int	is_n_word(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}
