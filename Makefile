FLAGS=-fsanitize=threads -Wall -Wextra -Werror
NAME=philo\

SRC=main.c\
helper.c\
helper2.c\
protections.c\

OBJ=main.o\
helper.o\
helper2.o\
protections.o\

all:$(NAME) 

$(NAME):$(OBJ)
	cc $(FLAGS) -o $@ $^

$(OBJ):$(SRC)
	cc $(FLAGS) -c $^

clean:
	rm -rf $(OBJ)

fclean:clean
	rm -rf $(NAME)

re:fclean all
