/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:57:29 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/09 15:59:54 by lmedrano         ###   ########.fr       */
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

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	return (0);
}

t_type	*clean_cmd_type(t_type *node)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char *) * ft_strlen(node->text) + 1);
	if (new_str == NULL)
		return (NULL);
	while (node->text[i] != '\0')
	{
		if (node->text[i] != '\'' && node->text[i] != '\"'
			&& !ft_isspace(node->text[i]))
		{
			new_str[j] = node->text[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	node->text = new_str;
	printf("without quotes is %s\n", new_str);
	return (node);
}

t_type	*create_node_and_assign_types(char *text, t_type *head)
{
	t_type	*node;

	node = create_node(text);
	assign_types(node, head);
	return (node);
}

//fct that takes blocks from split and transforms
//each block into nodes by calling create_node
//then iterates through list again 
//to assign a type to each node

t_type	*init_lst(char **blocks, t_type *node)
{
	t_type	*head;
	t_type	*current;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (blocks[i])
	{
		node = create_node_and_assign_types(blocks[i], head);
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
