/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:53:48 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/01 17:50:31 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(t_commande *cmd_lst, t_environment *env_copy)
{
	int	option;

	option = handle_option_all_n(&cmd_lst);
	if (cmd_lst->args == NULL && !option)
	{
		printf("\n");
		return (0);
	}
	if (cmd_lst->args == NULL && option)
	{
		return (0);
	}
	if (check_syntax_and_print(cmd_lst) == ERROR)
		return (ERROR);
	if (print_arguments(cmd_lst, env_copy, option) == 3)
		return (0);
	return (0);
}

void	ft_echo(char *str, t_environment *env_copy)
{
	int		i;
	char	*value_env;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			printf("print derrniere error");
			i++;
		}
		else if (str[i] == '$' && isalnum(str[i + 1]) && str[i + 1] != '\0')
		{
			if (check_is_in_env(env_copy, str) == ERROR)
				exit(1);
			else
			{
				value_env = get_env_value(env_copy, &str[i + 1]);
				printf("%s", value_env);
			}
		}
		else
			printf("%c", str[i]);
		i++;
	}
}

int	check_option_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ERROR);
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '-' && str[i + 1] == 'n')
		return (1);
	return (0);
}
