/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:20:23 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/31 12:27:54 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//fct that compares if input is equal to builtin 
int	is_builtin(char *node)
{
	if (ft_strncmp(node, "echo", 4) == 0)
		return (0);
	if (ft_strncmp(node, "pwd", 3) == 0)
		return (0);
	if (ft_strncmp(node, "cd", 2) == 0)
		return (0);
	if (ft_strncmp(node, "export", 6) == 0)
		return (0);
	if (ft_strncmp(node, "unset", 5) == 0)
		return (0);
	if (ft_strncmp(node, "env", 3) == 0)
		return (0);
	if (ft_strncmp(node, "exit", 4) == 0)
		return (0);
	else
		return (1);
}

//fct that checks if input is a symbol
int	is_asym(char *node)
{
	if (ft_strncmp(node, "|", 1) == 0)
		return (0);
	else if (ft_strncmp(node, ">>", 2) == 0)
		return (0);
	else if (ft_strncmp(node, "<<", 2) == 0)
		return (0);
	else if (ft_strncmp(node, ">", 1) == 0)
		return (0);
	else if (ft_strncmp(node, "<", 1) == 0)
		return (0);
	else
		return (1);
}

//fct that assigns type to each node
void	assign_types(t_type *node, t_type *lst, int cmd_assigned)
{
	t_type	*next_node;
	t_type	*head;

	head = node;
	next_node = NULL;
	if (ft_strncmp(node->text, "|", 1) == 0)
		assign_pipe(node);
	else if (ft_strncmp(node->text, ">>", 2) == 0)
		assign_dbl_ch_droit(node, lst, next_node);
	else if (ft_strncmp(node->text, "<<", 2) == 0)
		assign_dbl_ch_gauche(node, lst, next_node);
	else if (ft_strncmp(node->text, ">", 1) == 0)
		assign_ch_droit(node, lst, next_node);
	else if (ft_strncmp(node->text, "<", 1) == 0)
		assign_ch_gauche(node, lst, next_node);
	else if (is_builtin(node->text) == 0 && cmd_assigned == 0)
		assign_builtin(node);
	else if (is_abs_path_executable(node->text) == 1 && cmd_assigned == 0
		&& ft_strncmp(node->text, "/", 1) == 0)
	{
		printf("abs cmd\n");
		assign_abs_cmd(node);
	}
	else if (is_executable_command(node->text) == 0 && cmd_assigned == 0)
		assign_exec_cmd(node);
	else if (ft_strncmp(node->text, "./", 2) == 0 && cmd_assigned == 0)
		assign_exec_cmd(node);
	else
		assign_args(node);
}
