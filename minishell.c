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
        if (strcmp(current->key, key) == 0) 
		{
			printf("ENV VAR IS %s\n", current->key);
            return current;
        }
        current = current->next;
    }
    return NULL; // Node not found
}




void increment_shlvl(t_environment **env_copy)
{
//	if (!should_increment_shlvl) {
//		return;
//	}
	char *shlvl_str = get_env_value(*env_copy, "SHLVL");
	printf("valeur de SHVL dans la fonction incrementation :%s\n", shlvl_str);

	int shlvl = shlvl_str ? atoi(shlvl_str) : 0;
	shlvl++;

	// Utiliser ft_itoa pour convertir shlvl en chaîne
	char *shlvl_updated = ft_itoa(shlvl);
	if (shlvl_updated == NULL) {
		// Gestion de l'erreur d'allocation de mémoire
		return;
	}

	remplace_old_value(shlvl_updated, "SHLVL", *env_copy);

	// Libérer la mémoire allouée par ft_itoa
	free(shlvl_updated);
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
//		if (strcmp(av[0], "./minishell") == 0)
//			should_increment_shlvl = 1;

		//should_increment_shlvl = 0;

//		shlvl = get_env_value(head, "SHLVL");
//		printf("valeur de SHLVL : %s\n", shlvl);

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
