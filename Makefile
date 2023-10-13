NAME = minishell
SRCDIR = srcs
OBJSDIR = objs
SRCS = \
	srcs/builtins/is_builtin.c srcs/builtins/my_cd.c srcs/builtins/my_echo.c srcs/builtins/my_env.c srcs/builtins/my_execve.c srcs/builtins/my_exit.c srcs/builtins/my_export.c srcs/builtins/my_pwd.c\
	srcs/env/expand_env.c srcs/env/token_lst.c srcs/error/check_syntax_error.c srcs/exec/exec_one_cmd.c srcs/exec/main.c srcs/exec/pipefds.c srcs/lexer/lexer.c srcs/parser/parser.c srcs/parser/parser_utils.c\
	srcs/signal/terminate_program.c srcs/utils/control_shell_list.c srcs/utils/free_array.c srcs/utils/free_lists.c srcs/utils/print_arr.c srcs/utils/print_list.c srcs/utils/utils_print_list.c
OBJS := $(patsubst srcs/%.c, objs/%.o, $(SRCS))
LDFLAGS = -lreadline -Llibft -lft
LDLIBS = -lft
INCLUDES = -I ./includes -I ./libft/includes
# DEBUG = -g -fsanitize=address
DEBUG = -g
CFLAGS = -Wall -Wextra -Werror
RED=\033[31m
GREEN=\033[32m
RESET=\033[0m

$(OBJSDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(@D)
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

ifndef branch
	$(error branch is not defined.)
endif

ifndef message
	$(error message is not defined.)
endif

#useage make git b=<branch_name> m=<commit_message>

git:
	git add .
	git commit -m "$(m)"
	git push origin $(b)

.PHONY: git_commit_push
