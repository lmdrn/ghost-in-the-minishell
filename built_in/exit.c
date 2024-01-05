/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:25:44 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 22:15:29 by lmedrano         ###   ########.fr       */
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

void	ft_check_numeric(char *arg, int *error_flag)
{
	int	i;

	i = 0;
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

void	ft_exit(void)
{
	printf("Exiting ghost in the minishell with code %d\n", g_status);
	exit(g_status);
}

void	builtin_exit(t_commande *lst, int in_exec)
{
	char	*arg;
	int		out_of_range;
	int		error_flag;

	out_of_range = 0;
	error_flag = 0;
	if (in_exec == 1)
	{
		out_of_range = 1;
		error_flag = 1;
	}
	if (lst->args == NULL && in_exec == 0)
		exit_error(lst->cmd);
	else if (lst->args)
	{
		arg = lst->args->arg;
		ft_check_numeric(arg, &error_flag);
		if (!error_flag)
			out_of_range = check_min_max(arg);
	}
	if (!out_of_range && !error_flag)
		ft_exit();
}
