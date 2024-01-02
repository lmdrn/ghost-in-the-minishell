/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sorted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:50:03 by angela            #+#    #+#             */
/*   Updated: 2024/01/01 17:50:04 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//
//t_environment	*copy_env_list(t_environment *head)
//{
//	t_environment *current;
//	t_environment *new_list;
//	t_environment *new_node;
//	t_environment *tail;
//
//	if (head == NULL)
//		return NULL;
//
//	current = head;
//	new_list = NULL;
//	tail = NULL;
//
//	while (current != NULL)
//	{
//		new_node = malloc(sizeof(t_environment));
//		if (new_node == NULL)
//			return NULL;
//		new_node->key = strdup(current->key);
//		if (current->value != NULL)
//			new_node->value = strdup(current->value);
//		new_node->next = NULL;
//		if (new_list == NULL)
//			new_list = new_node;
//		else
//			tail->next = new_node;
//		tail = new_node;
//		current = current->next;
//	}
//	return new_list;
//}

t_environment *copy_env_list(t_environment *head) {
	if (head == NULL) {
		return NULL;
	}

	t_environment *current = head, *new_list = NULL, *tail = NULL, *new_node;

	while (current != NULL) {
		new_node = malloc(sizeof(t_environment));
		if (new_node == NULL) {
			// Gérer l'erreur d'allocation ici
			return NULL;
		}

		new_node->key = strdup(current->key);
		if (current->value != NULL)
			new_node->value = strdup(current->value);
		else
			new_node->value = NULL;
		new_node->next = NULL;

		if (new_list == NULL) {
			new_list = new_node;
		} else {
			tail->next = new_node;
		}
		tail = new_node;

		current = current->next;
	}

	return new_list;
}

int	ft_strchrint(char *s, char c)
{
	unsigned char	letter;
	int				i;

	i = 0;
	letter = c;
	while ((s[i] != '\0') && (s[i] != letter))
		i++;
	if (s[i] == letter)
		return (i);
	return (0);
}

int	need_swap(t_environment *a, t_environment *b)
{
	int	swap;

	if (a->key == NULL || b->key == NULL)
	{
		if (a->key == NULL && b->key != NULL)
		{
			return (1);
		}
		if (a->key != NULL && b->key == NULL)
		{
			return (0);
		}
		return (0);
	}
	swap = strcmp(a->key, b->key) > 0;
	return (swap);
}

void	swap_nodes(t_environment *a, t_environment *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void	bubble_sort_env(t_environment **head)
{
	int				swapped;
	t_environment	**current;

	if (*head == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = head;
		while ((*current)->next != NULL)
		{
			if (need_swap(*current, (*current)->next))
			{
				swap_nodes(*current, (*current)->next);
				swapped = 1;
			}
			current = &(*current)->next;
		}
	}
}

void	print_sorted_env(t_environment *env_copy)
{
	t_environment	*current;

	current = env_copy;
	while (current != NULL)
	{
		if (current->key != NULL)
		{
			if (current->value == NULL)
				printf("%s=''\n", current->key);
			else
				printf("%s=%s\n", current->key, current->value);
		}
		current = current->next;
	}
}
