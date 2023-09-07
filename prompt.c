/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:21:12 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/07 16:02:17 by lmedrano         ###   ########.fr       */
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
		printf("welcome to ghost in the minishell !");
		printf("Please enter a command\n");
		input = readline("$ ");
		if (input && *input)
			add_history (input);
		if (!ft_strncmp(input, "exit", 4))
			exit(1);
		else
		{
			printf("%s\n", input);
			printf("%d\n", word_count(input));
		}
	}
	return (0);
}

//ps -ef | grep 'firefox'

int	word_count(char *str)
{
	int		i;
	int		flag;
	int		wc;
	char	c;

	i = 0;
	flag = 0;
	wc = 0;
	c = ' ';
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && flag < 2)
			wc++;
		while (str[i] && str[i] != c)
		{
			if (str[i] == '\"')
				flag += 1;
			if (flag == 1)
				c = '\"';
			else
				c = ' ';
			i++;
		}
		if (str[i] != '\"')
			flag = 2;
		if (flag == 2)
			flag = 0;
	}
	return (wc);
}
