/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:37:28 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/15 14:42:14 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_welcome(void)
{
	ft_putendl_fd("\033[0;34mWelcome to ghost in the minishell!\n", 1);
	ft_putendl_fd("Please enter a command \e[0m\n", 1);
}

char	*ft_prompt(void)
{
	char	*input;

	input = readline("\n\U0001F63B \U0001F449 ");
    // Readline setup
    /* rl_bind_key('\t', rl_insert);  = 0; */
	return (input);
}
