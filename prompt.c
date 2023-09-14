/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:21:12 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/14 08:52:45 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// careful do not use printf (or modify later on) could create trouble
// (and we don't want trouble...)

int	main(int ac, char **av, char **envp)
{
	char	*input;
	int		i;

	i = 0;
	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		printf("\x1b[36mWelcome to ghost in the minishell!\n");
		printf("Please enter a command \e[0m\n");
		input = readline("\U0001F63B \U0001F449 ");
		if (input && *input)
			add_history (input);
		if (!ft_strncmp(input, "exit", 4))
			exit(1);
		else
		{
			printf("%s\n", input);
			printf("number of words :%d\n", word_count(input));
			/* printf("letters in block: %d\n", block_count(input, 0, ' ')); */
			char delimiter = ' '; // Change to space character
			int block_count;
			char** blocks = ft_parsing_split(input, delimiter, &block_count);
			i = 0;
			while (i < block_count)
			{
				printf("Block %d: %s\n", i, blocks[i]);
				free(blocks[i]);
				i++;
			}
			free(blocks);
		}
	}
	return (0);
}
