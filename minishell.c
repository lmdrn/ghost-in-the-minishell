/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:21:12 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 18:56:14 by lmedrano         ###   ########.fr       */
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

void	error_status(char *msg, int error)
{
	printf("Error: %s: command not found\n", msg);
	g_status = error;
}

void	init_minishell(int ac, char **av)
{
	check_args(ac, av);
	termios_mgmt(1);
	set_signals();
}

int	main(int ac, char **av, char **envp)
{
	char			**blocks;
	char			*input;
	t_environment	*head;

	input = NULL;
	init_minishell(ac, av);
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
		if (between_quotes(input) == 1)
			input = remove_xtra_spaces(input);
		else if (between_quotes(input) == 2 && block_count(input, ' ') == 1)
		{
			if (ft_strlen(input) == 2 && (input[0] == '\'' || input[0] == '\"'))
				error_status(input, 127);
			if (input[0] == '\"' || input[0] == '\'')
				input = one_word_with_quotes(input);
			if (!input)
				break ;
		}
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
	return (g_status);
}
