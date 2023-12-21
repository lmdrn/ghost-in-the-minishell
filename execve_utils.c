/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:13:10 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/21 12:21:42 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_cmd(char *cmd_path, char *path, char *token_start,
		char *command)
{
	cmd_path = concat_path_cmd(token_start, command);
	if (cmd != NULL && access(cmd_path, F_OK) == 0)
	{
		free(path);
		return (cmd_path);
	}
	else
	{
		free(cmd_path);
		return (NULL);
	}
}

char	*segment_malloc_copy(char *segment, char *token_start, char *token_end)
{
	int	segment_len;

	segment_len = token_end - token_start;
	segment = malloc(segment_len + 1);
	if (segment == NULL)
	{
		printf("Malloc failure\n");
		exit(EXIT_FAILURE);
		return (NULL);
	}
	else
	{
		ft_strncpy(segment, token_start, segment_len);
		segment[segment_len] = '\0';
		return (segment);
	}
}

void	copy_the_path(t_environment *env_copy, t_epi *epi)
{
	t_environment	*curr;

	curr = env_copy;
	while (curr->key != NULL && strcmp(curr->key, "PATH") != 0)
		curr = curr->next;
	epi->path = ft_strdup(curr->value);
	epi->tok_s = epi->path;
}

int	count_args(t_args *args)
{
	int	count;

	count = 0;
	while (args != NULL)
	{
		count++;
		args = args->next;
	}
	return (count);
}
