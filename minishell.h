/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:20:21 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/19 15:01:49 by lmedrano         ###   ########.fr       */
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

/* ooo - copy_env - ooo */

t_environment	*copy_env(char **envp);
void			free_env_struct(t_environment *env_struct);

/* ooo - create_cmd - ooo */

t_commande		*command_list(t_type *tokens, int *pipe_count, int *cmd_count,
					t_environment *env_copy);

/* ooo - create_lst - ooo */

t_type			*init_lst(char **blocks, t_type *node, t_environment *env_copy);

/* ooo - custom_parsing_split - ooo */

int				block_count(char const *str, char c);
char			**ft_parsing_split(const char *input, char c, int *wc);
void			ft_free_parsing_split(char **blocks);

/* ooo - error - ooo */

void			free_argv(char **argv);
int				ft_error(char *str);

/* ooo - execve - oo */

char			*find_executable_path(char *command, t_environment *env_copy);
char			**build_arg(t_commande *cmd, t_environment *env_copy);
int				execute_basic_cmd(t_commande *cmd, t_environment *env_copy);

/* ooo - expand_variable - ooo */

char			*find_env_variable(t_type *node);
char			*retrieve_env_variable(char *env_var, t_environment *env);
char			*replace_env_value(t_type *node, char *env_value);

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

/* ooo - output_utils - ooo */
char			*find_filename(t_commande *cmd);
int				create_output_file(t_commande *cmd);
void			close_fds_output(int output_file, int *pipe_fd);
void			pipe_fd_output(int *pipe_fd, int output_file);
char			*create_filename(t_commande *cmd);
int				create_output_file2(char *filename);

/* ooo - prompt - ooo */

void			ft_welcome(void);
char			*ft_prompt(void);

/* ooo - quotes -ooo */

void			assign_quotes(t_type *node, t_environment *env_copy);
t_type			*clean_cmd_type(t_type *node);
char			*remove_xtra_spaces(char *input);
int				between_quotes(char *str);

/* ooo - send_to_builtin_exec - ooo */

void			which_builtin(t_commande *cmd_lst);

/* ooo - send_to_execution - ooo*/

int				is_odd_or_even(int *pipe_count, int *cmd_count);

/* ooo - send_to_pipes - ooo*/

void			close_fds(t_commande *current_cmd, t_commande *cmd);
void			wait_for_children(t_commande *cmd);
void			send_to_execution(t_commande *cmd, t_environment *env_copy);
void			dup_and_close(int fd);

/* ooo - signals - ooo */

void			sigint_handler(int signum);
void			handling_signals(char *input);

/* ooo - tokenization - ooo */

int				is_builtin(char *input);
void			assign_types(t_type *node, t_type *lst,
					t_environment *env_copy);
/* ooo - utils - ooo */

char			*ft_strcat(char *dest, char *src);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dest, const char *src, unsigned int n);
char			*concat_str(char *s1, char *s2);

/* ooo - utils_2 - ooo */

int				ft_isspace(char c);
int				ft_strcmp(const char *s1, const char *s2);

/* ooo - TEST EXEC - ooo */

void			assign_fds(t_commande *cmd);
t_commande		*is_last_cmd(t_commande *cmd);
int				create_output_redir(char *filename, t_commande *cmd);
int				create_input_redir(char *filename, t_commande *cmd);
int				create_append(char *filename, t_commande *cmd);
int				heredoc_fd(char *del);
int				create_heredoc(char *filename, t_commande *cmd);
void			assign_redir(t_commande *cmd);
int				has_redir(t_commande *cmd);

/*-------------- builtin cd --------------*/
int				check_args(t_commande *cmd_lst, t_environment *env_copy);
int				ft_cd(t_environment *env_copy, char *path);
void			add_node_at_end(t_environment *head, char *key, char *value);
int				go_home(t_environment *env_copy, char *home);
char			*get_home(t_environment *head);
char			*get_env_value(t_environment *env_copy, char *key);
t_environment	*last_node(t_environment *head);
int				go_last_directories(t_environment *env_copy, int hyphen);
int				check_is_in_env(t_environment *env_copy, char *var);
int				check_path(char *path);
void			update_pwd_oldpwd(t_environment *head, char *change_pwd);
int				builtin_cd(t_commande *cmd_lst, t_environment *env_copy);
/* --------------builtin echo --------------*/
void ft_echo(char *str, t_environment *env_copy);
int check_option_n(char *str);
int echo(t_commande *cmd_lst, t_environment *env_copy);


#endif
