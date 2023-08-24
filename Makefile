NAME = minishell
SRCS = main.c
OBJS = ${SRCS:.o=.c}
CFLAGS = -lreadline

$(NAME) : $(OBJS)
	$(CC) $^ $(CFLAGS) -o $@

clean : 
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

add :
	git add *.c *.h Makefile