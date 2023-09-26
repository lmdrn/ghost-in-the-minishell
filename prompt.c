/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:21:12 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/26 19:33:00 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// careful do not use printf (or modify later on) could create trouble
// (and we don't want trouble...)

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**blocks;
	int		i;
	int		wc;
	int		block_count;
	char	delimiter;

	delimiter = ' ';
	i = 0;
	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		ft_putendl_fd("\x1b[36mWelcome to ghost in the minishell!\n", 1);
		ft_putendl_fd("Please enter a command \e[0m\n", 1);
		input = readline("\U0001F63B \U0001F449 ");
		if (input && *input)
			add_history (input);
		if (ft_strncmp(input, "exit", 4) == 0)
            exit(1);
		else
		{
			blocks = ft_parsing_split(input, delimiter, &block_count);
			wc = 0;
			while (blocks[wc] != NULL)
				wc++;
            printf("Word count is %d\n", wc);
            i = 0;
			while (i < block_count)
			{
				printf("Block %d: %s\n", i, blocks[i]);
				i++;
			}
            init_lst(blocks);
		}
	}
	return (0);
}
