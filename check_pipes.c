/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:44:25 by lmedrano          #+#    #+#             */
/*   Updated: 2023/10/04 15:03:04 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    is_odd_or_even(int *pipe_count, int *cmd_count)
{
    if ((*pipe_count % 2 != 0) && (*cmd_count % 2 == 0)) 
        printf("pipex shit should happen here\n");
    else if (*pipe_count == 0 && *cmd_count == 1)
            printf("execve shit should happen here\n");
    else if ((*pipe_count % 2 == 0) && (*cmd_count % 2 == 0))
    {
        printf("Error: Not enough cmds for pipe nbrs\n");
        exit(1);
    }

}

void    send_to_execution(int *pipe_count, int *cmd_count)
{
    is_odd_or_even(pipe_count, cmd_count);
}
