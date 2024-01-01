/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:57:29 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/29 13:07:34 by lmedrano         ###   ########.fr       */
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
	node->next = NULL;
	return (node);
}

t_type	*create_node_and_assign_types(char *text, t_type *head,
		t_environment *env_copy, int cmd_assigned)
{
	t_type	*node;

	node = create_node(text);
	assign_types(node, head, env_copy, cmd_assigned);
	return (node);
}

//fct that takes blocks from split and transforms
//each block into nodes by calling create_node
//then iterates through list again 
//to assign a type to each node

t_type	*init_lst(char **blocks, t_type *node, t_environment *env_copy)
{
	int cmd_assigned = 0 ;
	t_type	*head;
	t_type	*current;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (blocks[i])
	{
		node = create_node_and_assign_types(blocks[i], head, env_copy, cmd_assigned);
		if (node->type == cmd) {
			cmd_assigned = 1;
		}
		else if (node->type == 7) {
			cmd_assigned = 0;
		}
		if (!head)
		{
			head = node;
			current = node;
		}
		else
		{
			current->next = node;
			current = node;
		}
		i++;
	}

	return (head);
}
