# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/05 10:32:07 by lmedrano          #+#    #+#              #
#    Updated: 2023/09/26 15:02:14 by lmedrano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLUE 		= \033[38;5;69m
ORANGE 		= \033[38;5;215m
GREEN 		= \033[38;5;82m
RESET 		= \033[0m

SRCS 		= prompt.c parsing.c quotes.c labels.c copy_env.c bultins.c \
			  exit.c

OBJS 		= ${SRCS:.c=.o}

NAME		= minishell

CC 		= gcc

CFLAGS		= -Wall -Werror -Wextra

CFLAGS		+= -fsanitize=address -g3 

LIBFT =		-L./libft -lft

RM		= rm -rf

all:		$(NAME)

${NAME}:	${OBJS}
			@echo "$(RESET)$(ORANGE)ASSEMBLING $(NAME)$(RESET)"
			@$(MAKE) -C libft --silent
			${CC} ${CFLAGS} ${OBJS} $(LIBFT) -o ${NAME} -lreadline
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

