/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:13:54 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/30 16:22:27 by lmedrano         ###   ########.fr       */
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

//fct that search in path if command exists and can be executed with execve
int is_executable_command(char *node)
{
    if(access(node, X_OK) == 0)
    {
        printf("The command '%s' exists and is executable.\n", node);
        return (0);
    }
    else
    {
        printf("The command '%s' does not exist and is not executable.\n", node);
        return (1);
    }
}

//fct that compares if input is equal to builtin 
int is_builtin(char *node)
{
    if (ft_strncmp(node, "echo", 4) == 0)
        return (0);
    if (ft_strncmp(node, "pwd", 3) == 0)
        return (0);
    if (ft_strncmp(node, "cd", 2) == 0)
        return (0);
    if (ft_strncmp(node, "export", 6) == 0)
        return (0);
    if (ft_strncmp(node, "unset", 5) == 0)
        return (0);
    if (ft_strncmp(node, "env", 3) == 0)
        return (0);
    if (ft_strncmp(node, "exit", 4) == 0)
        return (0);
    else
        return (1);
}

int is_asym(char *node)
{
    if (ft_strncmp(node, "|", 1) == 0)
        return(0);
    if (ft_strncmp(node, ">", 1) == 0)
        return(0);
    if (ft_strncmp(node, "<", 1) == 0)
        return(0);
    if (ft_strncmp(node, ">>", 1) == 0)
        return(0);
    if (ft_strncmp(node, "<<", 1) == 0)
        return(0);
    else
        return(1);

}

//fct that assigns type to create_node()
void    assign_types(t_type *node)
{
    if (ft_strncmp(node->text, "|", 1) == 0)
    {
        node->type = is_pipe;
        printf("type is: %d\n", node->type);
    }
    else if (ft_strncmp(node->text, ">", 1) == 0)
    {
        node->type = ch_d;
        printf("type is: %d\n", node->type);
    }
    else if (ft_strncmp(node->text, "<", 1) == 0)
    {
        node->type = ch_g;
        printf("type is: %d\n", node->type);
    }
    else if (ft_strncmp(node->text, ">>", 1) == 0)
    {
        node->type = dbl_ch_d;
        printf("type is: %d\n", node->type);
    }
    else if (ft_strncmp(node->text, "<<", 1) == 0)
    {
        node->type = dbl_ch_g;
        printf("type is: %d\n", node->type);
    }
    else if (is_executable_command(node->text) == 0)
    {
        node->type = cmd;
        printf("type is: %d\n", node->type);
        /* if (is_asym(node->text) != -1) */
        /*     node->type->next = args; */
        //ici check si le next c'est un args
    }
    else if (is_builtin(node->text) == 0)
    {
        node->type = builtin;
        printf("type is: %d\n", node->type);
    }
    else
    {
        //other
        printf("type is nothing\n");
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
