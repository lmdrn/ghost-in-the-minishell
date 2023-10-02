/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:20:21 by lmedrano          #+#    #+#             */
/*   Updated: 2023/10/02 19:29:57 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

/* ooo - enums - ooo */

enum types {
    cmd, //0
    builtin, //1
    args, //2
    flags, //3
    filein, //4
    fileout, //5
    delimiter, //6
    is_pipe, //7
    ch_g, //8
    ch_d, //9
    dbl_ch_g, //10
    dbl_ch_d //11
};

/* ooo - structures - ooo */

typedef struct s_type
{
	char            *text;
    int             type;
    struct s_type   *next;

}	t_type;

typedef struct s_args
{
	char            *arg;
    struct s_args   *next;

}	t_args;

typedef struct s_commande
{
	char	    *cmd;
	t_args *args;
	char	    *fdin;
	char	    *fdout;
    struct s_commande   *next;
}	t_commande;

//execve needs : nom/path/env
//
/* ooo - proto - ooo */

int		ft_strcmp(char *s1, char *s2);
int		check_quotes(char const *str);
int		word_count(char const *str);
void	ft_free(char **tab, int j);
int		is_whitespace(char c);
int		is_quote(char c);
int		ft_error(char *str);
int		block_count(char const *str, char c);
void	ft_blocks(char *s, char c, char **block, int i);
char	**ft_parsing_split(const char *input, char c, int *wc);
void	blocks_into_types(char **blocks, int wc);
int     copy_env(char **envp);
void    custom_exit(void);
t_type  *commands_into_blocks(t_type *node, t_type *commands);
int    is_builtin(char *input);
t_type  *init_lst(char **blocks, t_type *node);
void    assign_types(t_type *node, t_type *lst);
void    ft_welcome(void);
char    *ft_prompt(void);
void    sigint_handler(int signum);
void    sigeof_handler(int signum);
t_commande  *command_list(t_type *tokens, char del);
void    free_commande_list(t_commande *head);
void    free_args(t_args *args);
void    print_commande_list(t_commande *head);

#endif
