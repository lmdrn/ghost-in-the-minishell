/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:20:21 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/26 14:57:06 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

/* ooo - structures - ooo */

typedef struct s_type
{
	char	*text;
	int		pipe;
	int		chevron_d;
	int		chevron_g;
	int		dbl_chev_d;
	int		dbl_chev_g;
}	t_type;

typedef struct s_commande
{
	char	**cmd;
	char	**args;
	char	**in;
	char	**out;
}	t_commande;

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
int    is_builtin(char *input);

#endif
