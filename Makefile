# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikhristi <ikhristi@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/26 18:59:58 by nikitos           #+#    #+#              #
#    Updated: 2023/08/06 14:16:23 by ikhristi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft

SRCS = src/main.c src/lexer.c src/read_input.c src/lexer_utils.c src/token.c src/parsing.c
OBJS = ${SRCS:.c=.o}

RM = rm -f

GREEN = \033[0;32m
BLUE = \033[1;34m
CYAN = \033[1;36m
PURPLE = \033[0;35m
RED = \033[0;31m
YELLOW = \033[1;33m

CFLAGS = -Wall -Wextra -Werror -g

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