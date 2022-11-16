FLAGS=-Wall -Wextra -Werror
NAME=server\

CSRC=helper.c\
client.c\

all:$(NAME) 

$(NAME):$(SOBJ) $(HOBJ)
	cc $(FLAGS) -o $@ $^

$(SOBJ):$(SSRC)
	cc $(FLAGS) -c $^

$(HOBJ):$(HSRC)
	cc $(FLAGS) -c $^

clean:
	rm -rf $(HOBJ) $(COBJ) $(SOBJ)

fclean:clean
	rm -rf $(NAME) $(NAME2)

re:fclean all
