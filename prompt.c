/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:21:12 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/11 11:38:56 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// careful do not use printf (or modify later on) could create trouble
// (and we don't want trouble...)

int	word_count(char *str);

int	main(int ac, char **av, char **envp)
{
	char	*input;

	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		printf("\x1b[36m Welcome to ghost in the minishell!\n");
		printf("Please enter a command \e[0m\n");
		input = readline("\U0001F63B \U0001F449 ");
		if (input && *input)
			add_history (input);
		if (!ft_strncmp(input, "exit", 4))
			exit(1);
		else
		{
			printf("%s\n", input);
			printf("number of words :%d\n", check_quotes(input));
		}
	}
	return (0);
}
