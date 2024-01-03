/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:21:12 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/03 14:05:34 by lmedrano         ###   ########.fr       */
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
	check_args(ac, av);
	termios_mgmt(1);
	set_signals();
	head = init_env(envp);
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
			/* g_status = 127; */
			free(input);
		}
		/* else if (init_tokenizer(blocks, head) == -2) */
		/* { */
		/* 	g_status = 1; */
		/* } */
		termios_mgmt(1);
		set_signals();
		termios_mgmt(0);
	}
	return (g_status % 256);
}
