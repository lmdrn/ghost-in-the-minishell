/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:20:21 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/22 20:00:41 by lmedrano         ###   ########.fr       */
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
# include "libft/libft.h"

/* ooo - GLOBAL VARS - ooo */

extern int	g_status;
/*◇───────────────────────────────────────────────────────────────◇*\
*	Macro
\*◇───────────────────────────────────────────────────────────────◇*/
# define ERROR				0
# define SUCCESS			1

/* ooo - ENUMS - ooo */

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

/* ooo - STRUCTURES - ooo */

typedef struct s_bparam {
	int		i;
	int		block_len;
	int		in_sq;
	int		in_dq;
}	t_bparam;

typedef struct s_epi {
	char	*path;
	char	*tok_s;
	char	*tok_e;
	char	*cmd_path;
	char	*seg;
}	t_epi;

typedef struct s_type
{
	char			*text;
	int				type;
	struct s_type	*next;
}	t_type;

typedef struct s_args
{
	char				*arg;
	int					type;
	struct s_args		*next;

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
	int					wait_status;
	t_environment		*env_copy;
	t_type				*tokens;
	struct s_commande	*next;
}	t_commande;

/* ooo - PROTOTYPES DE FONCTIONS - ooo */

/* ooo - absolute_cmd - ooo */

char			**build_absolute_arg(t_commande *cmd);
int				is_absolute_path(char *cmd);
void			execute_absolute_cmd(char **argv, t_commande *cmd);

/* ooo - append - ooo */

int				create_append(char *filename, t_commande *cmd);
void			init_append(t_commande *curr_cmd, t_commande *cmd);

/* ooo - assign_cmd_or_builtin - ooo */

void			assign_exec_cmd(t_type *node);
void			assign_builtin(t_type *node);

void			assign_else(t_type *node);

/* ooo - assign_types - ooo */

void			assign_pipe(t_type *node);
void			assign_dbl_ch_droit(t_type *node, t_type *lst,
					t_type *next_node);
void			assign_dbl_ch_gauche(t_type *node, t_type *lst,
					t_type *next_node);
void			assign_ch_gauche(t_type *node, t_type *lst, t_type *next_node);
void			assign_ch_droit(t_type *node, t_type *lst, t_type *next_node);

/* ooo - blocks_to_list - ooo */

int				is_executable_command(char *node);
int				is_absolute_path(char *cmd);
char			*get_full_path(char *dir, char *node);
int				is_abs_path_executable(char *cmd);

/* ooo - blocks_to_list_utils - ooo */

void			free_string_array(char **array);
char			*full_path_check(char **dirs, int i, char *node);

/* ooo - BUILTINS - ooo */

/* ooo - cd - ooo */

int				ft_cd(t_environment *env_copy, char *path);
int				go_home(t_environment *env_copy, char *home);
char			*get_home(t_environment *head);
int				go_home(t_environment *env_copy, char *home);
int				builtin_cd(t_commande *cmd_lst, t_environment *env_copy);

/* ooo - echo - ooo */

void			ft_echo(char *str, t_environment *env_copy);
int				check_option_n(char *str);
int				echo(t_commande *cmd_lst, t_environment *env_copy);
char			*get_env_value(t_environment *env_copy, char *env_key);

/* ooo - env - ooo */

void			print_env_builtin(t_environment *env_copy);

/* ooo - pwd - ooo */

int				check_args_pwd(t_commande *cmd_lst);
int				builtin_pwd( t_commande *cmd_lst);
void			update_pwd_oldpwd(t_environment *env_copy, char *change_pwd);

/* ooo - built_in_utils  - ooo */

int				check_is_in_env(t_environment *env_copy, char *var);
void			print_value(t_environment *env_copy, char *key);
char			*get_env_value(t_environment *env_copy, char *env_key);
int				check_path(char *path);

/* ooo - copy_env - ooo */

t_environment	*copy_env(char **envp);
void			free_env_struct(t_environment *env_struct);
int				env_count(char **envp);

/* ooo - clean_cmd - ooo */

int				count_word_node(t_type *node);

/* ooo - create_cmd - ooo */

t_commande		*command_list(t_type *tokens, t_environment *env_copy);
int				is_args_or_redir(t_type *current);

/* ooo - create_lst - ooo */

t_type			*init_lst(char **blocks, t_type *node, t_environment *env_copy);

/* ooo - custom_parsing_split - ooo */

int				block_count(char const *str, char c);
char			**ft_parsing_split(const char *input, char c, int *wc);
void			ft_free_parsing_split(char **blocks);
void			ft_last_block(const char *str, char **blocks,
					int bi, int start);

/* ooo - custom_parsing_split_utils - ooo */

int				block_malloc(int i, int start, char **blocks, int block_index);
void			add_last_block(const char *str, char **blocks,
					int block_index, int start);
int				quote_check(int in_dq, int in_sq);

/* ooo - error - ooo */

void			free_argv(char **argv);
int				ft_error(char *str);

/* ooo - execve - oo */

char			*find_executable_path(char *command, t_environment *env_copy);
char			**build_arg(t_commande *cmd, t_environment *env_copy);
int				execute_basic_cmd(t_commande *cmd, t_environment *env_copy);
char			*concat_path_cmd(char *path, char *cmd);
void			create_args(char **argv, t_commande *cmd);

/* ooo - execve_utils - oo */

char			*concat_cmd(char *cmd_path, char *path,
					char *token_start, char *command);
char			*segment_malloc_copy(char *segment, char *token_start,
					char *token_end);
void			copy_the_path(t_environment *env_copy, t_epi *epi);
int				count_args(t_args *args);

/* ooo - expand_variable - ooo */

char			*find_env_variable(t_type *node, char *end_position,
					char *variable);
char			*retrieve_env_variable(char *env_var, t_environment *env);
char			*replace_env_value(t_type *node, char *env_value);

/* ooo - expand_variable utils - ooo */

char			*get_end_pos(char *end_position, char *dollar);
char			*malloc_variable(int var_len);
void			get_current_pos(char *current_pos, char *end_position,
					char *variable, int i);

/* ooo - free_lst - ooo */

void			free_args(t_args *args);
void			free_commande_list(t_commande *head);
void			clear_commande_list(t_commande **lst);
void			print_commande_list(t_commande *head);

/* ooo - heredoc - ooo */
int				heredoc_fd(char	*del);
t_commande		*is_last_cmd(t_commande *cmd);
int				create_heredoc(char *filename, t_commande *cmd);
void			init_heredoc(t_commande *curr_cmd, t_commande *cmd);

/* ooo - init - ooo */

void			init_prompt(char *input);
t_environment	*init_env(char **envp);
int				init_tokenizer(char **blocks, t_environment *env_copy);
char			**init_parse(const char *input);

/* ooo - input_redir - ooo */

int				create_input_redir(char *filename, t_commande *cmd);
void			init_input(t_commande *curr_cmd, t_commande *cmd);

/* ooo - output_redir - ooo */

int				create_output_redir(char *filename, t_commande *cmd);
void			init_output(t_commande *curr_cmd, t_commande *cmd);

/* ooo - prompt - ooo */

void			ft_welcome(void);
char			*ft_prompt(void);

/* ooo - quotes -ooo */

void			assign_quotes(t_type *node, t_environment *env_copy);
char			*clean_cmd_type(t_type *node);
char			*remove_xtra_spaces(char *input);
int				between_quotes(char *str);

/* ooo - redir_utils - ooo */
char			*find_filename(t_commande *cmd);

/* ooo - send_to_builtin_exec - ooo */

void			which_builtin(t_commande *cmd_lst, t_environment *env_copy);

/* ooo - send_to_execution - ooo*/

int				is_odd_or_even(int *pipe_count, int *cmd_count);

/* ooo - send_to_pipes - ooo*/

void			close_fds(t_commande *current_cmd, t_commande *cmd);
void			wait_for_children(t_commande *cmd);
void			send_to_execution(t_commande *cmd, t_environment *env_copy);
void			dup_and_close_fdin(t_commande *curr_cmd);
void			dup_and_close_fdout(t_commande *curr_cmd);

/* ooo - setup_redir - ooo*/
void			assign_fds(t_commande *cmd);
void			assign_redir(t_commande *cmd);
int				which_token(t_commande *cmd, int token);

/* ooo - signals - ooo */

void			sigint_handler(int signum);
void			handling_signals(char *input);

/* ooo - tokenization - ooo */

int				is_builtin(char *input);
void			assign_types(t_type *node, t_type *lst,
					t_environment *env_copy, int command_assigned);

/* ooo - utils - ooo */

char			*ft_strcat(char *dest, char *src);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dest, const char *src, unsigned int n);
char			*concat_str(char *s1, char *s2);

/* ooo - utils_2 - ooo */

int				ft_isspace(char c);
int				ft_strcmp(const char *s1, const char *s2);

#endif
