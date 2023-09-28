NAME = minishell
SRCDIR = ./srcs
OBJSDIR = ./objs
FILES = \
	expand_env.c export.c help_main.c lexer.c \
	main.c parser.c parser_utils.c print_arr.c \
	print_list.c token_lst.c utils_print_list.c exec_one_cmd.c \
	is_builtin.c my_execve.c
SRCS = $(addprefix $(SRCDIR)/,$(FILES)) 
OBJS = $(addprefix $(OBJSDIR)/,$(notdir $(SRCS:.c=.o)))
LDFLAGS = -lreadline -Llibft -lft
INCLUDES = -I ./includes -I ./libft
# DEBUG = -g -fsanitize=address
DEBUG = -g

$(OBJSDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p objs
	@$(CC) -c $< $(DEBUG) $(INCLUDES) -o $@

$(NAME) : $(OBJS)
	@make bonus -C ./libft
	@$(CC) $^ $(LDFLAGS) $(DEBUG) $(INCLUDES) -o $@

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

oka_git-% :
	git add srcs/*.c includes/*.h libft/*.c Makefile README
	git commit -m "$(@:git-%=%)"
	git push origin work

