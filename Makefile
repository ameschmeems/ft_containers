NAME	:=	containers

SRCS	:=	main.cpp

OBJS	:=	${SRCS:.cpp=.o}

CC		:=	c++

CFLAGS	:=	-Wall -Wextra -Werror -std=c++98

%.o:		%.c
		${CC} ${CFLAGS} $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
		${CC} ${OBJS} -o ${NAME} ${CFLAGS}

clean:
		rm -f ${OBJS}

fclean:		clean
		rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re