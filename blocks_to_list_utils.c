/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:08:28 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/20 19:10:43 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*full_path_check(char **dirs, int i, char *node)
{
	char	*full_path;

	full_path = get_full_path(dirs[i], node);
	if (!full_path)
	{
		free_string_array(dirs);
		return (NULL);
	}
	return (full_path);
}
