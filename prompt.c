/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:21:12 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/09 18:12:05 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// careful do not use printf (or modify later on) could create trouble
// (and we don't want trouble...)

int	g_status = 0;

void	ft_welcome(void)
{
	ft_putendl_fd("\033[0;34mWelcome to ghost in the minishell!\n", 1);
	ft_putendl_fd("Please enter a command \e[0m\n", 1);
}

char	*ft_prompt(void)
{
	char	*input;

	input = readline("\n\U0001F63B \U0001F449 ");
	return (input);
}

//signal handler for Ctrl+C
void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handling_signals(char *input)
{
    // Install signal handlers
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);// Ctrl+\ (ignore)
	free(input);
}

int	main(int ac, char **av, char **envp)
{
	char		**blocks;
	int			i;
	int			wc;
	int			block_count;
	int			pipe_count;
	int			cmd_count;
	t_type 		*tokens;
	t_commande	*cmd_lst;
	char		*input;
	char		**env_copy;

	cmd_lst = NULL;
	tokens = NULL;
	input = NULL;
	(void)ac;
	(void)av;
	/* (void)envp; */
	env_copy = copy_env(envp);
	handling_signals(input);
	free_env(env_copy);
	ft_welcome();
	while (1)
	{
		input = ft_prompt();
		if (input == NULL)
		{
			free(input);
			break ;
		}
		if (input && *input)
			add_history (input);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break ;
		}
		else
		{
			if (ft_strncmp(input, "exit", 4) == 0)
			{
				free(input);
				break ;
			}
			input = remove_xtra_spaces(input);
			printf("Cleaned inputs is : %s\n", input);
			blocks = ft_parsing_split(input, ' ', &block_count);
			/* free(input); */
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
			tokens = init_lst(blocks, tokens);
			ft_free_parsing_split(blocks);
			cmd_lst = command_list(tokens, '|', &pipe_count, &cmd_count);
			printf("\nPipe nbr is %d and Cmd nbr is %d\n\n",
				pipe_count, cmd_count);
			if (cmd_lst != NULL)
			{
				printf("Command list:\n");
				print_commande_list(cmd_lst);
				/* free_args(cmd_lst->args); */
			}
			send_to_execution(&pipe_count, &cmd_count, cmd_lst, tokens);
			free_commande_list(cmd_lst);
		}
	}
	return (0);
}
