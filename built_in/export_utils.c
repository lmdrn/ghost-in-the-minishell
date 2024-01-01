/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:50:40 by angela            #+#    #+#             */
/*   Updated: 2024/01/01 17:50:41 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_cmd(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
		{
			i++;
			break ;
		}
		if (!ft_isalpha(arg[i]))
			return (ERROR);
		i++;
	}
	while (arg[i] != '\0')
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

char	*get_value_export(char *str)
{
	char	*res;
	int		equal;

	if (str == NULL)
		return (NULL);
	equal = ft_strchrint(str, '=');
	if (equal == 0)
		return (NULL);
	if (str[equal + 1] == '\0')
		return (ft_strdup("\"\""));
	res = ft_strdup(&str[equal + 1]);
	return (res);
}

char	*get_key_export(char *str)
{
	char	*res;
	int		equal;
	int		i;

	if (str == NULL)
		return (NULL);
	equal = ft_strchrint(str, '=');
	if (equal == 0)
		return (str);
	res = malloc(sizeof(char) * equal + 1);
	i = 0;
	while (equal > 0)
	{
		res[i] = str[i];
		i++;
		equal--;
	}
	res[i] = '\0';
	return (res);
}

int	count_args_export(t_commande *cmd_lst)
{
	int		count;
	t_args	*current;

	count = 0;
	current = cmd_lst->args;
	while (current != NULL)
	{
		count++;
		if (valid_cmd(current->arg) == ERROR)
		{
			printf("mauvais arguments\n");
			return (-1);
		}
		current = current->next;
	}
	return (count);
}

void	remplace_old_value(char *value, char *key, t_environment *env_copy)
{
	t_environment	*current;

	current = env_copy;
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
		{
			if (current->value != NULL)
				free(current->value);
			current->value = strdup(value);
			if (current->value == NULL )
				exit(EXIT_FAILURE);
		}
		current = current->next;
	}
}
