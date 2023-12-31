/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:21:12 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/31 14:00:04 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//MAIN FUNCTION:
//display prompt
//copies env
//in infinite loop, takes input, adds it to history
//checks if exit was typed (TO BE REPLACED BY BUILTIN)
//else check quotes qand remove extra spaces in input
//parses that shit and tokenize it

int	g_status = 0;

// Function to find the node with a specific key in the linked list
t_environment *find_node(char *key, t_environment	*head) {
    t_environment *current = head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) 
		{
			printf("ENV VAR IS %s\n", current->key);
            return current;
        }
        current = current->next;
    }
    return NULL; // Node not found
}

// Function to update the value of a specific key in the linked list
void update_env_variable(char *key, int increment, t_environment *head) {
    t_environment *node = find_node(key, head);
    if (node != NULL) {
        int value = atoi(node->value);
        value += increment;
        free(node->value);
        node->value = malloc(sizeof(char) * (strlen(key) + 1));
        printf("shll level is %d\n", value);
    }
}

int	main(int ac, char **av, char **envp)
{
	char			**blocks;
	char			*input;
	t_environment	*head;

	input = NULL;
	(void)ac;
	(void)av;
	init_prompt(input);
	head = init_env(envp);
	/* update_env_variable("SHLVL", 1, head); */
	while (1)
	{
		input = ft_prompt();
		if (input == NULL)
		{
			free(input);
			break ;
		}
		if (input && *input)
			add_history (input);
		if (ft_strncmp(input, "exit", 4) == 0
			|| ft_strncmp(input, "exit ", 5) == 0)
		{
			builtin_exit(input);
			update_env_variable("SHELL_LVL", -1, head);
			printf("Error is %d\n", g_status);
			free(input);
		}
		else
		{
			if (ft_strncmp(input, "exit", 4) == 0
				|| ft_strncmp(input, "exit ", 5) == 0)
			{
				builtin_exit(input);
				update_env_variable("SHELL_LVL", -1, head);
				printf("Error is %d\n", g_status);
				free(input);
				break ;
			}
			if (between_quotes(input) == 0)
				input = remove_xtra_spaces(input);
			/* printf("Cleaned input is : %s\n", input); */
			blocks = init_parse(input);
			if (blocks == NULL)
			{
				printf("I have been there\n");
				handling_signals(input);
			}
			else if (init_tokenizer(blocks, head) == -1)
			{
				printf("Error: %s: command not found\n", input);
				g_status = 127;
				printf("Error is %d\n", g_status);
				handling_signals(input);
			}
		}
	}
	return (g_status % 256);
}
