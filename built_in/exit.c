/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:25:44 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/29 22:12:43 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_min_max(char *arg)
{
	int	out_of_range;

	out_of_range = 0;
	if (ft_atol(arg, &g_status) == 0)
	{
		if (g_status < 0 || g_status > 255)
		{
			out_of_range = 1;
			printf("Error: Numeric value is out of range.\n");
		}
	}
	else
		out_of_range = 1;
	return (out_of_range);
}

void	ft_check_numeric(char *arg, int i, int *error_flag)
{
	if (arg[i] == '-')
		i++;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			printf("Error: Exit code should be a numeric value.\n");
			*error_flag = 1;
			return ;
		}
		i++;
	}
}

void	builtin_exit(char *input)
{
	char	*arg;
	int		i;
	int		out_of_range;
	int		error_flag;

	i = 0;
	out_of_range = 0;
	error_flag = 0;
	if (ft_strcmp(input, "exit") == 0)
		exit_error(input);
	else if (ft_strncmp(input, "exit ", 5) == 0)
	{
		arg = input + 5;
		ft_check_numeric(arg, i, &error_flag);
		if (!error_flag)
			out_of_range = check_min_max(arg);
	}
	if (!out_of_range && !error_flag)
	{
		printf("Exiting ghost in the minishell with code %d\n", g_status);
		exit(g_status);
	}
}