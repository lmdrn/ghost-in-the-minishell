/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:51:26 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/26 15:13:04 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *input)
{
    if (ft_strcmp(input, "cd") == 0)
    {
        /* custom_cd(); */
        return (1);
    }
    if (ft_strcmp(input, "pwd") == 0)
    {
        /* custom_pwd(); */
        return (1);
    }
    if (ft_strcmp(input, "env") == 0)
    {
        /* custom_env(); */
        return (1);
    }
    if (ft_strcmp(input, "echo") == 0)
    {
        /* custom_echo(); */
        return (1);
    }
    if (ft_strcmp(input, "export") == 0)
    {
        /* custom_export(); */
        return (1);
    }
    if (ft_strcmp(input, "unset") == 0)
    {
        /* custom_unset(); */
        return (1);
    }
    if (ft_strcmp(input, "alias") == 0)
    {
        /* custom_alias(); */
        return (1);
    }
    if (ft_strcmp(input, "exit") == 0)
    {
        custom_exit();
        return (1);
    }
    else
        return (0);
}    
