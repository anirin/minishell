NAME = minishell
SRCDIR = ./srcs
OBJSDIR = ./objs
FILES = \
	expand_env.c export.c pipefds.c lexer.c \
	main.c parser.c parser_utils.c print_arr.c \
	print_list.c token_lst.c utils_print_list.c exec_one_cmd.c \
	is_builtin.c my_execve.c free_lists.c free_array.c
SRCS = $(addprefix $(SRCDIR)/,$(FILES)) 
OBJS = $(addprefix $(OBJSDIR)/,$(notdir $(SRCS:.c=.o)))
LDFLAGS = -lreadline -Llibft -lft
INCLUDES = -I ./includes -I ./libft/includes
# DEBUG = -g -fsanitize=address
DEBUG = -g
CFLAGS = -Wall -Wextra -Werror
RED=\033[31m
GREEN=\033[32m
RESET=\033[0m

$(OBJSDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) -c $< $(DEBUG) $(INCLUDES) -o $@

$(NAME) : $(OBJS)
	@make -C ./libft
	@$(CC) $^ $(LDFLAGS) $(DEBUG) $(INCLUDES) -o $@ 
	@echo "$(GREEN)	✅ $(NAME) created$(RESET)"

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

git-% :
	git add objs/ srcs/*.c includes/*.h libft/includes/*.h libft/srcs/*.c libft/objs/ libft/Makefile Makefile README .gitignore
	git commit -m "$(@:git-%=%)"
	git push origin work

