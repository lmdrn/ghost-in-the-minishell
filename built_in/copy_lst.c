/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:50:48 by angela            #+#    #+#             */
/*   Updated: 2024/01/04 11:16:14 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_environment	*create_node_cpy(t_environment *current)
{
	t_environment	*new_node;

	new_node = malloc(sizeof(t_environment));
	if (new_node == NULL)
		return (NULL);
	new_node->key = ft_strdup(current->key);
	if (current->value != NULL)
		new_node->value = ft_strdup(current->value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_environment	*copy_env_list(t_environment *head)
{
	t_environment	*current;
	t_environment	*new_list;
	t_environment	*tail;
	t_environment	*new_node;

	current = head;
	new_list = NULL;
	tail = NULL;
	if (head == NULL)
		return (NULL);
	while (current != NULL)
	{
		new_node = create_node_cpy(current);
		if (new_node == NULL)
			return (NULL);
		if (new_list == NULL)
			new_list = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		current = current->next;
	}
	return (new_list);
}
