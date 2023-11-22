/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:21:41 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/22 16:56:06 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if NOT Child
// change stdout to pipe[1] (dup2(p[1], 1))
// close p[0]
// execute CMD -> probably ERROR here
// ELSE  inside CHILD
// dup2(p[0], 0);
// close(p[1]);
// execute 2nd command -> probably ERROR here
// close p[0]
//
//
// find out how to dynamically get to the next command
// find out if path and args in execve are properly dealt with
