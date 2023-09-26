/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:48:44 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/26 14:54:16 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//will probably have to add free in here at some point ?

void custom_exit(void)
{
    printf("Exiting Ghost in the minishell . . .\n");
    exit(0);
}
