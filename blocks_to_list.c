/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:13:54 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/26 20:19:02 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//fct to create node + copy txt into

struct  s_type  *create_node(const char *block)
{
    t_type  *node;

    node = malloc(sizeof(t_type));
    if (node == NULL)
    {
        ft_putendl_fd("malloc failed\n", 1);
        return (NULL);
    }
    node->text = ft_strdup(block); 
    assign_types(node);
    if (node->text == NULL)
    {
        ft_putendl_fd("dup failed\n", 1);
        return (NULL);
    }
    node->next = NULL;
    return (node);
}

//fct that assigns type to create_node()
void    assign_types(t_type *node)
{
    if (ft_strncmp(node->text, "|", 1) == 0)
    {
        node->type = is_pipe;
        /* printf("type is: %d\n", node->type); */
    }
    else if (ft_strncmp(node->text, ">", 1) == 0)
        node->type = ch_d;
    else if (ft_strncmp(node->text, "<", 1) == 0)
        node->type = ch_g;
    else if (ft_strncmp(node->text, ">>", 1) == 0)
        node->type = dbl_ch_d;
    else if (ft_strncmp(node->text, "<<", 1) == 0)
        node->type = dbl_ch_g;
    else
    {
        node->type = word;
        /* printf("type is: %d\n", node->type); */
    }
}

//fct that takes blocks from split and transforms each block into nodes by calling create_node
int    init_lst(char **blocks)
{
    t_type  *head;
    t_type  *current;
    t_type  *node;
    t_type  *print;
    t_type  *tmp;
    int     wc;
    int     i;

    head = NULL;
    current = NULL;
    i = 0;
    wc = 0;
    while (blocks[wc] != NULL)
        wc++;
    while (i < wc)
    {
        node = create_node(blocks[i]);
        if (head == NULL)
        {
            head = node;
            current = node;
        }
        else
        {
            current->next = node;
            current = node;
        }
        i++;
    }
    //print nodes
    print = head;
    while (print != NULL)
    {
        printf("node is: %s\n", print->text);
        print = print->next;
    }

    //free nodes
    print = head;
    while (print != NULL)
    {
        tmp = print;
        print = print->next;
        free(tmp->text);
        free(tmp);
    }
    free(blocks);
    return (0);
}
