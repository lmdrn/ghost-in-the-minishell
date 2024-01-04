/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:21:12 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/02 21:48:33 by lmedrano         ###   ########.fr       */
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
        if (ft_strcmp(current->key, key) == 0)
		{
			printf("ENV VAR IS %s\n", current->key);
            return current;
        }
        current = current->next;
    }
    return NULL; // Node not found
}



int	main(int ac, char **av, char **envp)
{
	char			**blocks;
	char			*input;
	t_environment	*head;

	input = NULL;
	(void)ac;
	(void)av;
	check_args(ac,av);
	termios_mgmt(1);
	set_signals();
	head = init_env(envp);

	increment_shlvl(&head);
	ft_welcome();

	while (1)
	{
		input = ft_prompt();
		if (!input)
			break ;
		if (input && *input)
			add_history (input);
		unset_signals();
		termios_mgmt(0);
		if (between_quotes(input) == 0)
			input = remove_xtra_spaces(input);
		blocks = init_parse(input);
		if (ft_strncmp(input, "exit", 4) == 0
			|| ft_strncmp(input, "exit ", 5) == 0)
		{
			builtin_exit(input);
			printf("Error is %d\n", g_status);
			free(input);
			break ;
		}
		if (blocks == NULL)
		{
			free(input);
		}
		else if (init_tokenizer(blocks, head) == -1)
		{
			printf("Error: %s: command not found\n", input);
			g_status = 127;
			/* printf("Error is %d\n", g_status); */
			free(input);
		}

		termios_mgmt(1);
		set_signals();
		termios_mgmt(0);
	}
	return (g_status % 256);
}
