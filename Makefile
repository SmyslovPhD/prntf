
SRCS 		= ft_printf.c 

OBJS		= ${SRCS:.c=.o} 

NAME		= libftprintf.a

CC			= gcc

RM			= rm -f

AR			= ar rc

CFLAGS		= -Wall -Wextra -Werror -std=c99

.c.o:		
			${MAKE} all -C ./libft
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} libft/libft.a

$(NAME):	${OBJS}
			${AR} ${NAME} ${OBJS}

all:		${NAME}

clean:	
			${MAKE} clean -C ./libft
			${RM} -r ${OBJS}

fclean:		clean
			${MAKE} fclean -C ./libft
			${RM} ${NAME}

re:			fclean all
