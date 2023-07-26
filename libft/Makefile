NAME	=	libft.a
# Имена скомпилированных программ
SRCS	=	ft_memset.c  \
	ft_bzero.c  \
	ft_memcpy.c  \
	ft_memmove.c  \
	ft_memchr.c  \
	ft_memcmp.c  \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isprint.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_strchr.c  \
	ft_atoi.c  \
	ft_strlen.c  \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_memcmp.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	get_next_line_bonus.c \
	get_next_line_utils_bonus.c \

SRCS_BONUS	=	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \

OBJS	=	${SRCS:.c=.o}
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
# Чтобы только измененные файлы .c компилировались в файлы .o
RM		=	rm -f
# -f (force) делает fclean исполняемым в любое время (даже без файлов .o)
CC		=	gcc
# Компилятор
CFLAGS	=	-Wall -Wextra -Werror

all:		${NAME}
# Используемые флаги
${NAME}:	${OBJS}
			ar rcs $(NAME) $(OBJS)

bonus: 		$(OBJS) $(OBJS_BONUS)
			ar rcs ${NAME} $(OBJS) ${OBJS_BONUS}
clean:
			${RM} ${OBJS} ${OBJS_BONUS}
# Удаляет все файлы с .o
fclean:		clean
			${RM} ${NAME}
# Удаляет libft.a
re:			fclean all
# Удалить и перекомпилировать
.PHONY:		all clean fclean re
# Запускаем команды, даже если файл с таким именем уже существует
