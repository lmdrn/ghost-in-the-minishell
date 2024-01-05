/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 21:11:59 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 23:03:08 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_and_check_executable(t_commande *cmd, t_environment *env_copy)
{
	char	*full_path;

	full_path = find_executable_path(cmd->cmd, env_copy);
	if (!full_path)
		ft_error(cmd->cmd);
	return (full_path);
}

char	**build_and_check_arguments(t_commande *cmd, char *full_path)
{
	char	**argv;

	argv = build_arg(cmd, full_path);
	if (!argv)
	{
		printf("Malloc error\n");
		return (NULL);
	}
	return (argv);
}

void	execute_command(t_commande *cmd, t_environment *env_copy)
{
	char	*full_path;
	char	**argv;
	char	**envp;

	full_path = find_and_check_executable(cmd, env_copy);
	if (!full_path)
		return ;
	argv = build_and_check_arguments(cmd, full_path);
	if (!argv)
	{
		free(full_path);
		return ;
	}
	envp = env_list_to_array(env_copy);
	execve(full_path, argv, envp);
	g_status = errno;
	free_argv(argv);
}

char	*find_exec_access(t_epi *epi, char *cmd)
{
	epi->seg = segment_malloc_copy(epi->seg, epi->tok_s, epi->tok_e);
	epi->cmd_path = concat_path_cmd(epi->seg, cmd);
	free(epi->seg);
	if (access(epi->cmd_path, F_OK) == 0
		|| access(epi->cmd_path, X_OK) == 0)
	{
		free(epi->path);
		return (epi->cmd_path);
	}
	epi->tok_s = epi->tok_e + 1;
	return (NULL);
}