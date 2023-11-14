/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:36:37 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/14 15:38:29 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//signal handler for Ctrl+C
void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handling_signals(char *input)
{
    // Install signal handlers
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);// Ctrl+\ (ignore)
	free(input);
}
