/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:20:21 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/13 12:45:53 by lmedrano         ###   ########.fr       */
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
# include "libft.h"

extern int	g_status;

/* ooo - enums - ooo */

enum e_types {
	cmd,
	builtin,
	args,
	flags,
	filein,
	fileout,
	delimiter,
	is_pipe,
	ch_g,
	ch_d,
	dbl_ch_g,
	dbl_ch_d,
	dbl_q,
	s_q
};

typedef struct s_type
{
	char			*text;
	int				type;
	struct s_type	*next;
}	t_type;

typedef struct s_args
{
	char			*arg;
	struct s_args	*next;

}	t_args;

typedef struct s_commande
{
	char				*cmd;
	t_args				*args;
	char				*fdin;
	char				*fdout;
	struct s_commande	*next;
}	t_commande;

/* ooo - proto - ooo */

int			ft_strcmp(char *s1, char *s2);
int			check_quotes(char const *str);
int			word_count(char const *str);
void		ft_free(char **tab, int j);
int			is_whitespace(char c);
int			is_quote(char c);
int			ft_error(char *str);
int			block_count(char const *str, char c);
void		ft_blocks(char *s, char c, char **block, int i);
char		**ft_parsing_split(const char *input, char c, int *wc);
void		blocks_into_types(char **blocks, int wc);
char		**copy_env(char **envp);
void		free_env(char **env);
void		custom_exit(void);
t_type		*commands_into_blocks(t_type *node, t_type *commands);
int			is_builtin(char *input);
t_type		*init_lst(char **blocks, t_type *node);
void		assign_types(t_type *node, t_type *lst);
void		assign_pipe(t_type *node);
void		assign_dbl_ch_droit(t_type *node, t_type *lst, t_type *next_node);
void		assign_dbl_ch_gauche(t_type *node, t_type *lst, t_type *next_node);
void		assign_ch_gauche(t_type *node, t_type *lst, t_type *next_node);
void		assign_ch_droit(t_type *node, t_type *lst, t_type *next_node);
void		assign_exec_cmd(t_type *node);
void		assign_builtin(t_type *node);
void		assign_else(t_type *node);
void		ft_welcome(void);
char		*ft_prompt(void);
void		sigint_handler(int signum);
void		sigeof_handler(int signum);
t_commande	*command_list(t_type *tokens, char del,
				int *pipe_count, int *cmd_count);
void		free_commande_list(t_commande *head);
void		free_args(t_args *args);
void		print_commande_list(t_commande *head);
void		ft_free_parsing_split(char **blocks);
void		send_to_execution(int *pipe_count, int *cmd_count,
				t_commande *cmd_lst, t_type *tokens);
int			execute_basic_cmd(t_commande *cmd);
char		*ft_strcat(char *dest, char *src);
char		*ft_strcpy(char *dst, const char *src);
int			is_executable_command(char *node);
char		*ft_strncpy(char *dest, const char *src, unsigned int n);
char		*concat_str(char *s1, char *s2);
void		free_argv(char **argv);
int			ft_error(char *str);
void		which_builtin(t_commande *cmd_lst);
void		handling_signals(char *input);
void		assign_quotes(t_type *node);
t_type		*clean_cmd_type(t_type *node);
int			ft_isspace(char c);
char		*remove_xtra_spaces(char *input);
int			between_quotes(char *str);
char		*find_env_variable(t_type *node);
char		*retrieve_env_variable(char *env_var);

#endif
