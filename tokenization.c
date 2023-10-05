/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:20:23 by lmedrano          #+#    #+#             */
/*   Updated: 2023/10/05 12:11:32 by lmedrano         ###   ########.fr       */
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
void	assign_types(t_type *node, t_type *lst)
{
	t_type	*next_node;

	if (ft_strncmp(node->text, "|", 1) == 0)
	{
		node->type = is_pipe;
		printf("%s type is: %d\n", node->text, node->type);
		printf("\n");
	}
	else if (ft_strncmp(node->text, ">>", 2) == 0)
	{
		node->type = dbl_ch_d;
		printf("%s type is: %d\n", node->text, node->type);
		printf("\n");
		next_node = lst;
		while (next_node != NULL)
		{
			if (next_node == node)
				break ;
			next_node = next_node->next;
		}
		if (next_node != NULL && next_node->next != NULL)
		{
			next_node = next_node->next;
			next_node->type = fileout;
			printf("%s type is: %d\n", next_node->text, next_node->type);
			printf("\n");
		}
	}
	else if (ft_strncmp(node->text, "<<", 2) == 0)
	{
		node->type = dbl_ch_g;
		printf("%s type is: %d\n", node->text, node->type);
		printf("\n");
		next_node = lst;
		while (next_node != NULL)
		{
			if (next_node == node)
				break ;
			next_node = next_node->next;
		}
		if (next_node != NULL && next_node->next != NULL)
		{
			next_node = next_node->next;
			next_node->type = delimiter;
			printf("%s type is: %d\n", next_node->text, next_node->type);
			printf("\n");
		}
	}
	else if (ft_strncmp(node->text, ">", 1) == 0)
	{
		node->type = ch_d;
		printf("%s type is: %d\n", node->text, node->type);
		printf("\n");
		next_node = lst;
		while (next_node != NULL)
		{
			if (next_node == node)
				break ;
			next_node = next_node->next;
		}
		if (next_node != NULL && next_node->next != NULL)
		{
			next_node = next_node->next;
			next_node->type = fileout;
			printf("%s type is: %d\n", next_node->text, next_node->type);
		}
	}
	else if (ft_strncmp(node->text, "<", 1) == 0)
	{
		node->type = ch_g;
		printf("type is: %d\n", node->type);
		printf("\n");
		next_node = lst;
		while (next_node != NULL)
		{
			if (next_node == node)
				break ;
			next_node = next_node->next;
		}
		if (next_node != NULL && next_node->next != NULL)
		{
			next_node = next_node->next;
			next_node->type = filein;
			printf(" %s type is: %d\n", next_node->text, next_node->type);
			printf("\n");
		}
	}
	else if (is_executable_command(node->text) == 0)
	{
		node->type = cmd;
		printf("%s type is: %d\n", node->text, node->type);
		printf("\n");
	}
	else if (is_builtin(node->text) == 0)
	{
		node->type = builtin;
		printf("%s type is: %d\n", node->text, node->type);
		printf("\n");
	}
	else
	{
		node->type = args;
		printf("%s type is: %d\n", node->text, node->type);
		printf("\n");
	}
}
