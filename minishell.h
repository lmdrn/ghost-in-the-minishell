/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:20:21 by lmedrano          #+#    #+#             */
/*   Updated: 2024/01/06 11:44:14 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include "libft/libft.h"

# define PRINTF_DBG(format, ...) printf("%s : %d: " format, __FILE__, __LINE__, __VA_ARGS__)

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
	s_q,
	abs_cmd
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
	int				flag;
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
void			execute_absolute_cmd(t_commande *cmd, char **envp);
int				is_abs_exec(char *cmd);

/* ooo - append - ooo */

int				create_append(char *filename, t_commande *cmd);
int				init_append(t_commande *curr_cmd, t_commande *cmd);

/* ooo - assign_cmd_or_builtin - ooo */

void			assign_exec_cmd(t_type *node);
void			assign_abs_cmd(t_type *node);
void			assign_builtin(t_type *node);
void			assign_args(t_type *node);
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

int				is_executable_command(char *node, t_environment *env);
int				is_absolute_path(char *cmd);
char			*get_full_path(char *dir, char *node);

/* ooo - blocks_to_list_utils - ooo */

void			free_string_array(char **array);
char			*full_path_check(char **dirs, int i, char *node);

/* ooo - BUILTINS - ooo */

/* ooo - shlvl - ooo */
void			increment_shlvl(t_environment **env_copy);
char			*decrement_and_convert_to_string(const char *str);
int				print_shlvl(t_environment *current);
void			update_env_variable(t_commande *cmd_lst,
					t_environment **env_copy);

/* ooo - unset - ooo */
void			erase_node(char *key, t_environment **env_copy);
int				built_unset(t_environment **env_copy, t_commande *cmd_lst);

/* ooo - export - ooo */
t_environment	*create_node_cpy(t_environment *current);
t_environment	*copy_env_list(t_environment *head);
void			no_arg_so_print(t_environment **env_copy, int nb_args);
int				need_swap(t_environment *a, t_environment *b);
void			swap_nodes(t_environment *a, t_environment *b);
void			bubble_sort_env(t_environment **head);
void			print_sorted_env(t_environment *env_copy);
int				ft_strchrint(char *s, char c);
char			*get_value_export(char *str);
char			*get_key_export(char *str);
int				valid_cmd(char *arg);
int				if_exist_in_env(char *key, t_environment *env_origin);
void			remplace_old_value(char *value, \
				char *key, t_environment *env_copy);
int				fill_env(t_commande *cmd_lst, \
				t_environment **env_copy, int nb_args);
int				count_args_export(t_commande *cmd_lst);
int				export_main(t_commande *cmd_lst, t_environment **env_copy);
int				list_size(t_environment *node);
void			add_node(t_environment **env_copy, char *key, char *value);
void			printCommandList(t_commande *cmdList);
void			print_nodes(t_environment **node, char c);
t_environment	*last_node(t_environment *head);

/* ooo - cd - ooo */

int				ft_cd(t_environment *env_copy, char *path, int path_back);
int				go_home(t_environment *env_copy, char *home);
char			*get_home(t_environment *head);
int				go_home(t_environment *env_copy, char *home);
int				builtin_cd(t_commande *cmd_lst, t_environment *env_copy);
char			*go_back_directories(char *path);
int				is_one_arg(int nb_args, t_commande *cmd_lst);
int				ticket_going_home(t_commande *cmd_lst);
int				count_args_cd(t_commande *cmd_lst);

/* ooo - echo - ooo */

void			ft_echo(char *str, t_commande *cmd,	t_environment *env_copy);
int				check_option_n(char *str);
char			*get_env_value(t_environment *env_copy, char *env_key);
int				handle_option_all_n(t_commande **cmd_lst);
int				check_syntax_and_print(t_commande *cmd_lst);
int				print_arguments(t_commande *cmd_lst, \
				t_environment *env_copy, int option);
int				echo(t_commande *cmd_lst, t_environment *env_copy);

/* ooo - env - ooo */

void			print_env_builtin(t_environment *env_copy, t_commande *cmd_lst);
void			print_environment_variables(t_environment *env_copy);

/* ooo - pwd - ooo */

int				builtin_pwd(void);
void			update_pwd_oldpwd(t_environment *env_copy,
					char *change_pwd, int old_new);

/* ooo - built_in_utils  - ooo */

int				check_is_in_env(t_environment *env_copy, char *var);
void			print_value(t_environment *env_copy, char *key);
char			*get_env_value(t_environment *env_copy, char *env_key);
int				check_path(char *path);
void			print_command_list(t_commande *cmd_list);

/* ooo - copy_env - ooo */

t_environment	*copy_env(char **envp);
void			free_env_struct(t_environment *env_struct);
int				env_count_array(char **envp);
int				env_count_lst(t_environment *env);
char			**env_list_to_array(t_environment *env);
char			**allocate_mem_x_env_array(int count);
void			copy_key_value_pair(t_environment *env, int count, char **envp);

/* ooo - clean_cmd - ooo */

int				count_word_node(t_type *node);

/* ooo - create_cmd - ooo */

t_commande		*command_list(t_type *tokens, t_environment *env_copy);
t_commande		*command_list_redir(t_type *tokens);
int				is_args_or_redir(t_type *current);
int				is_redir(t_type *current);
t_args			*create_new_arg(char *arg, int type);
t_commande		*create_cmd_node(char *name, t_environment *env_copy,
					t_type *tokens);

/* ooo - create_cmd_redir - ooo */
void			append_args_redir(t_args **args, char *arg, int type);
void			update_command_list(t_commande **cmd_head,
					t_commande **cmd_current, t_commande *new_cmd);
void			process_redir_args(t_type *tokens,
					t_commande **cmd_head, t_commande **cmd_current);
t_commande		*command_list_redir(t_type *tokens);

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

/* ooo - dollar - ooo */

char			*replace_exit_status(char *text);

/* ooo - error - ooo */

void			free_argv(char **argv);
int				ft_error(char *str);
void			error_without_exit(int error, char *message, int malloced);
void			exit_error(char *input);

/* ooo - execve - oo */

char			*find_executable_path(char *command, t_environment *env_copy);
char			**build_arg(t_commande *cmd, char *full_path);
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
void			copy_argument(char **argv, int *index, char *arg);

/* ooo - execve_utils_2 - oo */
void			execute_command(t_commande *cmd, t_environment *env_copy);
char			*find_exec_access(t_epi *epi, char *cmd);

/* ooo - exit - ooo */

int				exit_code_master(char *msg, int status, int print);

/* ooo - exit_utils - ooo */

int				ft_atol(const char *str, int *res);

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
int				count_list(t_commande *cmd);

/* ooo - heredoc - ooo */
int				heredoc_fd(char	*del);
t_commande		*is_last_cmd(t_commande *cmd);
int				create_heredoc(char *filename, t_commande *cmd);
int				init_heredoc(t_commande *curr_cmd, t_commande *cmd);

/* ooo - init - ooo */

void			init_prompt(void);
t_environment	*init_env(char **envp);
int				init_tokenizer(char **blocks, t_environment *env_copy);
char			**init_parse(const char *input);
int				if_cmd_is_null(t_type *tokens);
void			free_tokens(t_type *tokens);
t_commande		*create_cmd_list(t_type *tokens, t_environment *env_copy);
int				execution_stuff(t_commande *new_cmd_lst, t_type *tokens,
					t_commande *cmd_lst, t_environment *env_copy);
int				execute_single_cmd(t_commande *new_cmd_lst, t_type *tokens,
					t_environment *env_copy);

/* ooo - input_redir - ooo */

int				create_input_redir(char *filename, t_commande *cmd);
int				init_input(t_commande *curr_cmd, t_commande *cmd);

/* ooo - minishell - ooo */

void			builtin_exit(t_commande *lst, int in_exec);
void			check_args(int ac, char **av);
char			*one_word_with_quotes(const char *str);
void			error_status(char *msg, int error);
int				quote_manager(char **input);

/* ooo - output_redir - ooo */

int				create_output_redir(char *filename, t_commande *cmd);
int				init_output(t_commande *curr_cmd, t_commande *cmd);

/* ooo - prompt - ooo */

void			ft_welcome(void);
char			*ft_prompt(void);

/* ooo - quotes -ooo */

void			assign_quotes(t_type *node, t_environment *env_copy);
char			*clean_cmd_type(t_type *node);
char			*remove_xtra_spaces(char *input);
int				between_quotes(char *str);
int				dbl_inside_single(const char *block);
int				single_inside_single(const char *block);

/* ooo - quotes_utils - ooo */

void			reassign_new_node(t_type *node, char *new_node);

char			*replace_with_expand_var(char *env_var, char *env_value,
					t_type *node, t_environment *env_cpy);

/* ooo - redir_utils - ooo */
char			*find_filename(t_args *args);

/* ooo - send_to_builtin_exec - ooo */

void			which_builtin(t_commande *cmd_lst, t_environment *env_copy,
					int in_exec);

/* ooo - send_to_execution - ooo*/

int				is_odd_or_even(int *pipe_count, int *cmd_count);

/* ooo - send_to_pipes - ooo*/

void			close_fds(t_commande *current_cmd);
void			wait_for_children(t_commande *cmd);
void			send_to_execution(t_commande *cmd, t_commande *head,
					t_environment *env_copy);
void			dup_and_close_fdin(t_commande *curr_cmd);
void			dup_and_close_fdout(t_commande *curr_cmd);

/* ooo - setup_redir - ooo*/
void			assign_fds(t_commande *cmd);
int				assign_redir(t_commande *cmd);
int				which_token(t_commande *cmd, int token);

/* ooo - signals - ooo */

void			sigint_handler(int signum);
void			silence(int signum);
void			set_signals(void);
void			unset_signals(void);
void			termios_mgmt(int toggle);

/* ooo - tokenization - ooo */

int				is_builtin(char *input);
void			assign_types(t_type *node, t_type *lst,
					int command_assigned, t_environment *env);

/* ooo - utils - ooo */

char			*ft_strcat(char *dest, char *src);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dest, const char *src, unsigned int n);
char			*concat_str(char *s1, char *s2);

/* ooo - utils_2 - ooo */

int				ft_is_it_space(char c);
int				ft_strcmp(const char *s1, const char *s2);

#endif
