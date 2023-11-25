/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:21:12 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/14 16:31:52 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// careful do not use printf (or modify later on) could create trouble
// (and we don't want trouble...)

int	g_status = 0;

void print_environment_list(t_environment *head)
{
	int node_number = 1;
	t_environment *current = head;
	while (current != NULL)
	{
		if (current->key != NULL && current->value != NULL)
		{
			printf("Node %d: key -> %s, value -> %s\n", node_number, current->key, current->value);
		}
		else
		{
			printf("Node %d: Incomplete or corrupted data\n", node_number);
			break;
		}

		current = current->next;
		node_number++;
	}
}
int	main(int ac, char **av, char **envp)
{
	char			**blocks;
	char			*input;
	t_environment	*env_copy;

	input = NULL;
	(void)ac;
	(void)av;
	init_prompt(input);
	env_copy = init_env(envp);
//	if (env_copy != NULL)
//		print_environment_list(env_copy);
	printf("\n--------------------------\n");
	if (env_copy != NULL)
	{
		while (1)
		{
			input = ft_prompt();
			if (input == NULL) {
				free(input);
				break;
			}
			if (input && *input)
				add_history(input);
			if (ft_strncmp(input, "exit", 4) == 0) {
				free(input);
				break;
			} else {
				if (ft_strncmp(input, "exit", 4) == 0) {
					free(input);
					break;
				}
				if (between_quotes(input) == 0)
					input = remove_xtra_spaces(input);
				printf("Cleaned input is : %s\n", input);
				blocks = init_parse(input);
				init_tokenizer(blocks, env_copy);
			}
		}
	}
	printf ("moouarf\n");
	return (0);
}
