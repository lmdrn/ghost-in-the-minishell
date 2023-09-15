/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:28:24 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/15 15:49:05 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	blocks_into_types(char **blocks, int wc)
{
	t_type	*types;
	int		i;

	i = 0;
	types = malloc(sizeof(t_type) * wc);
	if (!types)
	{
		printf("mem alloc failed\n");
		exit(1);
	}
	while (i < wc)
	{
		types[i].text = blocks[i];
		if (ft_strcmp(blocks[i], "|") == 0)
			types[i].pipe = 1;
		else
			types[i].pipe = 0;
		printf("Pipe: %d\n", types[i].pipe);
		if (ft_strcmp(blocks[i], ">") == 0)
			types[i].chevron_d = 1;
		else
			types[i].chevron_d = 0;
		printf("Chevron Gauche: %d\n", types[i].chevron_g);
		if (ft_strcmp(blocks[i], "<") == 0)
			types[i].chevron_g = 1;
		else
			types[i].chevron_g = 0;
		printf("Chevron Droite: %d\n", types[i].chevron_d);
		if (ft_strcmp(blocks[i], ">>") == 0)
			types[i].dbl_chev_d = 1;
		else
			types[i].dbl_chev_d = 0;
		printf("Double Chevron Droit: %d\n", types[i].dbl_chev_d);
		if (ft_strcmp(blocks[i], "<<") == 0)
			types[i].dbl_chev_g = 1;
		else
			types[i].dbl_chev_g = 0;
		printf("Double Chevron Gauche: %d\n", types[i].dbl_chev_g);
		i++;
	}
	free(types);
}
