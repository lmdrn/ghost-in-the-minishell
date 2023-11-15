/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:35:50 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/15 14:41:00 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prompt(char *input)
{
	handling_signals(input);
	ft_welcome();
}

t_environment	*init_env(char **envp)
{
	t_environment	*env_copy;
	int				i;

	env_copy = copy_env(envp);
	i = 0;
	while (env_copy[i].key != NULL)
	{
		/* printf("Key: %s, Value: %s\n", env_copy[i].key, env_copy[i].value); */
		i++;
	}
	return (env_copy);
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
	wc = 0;
	while (blocks[wc] != NULL)
		wc++;
	printf("Word count is %d\n", wc);
	i = 0;
	while (i < block_count)
	{
		printf("Block %d: %s\n", i, blocks[i]);
		i++;
	}
	return (blocks);
}

// Function to create list, assign type to each node(tokenizer)
// Then create cmd block (cmd +  args)
//and send to execution who will treat different types accordingly
void	init_tokenizer(char **blocks, t_environment *env_copy)
{
	t_type		*tokens;
	t_commande	*cmd_lst;
	int			pipe_count;
	int			cmd_count;

	tokens = NULL;
	tokens = init_lst(blocks, tokens, env_copy);
	ft_free_parsing_split(blocks);
	cmd_lst = command_list(tokens, &pipe_count, &cmd_count);
	printf("\nPipe nbr is %d and Cmd nbr is %d\n\n",
		pipe_count, cmd_count);
	if (cmd_lst != NULL)
	{
		printf("Command list:\n");
		print_commande_list(cmd_lst);
	}
	if (is_odd_or_even(&pipe_count, &cmd_count) == 2)
	{
		if (tokens->type == 1)
			which_builtin(cmd_lst);
		else if (tokens->type == 0)
			duplicate_process(cmd_lst, env_copy);
	}
	/* free_commande_list(cmd_lst); */
	clear_commande_list(&cmd_lst);
	/* free_env_struct(env_copy); */
}