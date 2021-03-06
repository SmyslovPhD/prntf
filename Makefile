
SRCS 		= ft_printf.c 

OBJS		= ${SRCS:.c=.o} 

NAME		= libftprintf.a

CC			= gcc

RM			= rm -f

AR			= ar rcs

CFLAGS		= -Wall -Wextra -Werror -std=c99

LIBFT_F		= ./libft/

LIBFT		= libft.a

all:		${NAME}

.c.o:
			${MAKE} all -C ${LIBFT_F}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			cp ${LIBFT_F}${LIBFT} ${NAME}
			${AR} ${NAME} ${OBJS} 

clean:	
			${MAKE} clean -C ./libft
			${RM} -r ${OBJS}

fclean:		clean
			${MAKE} fclean -C ./libft
			${RM} ${NAME}

re:			fclean all
