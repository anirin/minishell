NAME = minishell
SRCDIR = ./srcs/
FILES = main.c lexer.c print_list.c print_arr.c perxer.c exec.c
SRCS = $(addprefix $(SRCDIR),$(FILES)) 
OBJS = ${SRCS:.c=.o}
CFLAGS = -lreadline -Llibft -lft
INCLUDES = -I ./includes -I ./libft
DEBUG = -g -fsanitize=address

%.o : %.c
	@$(CC) -c $< $(CFLAGS) $(INCLUDES) -o $@

$(NAME) : $(OBJS)
	@make bonus -C ./libft
	@$(CC) $^ $(CFLAGS) $(DEBUG) $(INCLUDES) -o $@

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