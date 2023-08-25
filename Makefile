NAME = minishell
SRCDIR = ./srcs/
FILES = main.c
SRCS = $(addprefix $(SRCDIR),$(FILES)) 
OBJS = ${SRCS:.c=.o}
CFLAGS = -lreadline -Llibft -lft 
INCLUDES = -I ./includes

%.o : %.c
	@$(CC) -c $< $(CFLAGS) $(INCLUDES) -o $@

$(NAME) : $(OBJS)
	@make -C ./libft
	@$(CC) $^ $(CFLAGS) $(INCLUDES) -o $@

all : $(NAME)

clean : 
	@make clean -C ./libft
	@rm -rf $(OBJS)

fclean : clean
	@make fclean -C ./libft
	@rm -rf $(NAME)

re : fclean all

add :
	git add srcs/*.c includes/*.h libft/* Makefile README

echo :
	echo $(OBJS)
	echo $(SRCS)