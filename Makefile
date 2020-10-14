# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mac <mac@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/19 17:15:33 by szakaria          #+#    #+#              #
#    Updated: 2020/10/14 12:52:22 by ommadhi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

CFLAGS = -Wall -Wextra -Werror

_lCYAN = \x1b[96m
_lYELLOW = \x1b[93m
_lGREEN = \x1b[92m
_lBLUE = \x1b[94m
_RED = \x1b[31m
_BOLD = \x1b[1m
_END = \x1b[0m

LIB = libft/libft.a
LIB2 = GTN/get_next_line.c

SRC = minishell.c GTN/get_next_line.c trait.c execve.c list.c \
		execve_help.c init_shell.c make_job.c wait_job.c jobs.c \
		help.c all_command_jobs.c help_command_jobs.c help_command_jobs_v2.c \
		help_v2.c  checker.c checker_v2.c checker_v3.c checker_v4.c \
		parsing.c help_parsing.c help_parsing_v2.c help_parsing_v3.c \
		trait_pipe.c redirect.c redirect_v2.c replace_with_env.c make_home.c \
		slash_quote.c redirect_help.c redirect_v3.c parse_the_redirect.c \
		redirect_help_v2.c help_trait_and.c get_path.c filter_command.c \
		built_back_fore.c built_env_echo.c mini_type.c built_unset.c \
		built_export.c built_cd.c help_cd.c help_cd_v2.c variables.c \
		move_variables.c help_variable.c help_v3.c\
		readline/ft_autocomp2.c\
        readline/ft_copy.c\
        readline/ft_multi_line.c\
        readline/ft_mv_cursor.c\
        readline/ft_press_key.c\
        readline/ft_readline.c\
        readline/ft_save_history.c\
        readline/get_cur_posix.c\
        readline/ft_scroll.c\
        readline/ft_add_and_del_char.c\
        readline/ft_goto.c\
        readline/ft_ctr_c.c\
        readline/ft_free_his.c\
        readline/ft_print_his.c\
        readline/ft_autoco_search.c\
		
C       = gcc
OBJ = $(SRC:.c=.o)
DEP = sh.h

all : $(NAME)

$(NAME) : LIB $(OBJ) 
		@$(C) -ltermcap $(CFLAGS)  $(OBJ) -o $(NAME) libft/libft.a

LIB:
		@make -C libft

%.o	: %.c $(DEP)
		$(C) $(CFLAGS)  -o $@ -c $<

clean	:
		@make clean -C libft
		@rm -f $(OBJ)

fclean	: clean
		@make fclean -C libft
		@rm -f $(NAME)

re	: fclean all
