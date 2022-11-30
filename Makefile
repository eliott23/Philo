FLAGS=-Wall -Wextra -Werror
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
	rm -rf $(HOBJ) $(COBJ) $(SOBJ)

fclean:clean
	rm -rf $(NAME) $(NAME2)

re:fclean all
