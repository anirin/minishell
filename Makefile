NAME = minishell
SRCDIR = ./srcs
BLTINDIR = ./srcs/builtins
OBJSDIR = ./objs
SRC_FILES = \
	expand_env.c export.c pipefds.c lexer.c \
	main.c parser.c parser_utils.c print_arr.c \
	print_list.c token_lst.c utils_print_list.c exec_one_cmd.c \
	free_lists.c free_array.c terminate_program.c 
BLTIN_FILES = \
	is_builtin.c my_execve.c my_pwd.c my_cd.c
SRCS := $(addprefix $(SRCDIR)/,$(SRC_FILES))
SRCS += $(addprefix $(BLTINDIR)/,$(BLTIN_FILES))
OBJS := $(patsubst ./srcs/%.c, ./objs/%.o, $(SRCS))
# OBJS += $(addprefix $(OBJSDIR)/,$(notdir $(SRCS:.c=.o)))
LDFLAGS = -lreadline -Llibft -lft
LDLIBS = -lft
INCLUDES = -I ./includes -I ./libft/includes
# DEBUG = -g -fsanitize=address
DEBUG = -g
CFLAGS = -Wall -Wextra -Werror
RED=\033[31m
GREEN=\033[32m
RESET=\033[0m

# srcs/builtin/a.o <- srcs/builtin/a.c
# [.c.o:] = [%.o: %.c]

# objs/[is_builtin].o <- src/[is_builtin].o
# objs/[builtin/is_builtin].o <- src/[builtin/is_builtin].o
$(OBJSDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) -c $< $(DEBUG) $(INCLUDES) -o $@

# $(OBJSDIR)/%.o : $(BLTINDIR)/%.c
# 	@$(CC) -c $< $(DEBUG) $(INCLUDES) -o $@

# objs/builtin/is_builtin.o
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

ifndef branch
	$(error branch is not defined.)
endif

ifndef message
	$(error message is not defined.)
endif

#useage make git b=<branch_name> m=<commit_message>

git:
	git add objs/ srcs/*.c includes/*.h srcs/*/*.c\
			Makefile README .gitignore\
			libft/includes/*.h libft/srcs/*.c libft/Makefile 
	git commit -m "$(m)"
	git push origin $(b)

.PHONY: git_commit_push
