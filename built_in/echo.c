/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:53:48 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/04 14:30:58 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(t_commande *cmd_lst, t_environment *env_copy)
{
	int	option;

	option = handle_option_all_n(&cmd_lst);
	if (cmd_lst->args == NULL && !option)
		return (0);
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

void	ft_echo(char *str, t_commande *cmd, t_environment *env_copy)
{
	(void)env_copy;
	write(cmd->fdout, str, ft_strlen(str));
}

int	check_option_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ERROR);
	if (str[i] == '-' && str[i + 1] == 'n' && \
		(str[i + 2] == ' ' || str[i + 2] == '\0'))
		return (1);
	return (0);
}
