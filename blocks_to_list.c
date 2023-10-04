/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:13:54 by lmedrano          #+#    #+#             */
/*   Updated: 2023/10/04 13:39:19 by lmedrano         ###   ########.fr       */
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
    if (node->text == NULL)
    {
        ft_putendl_fd("dup failed\n", 1);
        return (NULL);
    }
    node->next = NULL;
    return (node);
}

char		*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
		dst[i] = '\0';
	}
	return (dst);
}

char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (dest[i] != '\0')
		++i;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		++j;
	}
	dest[i] = '\0';
	return (dest);
}

//fct x step 3 of is_executable_command()
char    *concat_str(char *s1, char *s2)
{
    int len1;
    int len2;
    char    *res;
    
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    res = malloc(len1 + len2 + 1);
    if (res == NULL)
    {
        printf("Malloc failed\n");
        return (NULL);
    }
    ft_strcpy(res, s1);
    ft_strcat(res, s2);
    return (res);
}

//fct that search in path if command exists and can be executed with execve
//1. get path
//2. split path with :
//3. take each block and add command name to it
//4. go to location and see it exists + is executable
int is_executable_command(char *node)
{
    char    *path_env;
    char    **dirs;
    char    *full_path;
    char    *tmp;
    int     i;
    int     j;
    int     dir_count;

    (void)node;
    path_env = getenv("PATH");
    if (path_env == NULL)
    {
        printf("Path not found\n");
        return (1);
    }
    else
        printf("Path is : %s\n", path_env);
    dirs = ft_split(path_env, ':');
    if (dirs == NULL)
        printf("Split did not work\n");
    // -- test section start --
    i = 0;
    while (dirs[i] != NULL)
    {
        printf("Dir %d is: %s\n", i, dirs[i]);
        i++;
    }
    dir_count = i;
    i = 0;
    while(i < dir_count)
    {
        full_path = concat_str(dirs[i], "/");
        if (full_path == NULL)
        {
            j = 0;
            while (j < dir_count)
            {
                free(dirs[j]);
                j++;
            }
            free(dirs);
            return (1);
        }
        tmp = concat_str(full_path, node);
        free(full_path);
        if (tmp == NULL)
        {
            j = 0;
            while (j < dir_count)
            {
                free(dirs[j]);
                j++;
            }
            free(dirs);
            return (1);
        }
        full_path = tmp;
        printf("full path is: %s\n", full_path);
        if (access(full_path, F_OK) == 0)
        {
            if (access(full_path, X_OK) == 0)
            {
                j = 0;
                while (j < dir_count)
                {
                    free(dirs[j]);
                    j++;
                }
                free(dirs);
                free(tmp);
                printf("%s exists and is executable\n", node);
                return (0);
            }
        }
        free(full_path);
        i++;
    }

    i = 0;
    while (i < dir_count)
    {
        free(dirs[i]);
        i++;
    }
    free(dirs);
    // -- test section end --
    ft_putendl_fd("CMD does NOT exist OR is NOT executable", 1);
    return (1);
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

//fct that checks if input is a symbol
int is_asym(char *node)
{
    if (ft_strncmp(node, "|", 1) == 0)
        return(0);
    else if (ft_strncmp(node, ">>", 2) == 0)
        return(0);
    else if (ft_strncmp(node, "<<", 2) == 0)
        return(0);
    else if (ft_strncmp(node, ">", 1) == 0)
        return(0);
    else if (ft_strncmp(node, "<", 1) == 0)
        return(0);
    else
        return(1);

}

//fct that assigns type to each node
void    assign_types(t_type *node, t_type *lst)
{
    t_type  *next_node;
    if (ft_strncmp(node->text, "|", 1) == 0)
    {
        node->type = is_pipe;
        printf("%s type is: %d\n", node->text, node->type);
        printf("\n");
    }
    else if (ft_strncmp(node->text, ">>", 2) == 0)
    {
        node->type = dbl_ch_d;
        printf("%s type is: %d\n", node->text, node->type);
        printf("\n");
        next_node = lst;
        while (next_node != NULL) {
            if (next_node == node)
                break;
            next_node = next_node->next;
        }
        if (next_node != NULL && next_node->next != NULL) {
            next_node = next_node->next;
            next_node->type = fileout;
            printf("%s type is: %d\n", next_node->text, next_node->type);
            printf("\n");
        }
    }
    else if (ft_strncmp(node->text, "<<", 2) == 0)
    {
        node->type = dbl_ch_g;
        printf("%s type is: %d\n", node->text, node->type);
        printf("\n");
        next_node = lst;
        while (next_node != NULL) {
            if (next_node == node)
                break;
            next_node = next_node->next;
        }
        if (next_node != NULL && next_node->next != NULL) {
            next_node = next_node->next;
            next_node->type = delimiter;
            printf("%s type is: %d\n", next_node->text, next_node->type);
            printf("\n");
        }
    }
    else if (ft_strncmp(node->text, ">", 1) == 0)
    {
        node->type = ch_d;
        printf("%s type is: %d\n", node->text, node->type);
        printf("\n");
        next_node = lst;
        while (next_node != NULL) {
            if (next_node == node)
                break;
            next_node = next_node->next;
        }
        if (next_node != NULL && next_node->next != NULL) {
            next_node = next_node->next;
            next_node->type = fileout;
            printf("%s type is: %d\n", next_node->text, next_node->type);
        }
    }
    else if (ft_strncmp(node->text, "<", 1) == 0)
    {
        node->type = ch_g;
        printf("type is: %d\n", node->type);
        printf("\n");
        next_node = lst;
        while (next_node != NULL) {
            if (next_node == node)
                break;
            next_node = next_node->next;
        }
        if (next_node != NULL && next_node->next != NULL) {
            next_node = next_node->next;
            next_node->type = filein;
            printf(" %s type is: %d\n", next_node->text, next_node->type);
            printf("\n");
        }
    }
    else if (is_executable_command(node->text) == 0)
    {
        node->type = cmd;
        printf("%s type is: %d\n", node->text, node->type);
        printf("\n");
    }
    else if (is_builtin(node->text) == 0)
    {
        node->type = builtin;
        printf("%s type is: %d\n", node->text, node->type);
        printf("\n");
    }
    else
    {
        node->type = args;
        printf("%s type is: %d\n", node->text, node->type);
        printf("\n");
    }
}

//fct that takes blocks from split and transforms each block into nodes by calling create_node
//then iterates through list again to assign a type to each node
t_type    *init_lst(char **blocks, t_type *node)
{
    t_type  *head;
    t_type  *current;
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
        assign_types(print, head);
        print = print->next;
    }
    //free nodes
    /* print = head; */
    while (print != NULL)
    {
        tmp = print;
        print = print->next;
        free(tmp->text);
        free(tmp);
    }
    /* free(blocks); */
    return (head);
}
