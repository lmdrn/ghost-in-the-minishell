/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:11:03 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/07 17:13:05 by lmedrano         ###   ########.fr       */
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
