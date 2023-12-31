/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:50:48 by angela            #+#    #+#             */
/*   Updated: 2024/01/06 19:40:49 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	list_size(t_environment *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}

t_environment	*create_new_node(char *key, char *value)
{
	t_environment	*new_node;

	new_node = (t_environment *)malloc(sizeof(t_environment));
	if (new_node == NULL)
		exit(EXIT_FAILURE);
	new_node->key = ft_strdup(key);
	if (value != NULL)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	if ((new_node->key == NULL && key != NULL) || \
	(new_node->value == NULL && value != NULL))
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		exit(EXIT_FAILURE);
	}
	free(key);
	free(value);
	return (new_node);
}

void	add_node(t_environment **env_copy, char *key, char *value)
{
	t_environment	*new_node;
	t_environment	*last;

	new_node = create_new_node(key, value);
	if (*env_copy == NULL)
		*env_copy = new_node;
	else
	{
		last = last_node(*env_copy);
		last->next = new_node;
	}
}

void	print_nodes(t_environment **node, char c)
{
	t_environment	*current_node;

	current_node = *node;
	printf("Liste %c\n", c);
	if (current_node == NULL)
		printf("c'est vide\n");
	while (current_node != NULL)
	{
		printf("node(%s)->data = %s\n", current_node->key, current_node->value);
		current_node = current_node->next;
	}
}

t_environment	*last_node(t_environment *head)
{
	if (!head)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}
