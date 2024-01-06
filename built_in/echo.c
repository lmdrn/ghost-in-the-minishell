/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:53:48 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/06 20:52:59 by lmedrano         ###   ########.fr       */
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

void	ft_echo(char *str, t_commande *cmd, int fd)
{
	write(fd, str, ft_strlen(str));
}

