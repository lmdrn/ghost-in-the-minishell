/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:21:12 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/07 10:55:32 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// careful do not use printf (or modify later on) could create trouble
// (and we don't want trouble...)

int	main(int ac, char **av, char **envp)
{
	char	*input;

	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		printf("welcome to ghost in the minishell !");
		printf("Please enter a command\n");
		input = readline("$ ");
		if (input && *input)
			add_history (input);
		if (!ft_strncmp(input, "exit", 4))
			exit(1);
		else
			printf("%s\n", input);
	}
	return (0);
}
