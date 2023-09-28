/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:21:12 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/28 15:31:35 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// careful do not use printf (or modify later on) could create trouble
// (and we don't want trouble...)

int ctrl_d_pressed = 0;

void    ft_welcome(void)
{
    ft_putendl_fd("\x0b[35mWelcome to ghost in the minishell!\n", 1);
    ft_putendl_fd("Please enter a command \e[0m\n", 1);
}

char    *ft_prompt(void)
{
    char    *input;

    input = readline(NULL);
    return (input);

}

//signal handler for Ctrl+C
void    sigint_handler(int signum)
{
    (void)signum;
    printf("\n\U0001F63B \U0001F449 ");
}

//signal handler for Ctrl+D
void    sigeof_handler(int signum)
{
    (void)signum;
    ctrl_d_pressed = 1;
}

int	main(int ac, char **av, char **envp)
{
	char	**blocks;
	int		i;
	int		wc;
	int		block_count;
	char	delimiter;
    char    *input;

	delimiter = ' ';
    input = NULL;
	(void)ac;
	(void)av;
	(void)envp;

    // Install signal handlers
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);      // Ctrl+\ (ignore)
    free(input);
    ft_welcome();
	while (ctrl_d_pressed == 0)
	{
        printf("\U0001F63B \U0001F449 ");
        input = ft_prompt();
        if (input && *input)
            add_history (input);               
        if (input == NULL)
        {
            printf("Exiting shell...\n"); 
            free(input);
            break ;
        }
        if (ft_strncmp(input, "exit", 4) == 0)
        {
            free(input);
            break ;
        }
        else
        {
			blocks = ft_parsing_split(input, delimiter, &block_count);
            free(input);
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
            init_lst(blocks);
		}
	}
	return (0);
}
