/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:35:50 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/02 23:08:56 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environment	*new_env_node(char *env)
{
	t_environment	*ptr;
	char			*del;
	int				key;
	int				val;

	ptr = NULL;
	del = ft_strchr(env, '=');
	if (del != NULL)
	{
		key = del - env;
		val = ft_strlen(del + 1);
		ptr = (t_environment *)malloc(sizeof(t_environment));
		ptr->key = (char *)malloc(key + 1);
		ptr->value = (char *) malloc(val + 1);
		if (!ptr || !ptr->key || !ptr->value)
			perror("Failed to allocate a new node\n");
		ft_strncpy(ptr->key, env, key);
		ptr->key[key] = '\0';
		ft_strcpy(ptr->value, del + 1);
		ptr->value[val] = '\0';
	}
	return (ptr);
}

t_environment	*init_env(char **envp)
{
	t_environment	*head;
	t_environment	*curr;
	t_environment	*new_ptr;
	int				count;
	int				i;

	i = 0;
	head = NULL;
	count = env_count_array(envp);
	head = NULL;
	curr = NULL;
	while (i < count)
	{
		new_ptr = new_env_node(envp[i]);
		if (head == NULL)
		{
			head = new_ptr;
			curr = new_ptr;
		}
		else
		{
			curr->next = new_ptr;
			curr = new_ptr;
		}
		i++;
	}
	curr->next = NULL;
	return (head);
}

// Function to initiate parsing to transform input into blocks
// and alos count blocks for testing
char	**init_parse(const char *input)
{
	char	**blocks;
	int		wc;
	int		i;
	int		block_count;

	blocks = ft_parsing_split(input, ' ', &block_count);
	if (blocks == NULL)
	{
		return (NULL);
	}
	wc = 0;
	while (blocks[wc] != NULL)
		wc++;
	/* printf("Word count is %d\n", wc); */
	i = 0;
	while (i < block_count)
	{
		/* printf("Block %d: %s\n", i, blocks[i]); */
		i++;
	}
	return (blocks);
}

// Function to create list, assign type to each node(tokenizer)
// Then create cmd block (cmd +  args)
//and send to execution who will treat different types accordingly
int	init_tokenizer(char **blocks, t_environment *env_copy)
{
	t_type		*tokens;
	t_commande	*cmd_lst;

	tokens = NULL;
	cmd_lst = NULL;
	tokens = init_lst(blocks, tokens, env_copy);
	ft_free_parsing_split(blocks);
	if (tokens->type == 0 || tokens->type == 1 || tokens->type == 14)
	{
		cmd_lst = command_list(tokens, env_copy);
	}
	else if (tokens->type == 8 || tokens->type == 9 || tokens->type == 10
		|| tokens->type == 11)
	{
		cmd_lst = command_list_redir(tokens);
	}
	if (cmd_lst == NULL)
		return (-1);
	/* printf("\nPipe nbr is %d and Cmd nbr is %d\n\n", */
	/* 	pipe_count, cmd_count); */
	if (cmd_lst != NULL)
	{
		/* printf("Command list:\n"); */
		print_commande_list(cmd_lst);
	}
	assign_fds(cmd_lst);
	while (cmd_lst != NULL)
	{
		if (tokens->type == 1)
			which_builtin(cmd_lst, env_copy);
		assign_redir(cmd_lst);
		send_to_execution(cmd_lst, env_copy);
		cmd_lst = cmd_lst->next;
	}
	clear_commande_list(&cmd_lst);
	return (0);
}
