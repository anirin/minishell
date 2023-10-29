NAME = minishell
SRCDIR = srcs
OBJSDIR = objs
SRCS = \
	srcs/builtins/is_builtin.c srcs/builtins/my_cd.c srcs/builtins/my_cd_utils.c srcs/builtins/my_echo.c srcs/builtins/my_env.c srcs/builtins/my_execve.c srcs/builtins/my_exit.c srcs/builtins/my_exit_help.c srcs/builtins/my_export.c srcs/builtins/my_export_error.c srcs/builtins/my_export_modify_env_value.c srcs/builtins/my_export_to_string_parse_token.c srcs/builtins/my_pwd.c srcs/builtins/my_unset.c srcs/env/expand_env.c srcs/env/token_lst.c srcs/error/check_syntax_error.c srcs/error/print_err.c srcs/exec/envlist_to_envp.c srcs/exec/exec_in_child.c srcs/exec/exec_one_cmd.c srcs/exec/get_path.c srcs/exec/main.c srcs/exec/pipe.c srcs/exec/pipefds.c srcs/exec/redirect.c srcs/exec/redirect_in.c srcs/exec/redirect_out.c srcs/lexer/add_colon_doll_token.c srcs/lexer/add_pipe_redirect_token.c srcs/lexer/add_quote_token.c srcs/lexer/lexer.c srcs/parser/get_cmd_args.c srcs/parser/get_redirect.c srcs/parser/parser.c srcs/parser/parser_utils.c srcs/parser/set_stat_content.c srcs/signal/handle_signal.c srcs/signal/handle_signal_utils.c srcs/utils/change_finish_stat.c srcs/utils/free_array.c srcs/utils/free_lists.c srcs/utils/print_arr.c srcs/utils/print_list.c
OBJS := $(patsubst srcs/%.c, objs/%.o, $(SRCS))
LDFLAGS = -Llibft -lft -L $(shell brew --prefix readline)/lib -lreadline
LDLIBS = -lft
INCLUDES = -I ./includes -I ./libft/includes -I $(shell brew --prefix readline)/include
#DEBUG = -g -fsanitize=address
#DEBUG = -g
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
	# @echo $(SRCS)
	# @echo $(OBJS)
	echo $(LDFLAGS)

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

leak:
	while [ 1 ]; do leaks minishell; sleep 2; done

.PHONY: git_commit_push
