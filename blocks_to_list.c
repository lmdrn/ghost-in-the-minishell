/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:13:54 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/30 18:18:56 by lmedrano         ###   ########.fr       */
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
char	*ft_strcpy(char *dest, const char *src)
{
	unsigned int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}

char    *ft_strcat(char *dst, char *src)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (dst[i] != '\0')
        i++;
    while (src[j] != '\0')
    {
        dst[i + j] = src[j];
        j++;
    }
    dst[i + j] = '\0';
    return (dst);
}

char    *concat_str(char *s1, char *s2)
{
    size_t  len1;
    size_t  len2;
    char    *res;

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    res = malloc(sizeof(len1 + len2 + 2));
    if (res == NULL)
    {
        perror("malloc failed\n");
        return (NULL);
    }
    ft_strcpy(res, s1);
    if (s1[len1 - 1] != '/')
        ft_strcat(res, s2);
    return (res);
}
//fct that search in path if command exists and can be executed with execve
char *is_executable_command(char *node)
{
    char    *path_env;
    char    path_cpy[1024];
    char    *dir;
    char    *delimiter;
    char    *full_path;
    int     len;

    len = 0;
    path_env = getenv("PATH");
    if (path_env == NULL)
    {
        ft_putendl_fd("PATH environment variable not found.\n", 1);
        return (NULL);    
    }
    ft_strcpy(path_cpy, path_env);
    path_cpy[len - 1] = '\0';
    dir = path_cpy;
    while (*dir != '\0') 
    {
        delimiter = ft_strchr(dir, ':');
        if (delimiter != NULL)
            *delimiter = '\0';
        full_path = concat_str(dir, node);
        if (full_path == NULL)
            return (NULL);
        if (access(full_path, F_OK) == 0)
        {
            if (access(full_path, X_OK) == 0)
                return (full_path);
        }
        if (delimiter != NULL)
        {
            *delimiter = ':';
            dir = delimiter + 1;
        }
        else
            break ;
        free(full_path);
    }
    return (NULL);
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
    t_type  *next_node;

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
    else if (is_executable_command(node->text) == NULL)
    {
        node->type = cmd;
        printf("type is: %d\n", node->type);
        if (is_asym(node->text) != 0)
        {
            next_node = node->next;
            if (next_node != NULL)
                next_node->type = args;
            else
                printf("error no next node\n");
        }
    }
    else if (is_builtin(node->text) == 0)
    {
        node->type = builtin;
        printf("type is: %d\n", node->type);
        if (is_asym(node->text) != 0)
        {
            next_node = node->next;
            if (next_node != NULL)
                next_node->type = args;
            else
                printf("error no next node\n");
        }
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
