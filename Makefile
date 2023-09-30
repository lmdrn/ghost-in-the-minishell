# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angela <angela@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/05 10:32:07 by lmedrano          #+#    #+#              #
#    Updated: 2023/09/30 16:54:08 by lmedrano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLUE 		= \033[38;5;69m
ORANGE 		= \033[38;5;215m
GREEN 		= \033[38;5;82m
RESET 		= \033[0m
BS_N_TXT			=		echo "\n"
                                                  
                                       

SRCS 		= prompt.c parsing.c blocks_to_list.c

OBJS 		= ${SRCS:.c=.o}

NAME		= minishell

CC 		= gcc

CFLAGS		= -Wall -Werror -Wextra

CFLAGS		+= -fsanitize=address -g3 

LIBFT =		-L./libft -lft

RM		= rm -rf

all:		$(NAME)

${NAME}:	${OBJS}
			@tput setaf 2; cat ascii_art/ghost; tput setaf
			@$(BS_N_TXT)
			@$(BS_N_TXT)
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

