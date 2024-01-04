/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:54:02 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/04 12:00:45 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_option_all_n(t_commande **cmd_lst)
{
	int	option;

	option = 0;
	if (*cmd_lst != NULL && (*cmd_lst)->args != NULL \
	&& (*cmd_lst)->args->arg != NULL)
		option = check_option_n((*cmd_lst)->args->arg);
	while ((*cmd_lst)->args != NULL && \
	check_option_n((*cmd_lst)->args->arg) == 1)
		(*cmd_lst)->args = (*cmd_lst)->args->next;
	return (option);
}

int	check_syntax_and_print(t_commande *cmd_lst)
{
	t_commande	*current;

	current = cmd_lst;
	while (current != NULL && current->args != NULL \
	&& current->args->arg != NULL)
	{
		if (ft_strncmp(current->args->arg, "|", 1) == 0 \
		||ft_strncmp(current->args->arg, ">", 1) == 0)
			return (ERROR);
		else
			current = current->next;
	}
	return (SUCCESS);
}

int	print_arguments(t_commande *cmd_lst, \
t_environment *env_copy, int option)
{
	while (cmd_lst->args != NULL && cmd_lst->args->arg != NULL)
	{
		if (cmd_lst->args->type == 8 || cmd_lst->args->type == 9
			|| cmd_lst->args->type == 10 || cmd_lst->args->type == 11)
			break ;
		else
			ft_echo(cmd_lst->args->arg, cmd_lst, env_copy);
		if (cmd_lst->args->next != NULL
			&& cmd_lst->args->next->arg != NULL)
			write(cmd_lst->fdout, " ", 1);
		if (cmd_lst->args->next != NULL)
			cmd_lst->args = cmd_lst->args->next;
		else
			break ;
	}
	if (option)
		return (3);
	if (!option)
		write(cmd_lst->fdout, "\n", 1);
	return (0);
}
