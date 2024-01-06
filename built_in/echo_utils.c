/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:54:02 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/06 21:38:58 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option_n(t_commande **cmd)
{
	t_args	*tmp;
	char	*new_arg;

	if (!ft_strncmp((*cmd)->args->arg, "-n", 2))
	{
		new_arg = (*cmd)->args->arg;
		new_arg++;
		if (!is_n_word(new_arg))
		{
			tmp = (*cmd)->args->next;
			free((*cmd)->args->arg);
			free((*cmd)->args);
			(*cmd)->args = tmp;
			return (1);
		}
	}
	return (0);
}

int	handle_option_all_n(t_commande **cmd_lst)
{
	t_args	*tmp;
	int		option;

	option = 0;
	tmp = (*cmd_lst)->args;
	while ((*cmd_lst)->args != NULL && check_option_n(cmd_lst) == 1)
	{
		option = 1;
		tmp = (*cmd_lst)->args;
	}
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

int	print_arguments(t_commande *cmd_lst,
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
