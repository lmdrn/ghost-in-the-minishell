/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:44:25 by lmedrano          #+#    #+#             */
/*   Updated: 2023/10/05 09:51:59 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    is_odd_or_even(int *pipe_count, int *cmd_count)
{
    if ((*pipe_count % 2 != 0) && (*cmd_count % 2 == 0)) 
    {
        printf("pipex shit should happen here\n");
        return (1);
    }
    else if (!(*pipe_count) && *cmd_count == 1)
    {
        printf("execve shit should happen here\n");
        return (2);
    }
    else if (((*pipe_count % 2 == 0) && (*cmd_count % 2 == 0)) || (*pipe_count % 2 != 0 && *cmd_count % 2 != 0))
    {
        printf("Error: Not enough cmds or pipes\n");
        exit(1);
    }
    return (0);
}

void    send_to_execution(int *pipe_count, int *cmd_count, t_commande *cmd_lst)
{
    if (is_odd_or_even(pipe_count, cmd_count) == 2)
       execute_basic_cmd(cmd_lst); 
}
