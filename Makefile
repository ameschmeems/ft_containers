NAME	:=	containers

SRCS	:=	main.cpp

CC		:=	c++

CFLAGS	:=	-Wall -Wextra -Werror -std=c++98

test:
		${CC} ${CFLAGS} main.cpp -o ft_test_bin
		${CC} ${CFLAGS} main.cpp -o stl_test_bin -D STD
		./ft_test_bin >ft_test_file && ./stl_test_bin >stl_test_file
		diff -y ./ft_test_file ./stl_test_file

valgrind:
		${CC} ${CFLAGS} main.cpp -o ft_test_bin
		valgrind --leak-check=full ./ft_test_bin

leaks:
		${CC} ${CFLAGS} main.cpp -o ft_test_bin
		leaks -atExit -- ./ft_test_bin

performance:
		${CC} ${CFLAGS} intra_test_ft.cpp -o mine
		${CC} ${CFLAGS} intra_test_stl.cpp -o stl
		@echo "My times:"
		@time ./mine 42
		@echo "STL times:"
		@time ./stl 42

.PHONY:		all test valgrind leaks performance