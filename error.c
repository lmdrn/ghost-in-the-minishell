/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:11:03 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 00:22:02 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argv(char **argv)
{
	if (!argv)
		return ;
	free(argv);
}

int	ft_error(char *str)
{
	printf("Error: %s: command not found\n", str);
	g_status = 127;
	return (g_status);
}

void	error_without_exit(int error, char *message, int malloced)
{	
	error = error % 256;
	ft_putendl_fd(message, 2);
	if (malloced == 1)
		free(message);
	g_status = error;
}

void	exit_error(char *input)
{
	printf("exit\n");
	free(input);
	g_status = 2;
	exit(g_status);
}

void	check_args(int ac, char **av)
{
	(void)av;
	if (ac > 1)
	{
		printf("Error: Wrong nbr of args\n");
		exit(1);
	}
}
