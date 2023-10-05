/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:13:54 by lmedrano          #+#    #+#             */
/*   Updated: 2023/10/05 11:41:16 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//fct to create node + copy txt into
struct	s_type	*create_node(const char *block)
{
	t_type	*node;

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

//fct that search in path if command exists and can be executed with execve
//1. get path
//2. split path with :
//3. take each block and add command name to it
//4. go to location and see it exists + is executable
int	is_executable_command(char *node)
{
	char	*path_env;
	char	**dirs;
	char	*full_path;
	char	*tmp;
	int		i;
	int		j;
	int		dir_count;

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
		/* printf("Dir %d is: %s\n", i, dirs[i]); */
		i++;
	}
	dir_count = i;
	i = 0;
	while (i < dir_count)
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
		/* printf("full path is: %s\n", full_path); */
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

//fct that takes blocks from split and transforms
//each block into nodes by calling create_node
//then iterates through list again 
//to assign a type to each node
t_type	*init_lst(char **blocks, t_type *node)
{
	t_type	*head;
	t_type	*current;
	t_type	*print;
	t_type	*tmp;
	int		wc;
	int		i;

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
