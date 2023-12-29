/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:25:44 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/29 16:02:40 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_min_max(char *arg)
{
	g_status = ft_atoi(arg);
	if (g_status < INT_MIN || g_status > INT_MAX)
	{
		printf("Error: Exit code is out of range.\n");
		return ;
	}
}

void	builtin_exit(char *input)
{
	char	*arg;
	int		i;

	i = 0;
	if (ft_strcmp(input, "exit") == 0)
	{
		printf("Exiting ghost in the minishell.....\n");
		free(input);
		exit(g_status);
	}
	else if (ft_strncmp(input, "exit ", 5) == 0)
	{
		arg = input + 5;
		while (arg[i] != '\0')
		{
			if (arg[i] < '0' || arg[i] > '9')
			{
				printf("Error: Exit code should be a numeric value.\n");
				return ;
			}
			i++;
		}
		check_min_max(arg);
	}
	printf("Exiting ghost in the minishell with code %d\n", g_status);
	exit(g_status);
}
