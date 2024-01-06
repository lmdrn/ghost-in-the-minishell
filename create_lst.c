/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:57:29 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/06 18:57:45 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//fct to create node + copy txt into
struct	s_type	*create_node(char *block)
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
	assign_types(node, head, cmd_assigned, env_copy);
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

/*
 * ints[0] == 0
 * ints[1] == cmd_ok
 * ints[2] == pipe
*/

int	init_while(char **blocks, t_type *node, t_type **head,
			t_environment *env_copy)
{
	t_type	*current;
	int		ints[3];

	ft_memset(ints, 0, sizeof(ints));
	current = NULL;
	while (blocks[ints[0]])
	{
		node = create_node_and_assign_types(blocks[ints[0]], *head,
				env_copy, ints[1]);
		if (node->type == cmd || node->type == abs_cmd || node->type == builtin)
			ints[1] = 1;
		else if (node->type == 7)
		{
			ints[1] = 0;
			ints[2] = 1;
		}
		append_to_list(head, &current, node);
		ints[0]++;
	}
	if (ints[1] == 0 && ints[2])
		return (1);
	return (0);
}

//fct that takes blocks from split and transforms
//each block into nodes by calling create_node
//then iterates through list again 
//to assign a type to each node

t_type	*init_lst(char **blocks, t_type *node, t_environment *env_copy)
{
	t_type	*head;
	int		ret;

	head = NULL;
	ret = init_while(blocks, node, &head, env_copy);
	if (ret == 1)
	{
		printf("Error: syntax error: unexpected end of file\n");
		return (NULL);
	}
	return (head);
}
