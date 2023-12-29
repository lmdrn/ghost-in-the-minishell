/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 22:07:39 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/29 22:08:41 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_sign(const char *str, int sign)
{
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '+')
			sign = 1;
		else
			sign = -1;
	}
	return (sign);
}

void	check_if_neg(int *res, int sign)
{
	if (sign == -1 && *res < 0)
		*res = (*res + 256) % 256;
	else
		*res = (*res + 256) % 256;
}

int	ft_atol(const char *str, int *res)
{
	long	long_nbr;
	int		sign;

	long_nbr = 0;
	sign = 1;
	while (ft_isspace(*str))
			str++;
	sign = count_sign(str, sign);
	while (isdigit(*str) || *str == '-')
	{
		if (*str == '-')
		{
			str++;
			continue ;
		}
		long_nbr = long_nbr * 10 + (*str++ - '0');
		if (long_nbr > INT_MAX || long_nbr < INT_MIN)
		{
			printf("Error: Numeric value is out of range.\n");
			return (-1);
		}
	}
	*res = sign * (int)long_nbr;
	check_if_neg(res, sign);
	return (0);
}
