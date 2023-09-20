# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/26 18:59:58 by nikitos           #+#    #+#              #
#    Updated: 2023/09/20 12:34:50 by nikitos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft

SRCS = src/env.c src/main.c src/handler.c  src/export.c src/unset.c src/export_2.c src/signals.c src/free.c src/lexer_1.c src/lexer_2.c src/lexer_3.c src/array_reading.c src/clear.c src/read_input.c src/cd.c src/pipe_utils.c  src/executor.c src/redirection_1.c src/redirection_2.c src/heredoc.c src/lexer_utils.c src/token.c src/pars_utils.c
OBJS = ${SRCS:.c=.o}

RM = rm -f

GREEN = \033[0;32m
BLUE = \033[1;34m
CYAN = \033[1;36m
PURPLE = \033[0;35m
RED = \033[0;31m
YELLOW = \033[1;33m
INC = inc
# -fsanitize=address -g -I $(INC)
#CFLAGS = -Wall -Wextra -Werror -g

all:	$(NAME)

$(NAME):	$(OBJS)
			@echo "\n"
			@echo "$(YELLOW)Starting compiling...$(DEF_COLOR)"
			@echo "\n"
			@echo "$(CYAN)."
			@make -C $(LIBFT)
			mv $(LIBFT)/libft.a libft.a
			gcc $(CFLAGS) $(OBJS) -lreadline -o $(NAME) libft.a
			@echo "\n"
			@echo "$(GREEN)MINISHELL compiled!$(DEF_COLOR)"

clean:
		@make -C $(LIBFT) clean
		@echo "$(RED)Starting deleting..."
		$(RM) $(OBJS)
		$(RM) libft.a
		@echo "\n"
		@echo "$(YELLOW)Objects removed!"
		@echo "\n"

fclean: clean
		@echo "$(RED)Starting deleting..."
		${RM} $(NAME)

re:		fclean all

.PHONY:		all clean fclean re