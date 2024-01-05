/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:21:12 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 21:15:11 by lmedrano         ###   ########.fr       */
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


void	init_minishell(int ac, char **av, t_environment **head, char **envp)
{
	check_args(ac, av);
	termios_mgmt(1);
	set_signals();
	*head = init_env(envp);
	increment_shlvl(head);
	ft_welcome();
}

void	parse_and_execute(char **blocks, char *input, t_environment *head)
{
	blocks = init_parse(input);
	if (blocks == NULL)
		free(input);
	else if (ft_strncmp(input, ".", 2) == 0)
	{
		printf(".: filename argument required\n");
		g_status = 2;
	}
	else if (ft_strncmp(input, "..", 3) == 0)
		error_status(input, 127);
	else if (init_tokenizer(blocks, head) == -1)
		error_status(input, 127);
	termios_mgmt(1);
	set_signals();
	termios_mgmt(0);
}

int	main(int ac, char **av, char **envp)
{
	char			**blocks;
	char			*input;
	t_environment	*head;

	input = NULL;
	init_minishell(ac, av, &head, envp);
	while (1)
	{
		input = ft_prompt();
		if (!input)
			break ;
		if (input && *input)
			add_history (input);
		unset_signals();
		termios_mgmt(0);
		if (between_quotes(input) == 1)
			input = remove_xtra_spaces(input);
		else if (between_quotes(input) == 2 && block_count(input, ' ') == 1)
			if (!quote_manager(&input))
				continue ;
		parse_and_execute(blocks, input, head);
	}
	return (g_status);
}
