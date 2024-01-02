/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:54:02 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/02 14:53:33 by lmedrano         ###   ########.fr       */
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
		{
			printf("bash: erreur de syntaxe `%s'\n", current->args->arg);
			return (ERROR);
		}
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
		ft_echo(cmd_lst->args->arg, env_copy);
		if (cmd_lst->args->next != NULL
			&& cmd_lst->args->next->arg != NULL)
			printf(" ");
		if (cmd_lst->args->next != NULL)
			cmd_lst->args = cmd_lst->args->next;
		else
			break ;
	}
	if (option)
		return (3);
	if (!option)
	{
		printf("\n");
	}
	return (0);
}
