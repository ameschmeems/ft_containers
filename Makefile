NAME	:=	containers

SRCS	:=	main.cpp

OBJS	:=	${SRCS:.cpp=.o}

CC		:=	c++

CFLAGS	:=	-Wall -Wextra -Werror -std=c++98

test:
		${CC} ${CFLAGS} ${SRCS} -o ft_test_bin
		${CC} ${CFLAGS} ${SRCS} -o stl_test_bin -D STD
		./ft_test_bin >ft_test_file && ./stl_test_bin >stl_test_file
		diff -y ./ft_test_file ./stl_test_file

valgrind:
		${CC} ${CFLAGS} ${SRCS} -o ft_test_bin
		valgrind --leak-check=full ./ft_test_bin

leaks:
		${CC} ${CFLAGS} ${SRCS} -o ft_test_bin
		leaks -atExit -- ./ft_test_bin

.PHONY:		all test valgrind leaks