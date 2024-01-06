/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:54:02 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/06 16:18:58 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_option_all_n(t_commande **cmd_lst)
{
	t_args *tmp;
	int		option;

	option = 0;
	tmp = (*cmd_lst)->args;
	if (*cmd_lst != NULL && tmp != NULL \
	&& tmp->arg != NULL)
		option = check_option_n(tmp->arg);
	while (tmp != NULL && \
	check_option_n(tmp->arg) == 1)
		tmp = tmp->next;
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

int	idk(t_commande *cmd)
{
	t_args	*tmp;
	int		fd;

	fd = 1;
	tmp = cmd->args;
	while (tmp)
	{
		if (tmp->type == 8 || tmp->type == 9
			|| tmp->type == 10 || tmp->type == 11)
			fd = cmd->fdout;
		tmp = tmp->next;
	}
	return (fd);
}

int	print_arguments(t_commande *cmd_lst, \
t_environment *env_copy, int option)
{
	t_args	*tmp;
	int		fd;

	fd = idk(cmd_lst);
	tmp = cmd_lst->args;
	while (tmp != NULL && tmp->arg != NULL)
	{
		if (tmp->type == 8 || tmp->type == 9
			|| tmp->type == 10 || tmp->type == 11)
			break ;
		else
			ft_echo(tmp->arg, cmd_lst, fd);
		if (tmp->next != NULL
			&& tmp->next->arg != NULL)
			write(fd, " ", 1);
		if (tmp->next != NULL)
			tmp = tmp->next;
		else
			break ;
	}
	if (option)
		return (3);
	if (!option)
		write(fd, "\n", 1);
	return (0);
}
