/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:57:29 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/02 20:59:33 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//fct to create node + copy txt into
struct	s_type	*create_node(const char *block)
{
	t_type	*node;

	node = malloc(sizeof(t_type));
	if (node == NULL)
	{
		ft_putendl_fd("malloc failed\n", 1);
		return (NULL);
	}
	node->text = ft_strdup(block);
	if (node->text == NULL)
	{
		ft_putendl_fd("dup failed\n", 1);
		return (NULL);
	}
	node->flag = 0;
	node->next = NULL;
	return (node);
}

t_type	*create_node_and_assign_types(char *text, t_type *head,
		t_environment *env_copy, int cmd_assigned)
{
	t_type	*node;

	node = create_node(text);
	assign_types(node, head, cmd_assigned);
	printf("text is %s, type is %d\n", node->text, node->type);
	if (node->type == args)
		assign_quotes(node, env_copy);
	return (node);
}

void	append_to_list(t_type **head, t_type **current, t_type *node)
{
	if (!(*head))
	{
		*head = node;
		*current = node;
	}
	else
	{
		(*current)->next = node;
		*current = node;
	}
}

//fct that takes blocks from split and transforms
//each block into nodes by calling create_node
//then iterates through list again 
//to assign a type to each node

t_type	*init_lst(char **blocks, t_type *node, t_environment *env_copy)
{
	int		cmd_assigned;
	t_type	*head;
	t_type	*redir;
	t_type	*current;
	int		i;

	head = NULL;
	redir = NULL;
	current = NULL;
	cmd_assigned = 0;
	i = 0;
	while (blocks[i])
	{
		node = create_node_and_assign_types(blocks[i], head,
				env_copy, cmd_assigned);
		if (node->type == cmd || node->type == abs_cmd || node->type == builtin)
			cmd_assigned = 1;
		else if (node->type == 7)
			cmd_assigned = 0;
		append_to_list(&head, &current, node);
		i++;
	}
	return (head);
}
