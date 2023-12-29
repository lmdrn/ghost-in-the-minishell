/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:11:03 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/29 20:30:55 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argv(char **argv)
{
	if (!argv)
		return ;
	free(argv[0]);
	free(argv);
}

int	ft_error(char *str)
{
	printf("Error: %s is not an executable cmd\n", str);
	return (1);
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
	printf("Exiting ghost in the minishell.....\n");
	free(input);
	exit(g_status);
}
