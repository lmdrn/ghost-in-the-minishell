/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:35:50 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 21:54:50 by lmedrano         ###   ########.fr       */
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

t_environment	*while_logic(int count, char **envp)
{
	t_environment	*new_ptr;
	t_environment	*head;
	t_environment	*curr;
	int				i;

	i = 0;
	curr = NULL;
	head = NULL;
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

t_environment	*init_env(char **envp)
{
	t_environment	*head;
	t_environment	*curr;
	int				count;

	count = env_count_array(envp);
	if (count == 0 || !envp)
		return (NULL);
	head = NULL;
	head = while_logic(count, envp);
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
	i = 0;
	while (i < block_count)
		i++;
	return (blocks);
}

// Function to create list, assign type to each node(tokenizer)
// Then create cmd block (cmd +  args)
//and send to execution who will treat different types accordingly
int	init_tokenizer(char **blocks, t_environment *env_copy)
{
	t_type		*tokens;
	t_commande	*cmd_lst;
	t_commande	*new_cmd_lst;

	tokens = init_lst(blocks, tokens, env_copy);
	if (tokens == NULL)
		return (1);
	ft_free_parsing_split(blocks);
	cmd_lst = create_cmd_list(tokens, env_copy);
	if (cmd_lst == NULL)
		return (if_cmd_is_null(tokens));
	assign_fds(cmd_lst);
	new_cmd_lst = cmd_lst;
	if (new_cmd_lst->next == NULL && tokens->type == 1)
	{
		if (execute_single_cmd(new_cmd_lst, tokens, env_copy) == -1)
			return (-1);
	}
	else
		if (execution_stuff(new_cmd_lst, tokens, cmd_lst, env_copy) == -1)
			return (-1);
	free_tokens(tokens);
	return (0);
}
