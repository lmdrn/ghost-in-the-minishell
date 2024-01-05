/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:35:50 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/05 20:54:08 by lmedrano         ###   ########.fr       */
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

void	free_tokens(t_type *tokens)
{
	t_type	*tmp;

	while (tokens != NULL)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->text);
		tmp->text = NULL;
		free(tmp);
		tmp = NULL;
	}
	free(tokens);
}

// Function to create list, assign type to each node(tokenizer)
// Then create cmd block (cmd +  args)
//and send to execution who will treat different types accordingly
int	init_tokenizer(char **blocks, t_environment *env_copy)
{
	t_type		*tokens;
	t_commande	*cmd_lst;
	t_commande	*new_cmd_lst;
	int			fd;

	tokens = NULL;
	cmd_lst = NULL;
	tokens = init_lst(blocks, tokens, env_copy);
	if (tokens == NULL)
		return (1);
	ft_free_parsing_split(blocks);
	if (tokens->type == 0 || tokens->type == 1 || tokens->type == 14)
		cmd_lst = command_list(tokens, env_copy);
	else if (tokens->type == 8 || tokens->type == 9 || tokens->type == 10
		|| tokens->type == 11)
		cmd_lst = command_list_redir(tokens);
	if (cmd_lst == NULL)
	{
		if (tokens->type == 8 && tokens->next)
		{
			fd = open(tokens->next->text, O_RDONLY);
			if (fd < 0)
			{
				printf("Error: %s: No such file or directory\n",
					tokens->next->text);
				return (1);
			}
			return (1);
		}
		g_status = 127;
		free_tokens(tokens);
		return (-1);
	}
	// if (cmd_lst != NULL)
	// 	print_commande_list(cmd_lst);
	assign_fds(cmd_lst);
	new_cmd_lst = cmd_lst;
	if (new_cmd_lst->next == NULL && tokens->type == 1)
	{
		if (assign_redir(new_cmd_lst) == -1)
		{
			free_tokens(tokens);
			return (-1);
		}
		which_builtin(new_cmd_lst, env_copy, 0);
	}
	else
	{
		while (new_cmd_lst != NULL)
		{
			if (assign_redir(new_cmd_lst) == -1)
			{
				free_tokens(tokens);
				return (-1);
			}
			send_to_execution(new_cmd_lst, cmd_lst, env_copy);
			new_cmd_lst = new_cmd_lst->next;
		}
		close_fds(cmd_lst);
		wait_for_children(cmd_lst);
		clear_commande_list(&cmd_lst);
	}
	free_tokens(tokens);
	return (0);
}
