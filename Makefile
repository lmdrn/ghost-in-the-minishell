# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmedrano <lmedrano@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/05 10:32:07 by lmedrano          #+#    #+#              #
#    Updated: 2023/12/22 18:38:57 by lmedrano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLUE 		= \033[38;5;69m
ORANGE 		= \033[38;5;215m
GREEN 		= \033[38;5;82m
RESET 		= \033[0m
BS_N_TXT			=		echo "\n"
                                                  
                                       

SRCS 		= prompt.c custom_parsing_split.c blocks_to_list.c \
			  create_cmd.c execve.c tokenization.c \
			  utils.c error.c free_lst.c assign_types.c \
			  assign_cmd_or_builtin.c create_lst.c \
			  copy_env.c send_to_builtin_exec.c quotes.c \
			  utils_2.c expand_variable.c minishell.c \
			  signals.c init.c send_to_execution.c \
			  send_to_pipes.c output_redir.c heredoc.c \
			  redir_utils.c setup_redir.c input_redir.c \
			  append.c built_in/cd.c built_in/echo.c \
			  built_in/cd_utils.c built_in/echo_utils.c\
			  built_in/export_utils.c built_in/export_sorted.c\
			  built_in/unset.c built_in/copy_lst.c\
			  built_in/pwd.c built_in/env.c built_in_utils.c \
			  built_in/export.c built_in/list_utils.c\
			  blocks_to_list_utils.c create_cmd_utils.c \
			  custom_parsing_split_utils.c clean_cmd.c \
			  execve_utils.c expand_variable_utils.c \
			  absolute_cmd.c

OBJS 		= ${SRCS:.c=.o}

NAME		= minishell

CC 		= gcc

CFLAGS		= -Wall -Werror -Wextra -I$(HOME)/.brew/opt/readline/include -Ilibft

CFLAGS		+= -fsanitize=address -g

LIBFT =		-L./libft -lft

READLINE =	-I$(HOME)/.brew/opt/readline/include -L$(HOME)/.brew/opt/readline/lib -lreadline 

RM		= rm -rf

all:		$(NAME)

${NAME}:	${OBJS}
			@tput setaf 2; cat ascii_art/ghost; tput setaf
			@$(BS_N_TXT)
			@$(BS_N_TXT)
			@echo "$(RESET)$(ORANGE)ASSEMBLING $(NAME)$(RESET)"
			@$(MAKE) -C libft --silent
			${CC} ${CFLAGS} ${OBJS} $(LIBFT) -o ${NAME} ${READLINE}
			@echo "$(RESET)$(GREEN)$(NAME) HAS ASSEMBLED ✓$(RESET)"

clean:		
			@echo "$(RESET)$(ORANGE)I'M CLEANING OUT MY CLOSET...$(RESET)"
			@$(MAKE) -C libft clean
			@echo "$(RESET)$(GREEN)CLEANED ✓$(RESET)"

fclean:		clean
			@echo "$(RESET)$(ORANGE)ONE MORE TIME...$(RESET)"
			rm -f libft/libft.a
			${RM} ${OBJS} ${NAME}
			@echo "$(RESET)$(GREEN)ALL CLEANED ✓✓$(RESET)"

re:			fclean all

.PHONY:		all clean fclean libft re
