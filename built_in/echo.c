/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:53:48 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/06 12:59:50 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(t_commande *cmd_lst, t_environment *env_copy)
{
	int	option;

	option = handle_option_all_n(&cmd_lst);
	if (cmd_lst->args == NULL && !option)
		return (0);
	else if (cmd_lst->args == NULL && option)
		return (0);
	else if (check_syntax_and_print(cmd_lst) == ERROR)
	{
		g_status = ERROR;
		return (ERROR);
	}
	else if (print_arguments(cmd_lst, env_copy, option) == 3)
		return (0);
	g_status = 0;
	return (g_status);
}

void	ft_echo(char *str, t_commande *cmd, t_environment *env_copy)
{
	(void)env_copy;
	write(1, str, ft_strlen(str));
}

int	check_option_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ERROR);
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			if (str[i + 1] == ' ' || str[i + 1] == '\0')
				return (1);
			i++;
		}
		return (1);
	}
	return (0);
}
