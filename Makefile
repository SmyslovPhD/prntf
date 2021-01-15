
SRCS 		= ft_printf.c 

OBJS		= ${SRCS:.c=.o} 

NAME		= libftprintf.a

CC			= gcc

RM			= rm -f

AR			= ar rc

CFLAGS		= -Wall -Wextra -Werror -std=c99

all:		${NAME}

.c.o:
			${MAKE} all -C ./libft
			ranlib libft/libft.a
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -L. -lft

$(NAME):	${OBJS}
			${AR} ${NAME} ${OBJS}

clean:	
			${MAKE} clean -C ./libft
			${RM} -r ${OBJS}

fclean:		clean
			${MAKE} fclean -C ./libft
			${RM} ${NAME}

re:			fclean all
