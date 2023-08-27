CFLAGS = -Wall -Wextra -Werror
AR = ar rc
NAME = ./libft.a
OBJCS = $(SRCS:%.c=%.o)
BOBJCS = $(BSRCS:%.c=%.o)
SRCS = ft_atoi.c\
ft_bzero.c\
ft_calloc.c\
ft_isalnum.c\
ft_isalpha.c\
ft_isascii.c\
ft_isdigit.c\
ft_isprint.c\
ft_itoa.c\
ft_memchr.c\
ft_memcmp.c\
ft_memcpy.c\
ft_memmove.c\
ft_memset.c\
ft_putchar_fd.c\
ft_putendl_fd.c\
ft_putnbr_fd.c\
ft_putstr_fd.c\
ft_split.c\
ft_strchr.c\
ft_strdup.c\
ft_striteri.c\
ft_strjoin.c\
ft_strlcat.c\
ft_strlcpy.c\
ft_strlen.c\
ft_strmapi.c\
ft_strncmp.c\
ft_strnstr.c\
ft_strrchr.c\
ft_strtrim.c\
ft_substr.c\
ft_tolower.c\
ft_toupper.c\
get_next_line.c

BSRCS = ft_lstadd_back.c\
ft_lstadd_front.c\
ft_lstclear.c\
ft_lstdelone.c\
ft_lstiter.c\
ft_lstlast.c\
ft_lstnew.c\
ft_lstsize.c\
ft_lstmap.c

ifdef WITH_BONUS
	SRCS+=$(BSRCS)
endif

%.o : %.c
	@$(CC) -c $< $(CFLAGS) -o $@

$(NAME): $(OBJCS)
	@$(AR) $@ $^

all: $(NAME)
	@echo "libft all"

bonus:
	make WITH_BONUS=1 $(NAME)

clean:
	@$(RM) $(BOBJCS) $(OBJCS) 
	@echo "libft clean"

fclean: clean
	@$(RM) $(NAME)
	@echo "libft fclean"

re: fclean all

.PHONY : all clean fclean re bonus