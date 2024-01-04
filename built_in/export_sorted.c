/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sorted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:50:03 by angela            #+#    #+#             */
/*   Updated: 2024/01/02 13:46:18 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	swap = ft_strcmp(a->key, b->key) > 0;
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
		if (current->key != NULL && !print_shlvl(current))
		{
			if (current->value == NULL)
				printf("%s=''\n", current->key);
			else
				printf("%s=%s\n", current->key, current->value);
		}
		current = current->next;
	}
}
