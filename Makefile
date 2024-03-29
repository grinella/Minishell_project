NAME			=	minishell

LIBFT_A			=	libft.a
LIBFT_DIR		=	include/libft/
LIBFT			=	$(addprefix $(LIBFT_DIR), $(LIBFT_A))

CC				=	gcc -g
INCLUDE			=	includes
CFLAGS			=	-Wall -Wextra -Werror -I$(INCLUDE)
RM				=	rm -f

SRCS = 		minishell.c \
			mini_utils.c \
			mini_free.c \
			parser/lexer.c \
			parser/lexer_utils.c \
			parser/alloc_functions.c \
			parser/mini_count_words.c \
			parser/tokenizer_fill_str.c \
			parser/tokenizer_fill_node.c \
			parser/tokenizer_utils.c \
			parser/tokenizer.c \
			signals/signals.c \
			executor/builtins/builtin.c \
			executor/builtins/my_exit.c \
			executor/builtins/my_echo.c \
			executor/builtins/my_env.c \
			executor/builtins/my_cd.c \
			executor/builtins/my_pwd.c \
			executor/builtins/my_export.c \
			executor/executor.c \
			executor/redirections.c \
			# builtins/*.c \
			executor/builtins/builtin_utils.c \
			executor/redirection.c \

OBJS		=	$(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft -L/usr/local/opt/readline/lib -lreadline -ltermcap
			@echo "\nLinked into executable \033[0;32mminishell\033[0m."

# $(NAME):	$(LIBFT) $(OBJS)
# 			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft -L/Users/$(USER)/.brew/opt/readline/lib -lreadline -ltermcap
# 			@echo "\nLinked into executable \033[0;32mminishell\033[0m."

$(LIBFT):
			@echo "Compiling libft.a"
			@$(MAKE) all -s -C $(LIBFT_DIR)

.c.o:
			@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

localclean:
			@$(RM) $(OBJS)
			@echo "Removed object files."

clean:		localclean
			@$(MAKE) clean -s -C $(LIBFT_DIR)
			@echo "Clean libft."

fclean:		localclean
			@$(MAKE) fclean -s -C $(LIBFT_DIR)
			@echo "Full clean libft."
			@$(RM) $(NAME)
			@echo "Removed executable."

re:			fclean all

.PHONY:		all clean fclean localclean re