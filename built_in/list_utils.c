/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:50:48 by angela            #+#    #+#             */
/*   Updated: 2024/01/02 13:48:04 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char* decrement_and_convert_to_string(const char* str) {
	if (str == NULL) {
		return NULL;
	}

	int value = atoi(str);  // Convertit la chaîne en entier
	if (value > 0)
		value--;                // Décrémente la valeur

	// Convertit la valeur décrémentée en chaîne
	char* result = ft_itoa(value);
	return result;
}


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
	new_node->key = strdup(key);
	if (value != NULL)
		new_node->value = strdup(value);
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
