/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:20:21 by lmedrano          #+#    #+#             */
/*   Updated: 2023/11/27 16:56:45 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"

/*----- Macro -----*/
extern int	g_status;
# define ERROR 1
# define SUCCESS 0

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

typedef struct s_environment
{
	char					*key;
	char					*value;
	struct s_environment	*next;
}	t_environment;

typedef struct s_commande
{
	char				*cmd;
	t_args				*args;
	int					fdin;
	int					fdout;
	pid_t				pid;
	t_environment		*env_copy;
	struct s_commande	*next;
}	t_commande;

/* ooo - proto - ooo */

int				ft_strcmp(char *s1, char *s2);
int				check_quotes(char const *str);
int				word_count(char const *str);
void			ft_free(char **tab, int j);
int				is_whitespace(char c);
int				is_quote(char c);
int				ft_error(char *str);
int				block_count(char const *str, char c);
void			ft_blocks(char *s, char c, char **block, int i);
char			**ft_parsing_split(const char *input, char c, int *wc);
char			**init_parse(const char *input);
void			blocks_into_types(char **blocks, int wc);
t_environment	*copy_env(char **envp);
void			free_env(char **env);
void			custom_exit(void);
t_type			*commands_into_blocks(t_type *node, t_type *commands);
int				is_builtin(char *input);
t_type			*init_lst(char **blocks, t_type *node, t_environment *env_copy);
void			assign_types(t_type *node, t_type *lst,
					t_environment *env_copy);
void			assign_pipe(t_type *node);
void			assign_dbl_ch_droit(t_type *node, t_type *lst,
					t_type *next_node);
void			assign_dbl_ch_gauche(t_type *node, t_type *lst,
					t_type *next_node);
void			assign_ch_gauche(t_type *node, t_type *lst, t_type *next_node);
void			assign_ch_droit(t_type *node, t_type *lst, t_type *next_node);
void			assign_exec_cmd(t_type *node);
void			assign_builtin(t_type *node);
void			assign_else(t_type *node);
void			ft_welcome(void);
char			*ft_prompt(void);
void			sigint_handler(int signum);
void			sigeof_handler(int signum);
t_commande		*command_list(t_type *tokens, int *pipe_count, int *cmd_count,
					t_environment *env_copy);
void			free_commande_list(t_commande *head);
void			free_args(t_args *args);
void			print_commande_list(t_commande *head);
void			ft_free_parsing_split(char **blocks);
int				execute_basic_cmd(t_commande *cmd, t_environment *env_copy);
char			*ft_strcat(char *dest, char *src);
char			*ft_strcpy(char *dst, const char *src);
int				is_executable_command(char *node);
char			*ft_strncpy(char *dest, const char *src, unsigned int n);
char			*concat_str(char *s1, char *s2);
void			free_argv(char **argv);
int				ft_error(char *str);
void			which_builtin(t_commande *cmd_lst, t_environment *env_copy);
void			handling_signals(char *input);
void			assign_quotes(t_type *node, t_environment *env_copy);
t_type			*clean_cmd_type(t_type *node);
int				ft_isspace(char c);
char			*remove_xtra_spaces(char *input);
int				between_quotes(char *str);
char			*find_env_variable(t_type *node);
char			*retrieve_env_variable(char *env_var, t_environment *env);
char			*replace_env_value(t_type *node, char *env_value);
void			free_env_struct(t_environment *env_struct);
int				ft_strcmp(char *s1, char *s2);
int				is_odd_or_even(int *pipe_count, int *cmd_count);
void			duplicate_process(t_commande *cmd_lst, t_environment *env_copy);
void			init_tokenizer(char **blocks, t_environment *env_copy);
void			init_prompt(char *input);
t_environment	*init_env(char **envp);
void			clear_commande_list(t_commande **lst);
void			send_to_pipes(t_environment *env_copy, t_commande *cmd_lst);
char			*find_executable_path(char *command, t_environment *env_copy);
char			**build_arg(t_commande *cmd, t_environment *env_copy);
int				create_pipes(t_commande *cmd, t_environment *env_copy, int cmd_count);
void			execute_pipeline(t_commande *cmd_lst, t_environment *env_copy);
char			*find_cmd_path(t_commande *cmd_lst, t_environment *env_copy);
char			**find_cmd_args(t_commande *cmd_lst, t_environment *env_copy);
char			**env_list_to_array(t_environment *env_copy);
void			close_fds(t_commande *cmd);
/*-------------cd-----------------------------*/
int				ft_cd(t_environment *env_copy, char *path);
void			add_node_at_end(t_environment *head, char *key, char *value);
int				go_home(t_environment *env_copy, char *home);
char			*get_home(t_environment *head);
t_environment	*last_node(t_environment *head);
int				check_is_in_env(t_environment *env_copy, char *var);
int				check_path(char *path);
//int static		check_args_cd(t_commande *cmd_lst);
void			update_pwd_oldpwd(t_environment *env_copy, char *change_pwd);
int				go_home(t_environment *env_copy, char *home);
int				builtin_cd(t_commande *cmd_lst, t_environment *env_copy);
char			*print_value(t_environment    *env_copy, char *key);
/* -------------------pwd-----------------------------*/
int check_args(t_commande *cmd_lst);
int builtin_pwd(t_commande *cmd_lst);
/* -------------------env-----------------------------*/
void print_env_builtin(t_environment  *env_copy);
/* -------------------echo-----------------------------*/
void	ft_echo(char *str, t_environment *env_copy);
int 	check_option_n(char *str);
int		echo(t_commande *cmd_lst, t_environment *env_copy);
#endif
