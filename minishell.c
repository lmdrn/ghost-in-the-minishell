/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:21:12 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/29 19:10:42 by lmedrano         ###   ########.fr       */
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
		}
		else
		{
			if (ft_strncmp(input, "exit", 4) == 0
				|| ft_strncmp(input, "exit ", 5) == 0)
			{
				builtin_exit(input);
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
