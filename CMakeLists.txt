cmake_minimum_required(VERSION 3.21)
project(miiiiiiiii_cd C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
#include_directories(./libft/ /Users/angela/.brew/opt/readline/include /Users/angela/.brew/opt/readline/lib)
#include_directories(libft readline)

add_compile_options(-I/Users/angela/.brew/opt/readline/include -L/Users/angela/.brew/opt/readline/lib -lreadline)
add_compile_options(-Wall -Werror -Wextra -I/Users/angela/.brew/opt/readline/include -Ilibf)

SET(LIBS readline)
SET(LIBS ${LIBS})
add_executable(miiiiiiiii_cd
        built_in/cd.c
        libft/ft_atoi.c
        libft/ft_bzero.c
        libft/ft_calloc.c
        libft/ft_isalnum.c
        libft/ft_isalpha.c
        libft/ft_isascii.c
        libft/ft_isdigit.c
        libft/ft_isprint.c
        libft/ft_itoa.c
        libft/ft_lstadd_back_bonus.c
        libft/ft_lstadd_front_bonus.c
        libft/ft_lstclear_bonus.c
        libft/ft_lstdelone_bonus.c
        libft/ft_lstiter_bonus.c
        libft/ft_lstlast_bonus.c
        libft/ft_lstmap_bonus.c
        libft/ft_lstnew_bonus.c
        libft/ft_lstsize_bonus.c
        libft/ft_memchr.c
        libft/ft_memcmp.c
        libft/ft_memcpy.c
        libft/ft_memmove.c
        libft/ft_memset.c
        libft/ft_putchar_fd.c
        libft/ft_putendl_fd.c
        libft/ft_putnbr_fd.c
        libft/ft_putstr_fd.c
        libft/ft_split.c
        libft/ft_strchr.c
        libft/ft_strdup.c
        libft/ft_striteri.c
        libft/ft_strjoin.c
        libft/ft_strlcat.c
        libft/ft_strlcpy.c
        libft/ft_strlen.c
        libft/ft_strmapi.c
        libft/ft_strncmp.c
        libft/ft_strnstr.c
        libft/ft_strrchr.c
        libft/ft_strtrim.c
        libft/ft_substr.c
        libft/ft_tolower.c
        libft/ft_toupper.c
        libft/libft.h
        assign_cmd_or_builtin.c
        assign_types.c
        blocks_to_list.c
        copy_env.c
        create_cmd.c
        create_lst.c
        custom_parsing_split.c
        error.c
        execve.c
        expand_variable.c
        free_lst.c
        init.c
        minishell.c
        minishell.h
        prompt.c
        quotes.c
        send_to_builtin_exec.c
        send_to_execution.c
        send_to_pipes.c
        signals.c
        test_chdir.c
        tokenization.c
        utils.c
        utils_2.c
        built_in/export.c
        built_in/pwd.c
        built_in/env.c
        built_in/cd.c
        built_in/list_utils.c)

#TARGET_LINK_LIBRARIES(miiiiiiiii_cd ${LIBS})