SRCS 		= ft_printf.c 

OBJS		= ${SRCS:.c=.o} 

NAME		= printf.a

CC			= gcc

RM			= rm -f

AR			= ar rc

CFLAGS		= -Wall -Wextra -Werror -std=c99

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${AR} ${NAME} ${OBJS}

all:		${NAME}

clean:	
			${RM} -r ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all
