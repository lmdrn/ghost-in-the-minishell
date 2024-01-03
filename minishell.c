/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:21:12 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/03 18:31:29 by lmedrano         ###   ########.fr       */
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

// Function to extract a single word from a string enclosed in quotes
char	*one_word_with_quotes(const char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new_input;

	len = ft_strlen(str);
	i = 0;
	if (len < 2)
		return (NULL);
	if (str[i] != '\"' && str[i] != '\'')
		return (NULL);
	while (str[i + 1] != '\0' && !ft_isspace(str[i + 1]))
		i++;
	if (str[i] != '\"' && str[i] != '\'')
		return (NULL);
	new_input = malloc(len - 2 + 1);
	j = 0;
	i = 1;
	while (i < len - 1)
		new_input[j++] = str[i++];
	new_input[j] = '\0';
	return (new_input);
}

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
		printf("block ocunt is %d\n", block_count(input, ' '));
		printf("quotes is %d\n", between_quotes(input));
		if (between_quotes(input) == 1)
			input = remove_xtra_spaces(input);
		else if (between_quotes(input) == 2 && block_count(input, ' ') == 1)
		{
			input = one_word_with_quotes(input);
			if (!input)
				break ;
		}
		else if (between_quotes(input) == 0)
			printf("yo\n");
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
			/* free(input); */
		}
		termios_mgmt(1);
		set_signals();
		termios_mgmt(0);
	}
	return (g_status % 256);
}
