/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 21:11:59 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/30 21:12:45 by lmedrano         ###   ########.fr       */
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

char	**build_and_check_arguments(t_commande *cmd, t_environment *env_copy)
{
	char	**argv;

	argv = build_arg(cmd, env_copy);
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
	argv = build_and_check_arguments(cmd, env_copy);
	if (!argv)
	{
		free(full_path);
		return ;
	}
	envp = env_list_to_array(env_copy);
	execve(full_path, argv, envp);
	g_status = errno;
	free_argv(argv);
	free(full_path);
}