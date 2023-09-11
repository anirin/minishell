NAME = minishell
SRCDIR = ./srcs
OBJSDIR = ./objs
FILES = main.c lexer.c print_list.c print_arr.c parser.c exec_utils.c exec_one_readline.c redirect.c export.c
SRCS = $(addprefix $(SRCDIR)/,$(FILES)) 
OBJS = $(addprefix $(OBJSDIR)/,$(notdir $(SRCS:.c=.o)))
CFLAGS = -lreadline -Llibft -lft
INCLUDES = -I ./includes -I ./libft
DEBUG = -g -fsanitize=address

$(OBJSDIR)/%.o : $(SRCDIR)/%.c
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

echo :
	@echo $(SRCS)
	@echo $(OBJS)

re : fclean all

add :
	git add srcs/*.c includes/*.h libft/* Makefile README