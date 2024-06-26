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
			executor/builtins/builtin_utils.c \
			executor/builtins/my_exit.c \
			executor/builtins/my_echo.c \
			executor/builtins/my_env.c \
			executor/builtins/my_cd.c \
			executor/builtins/my_pwd.c \
			executor/builtins/my_export.c \
			executor/builtins/my_unset.c \
			executor/executor.c \
			executor/executor_utils.c \
			executor/redirections.c

OBJS		=	$(SRCS:%.c=%.o)

all:		$(NAME)

# RED = \033[0;31m
# ORANGE = \033[0;33m
# YELLOW = \033[0;93m
# GREEN = \033[0;32m
# BLUE = \033[0;34m
# INDIGO = \033[0;94m
# VIOLET = \033[0;35m
# RESET = \033[0m

$(NAME):	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft -L/usr/local/opt/readline/lib -lreadline -ltermcap
			@echo "\nLinked into executable \033[0;32mminishell\033[0m."
			@echo "\033[0;31m""       ::::  ::::   ::::::::::: ::::    ::: ::::::::::: ::::::::  :::    ::: :::        :::::::: "
			@echo "\033[0;33m""      :+:+: :+:+:      :+:     :+:+:   :+:     :+:    :+:    :+: :+:    :+: :+:       :+:    :+: "
			@echo "\033[0;93m""    +:+ +:+:+ +:+     +:+     :+:+:+  +:+     +:+    +:+        +:+    +:+ +:+       +:+    +:+  "
			@echo "\033[0;32m""   +#+  +:+  +#+     +#+     +#+ +:+ +#+     +#+    +#+        +#+    +:+ +#+       +#+    +:+   "
			@echo "\033[0;96m""  +#+       +#+     +#+     +#+  +#+#+#     +#+    +#+        +#+    +#+ +#+       +#+    +#+    "
			@echo "\033[0;94m"" #+#       #+#     #+#     #+#   #+#+#     #+#    #+#    #+# #+#    #+# #+#       #+#    #+#     "
			@echo "\033[0;35m""###       ### ########### ###    #### ########### ########   ########  ########## ########       "
			@echo "\033[0;90m""*_*_*_*_*_*_*_*_*_*_*_*_*BY ecaruso & grinella*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*"
			@echo "\033[0m"


$(LIBFT):
			@echo "Compiling libft.a"
			@$(MAKE) all -s -C $(LIBFT_DIR)

.c.o:
			@printf "\033[0;32mGenerating minishell objects... %-33.33s\r" $@
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

localclean:
			@$(RM) $(OBJS)
			@echo "\033[0;31m""Removed object files."

clean:		localclean
			@$(MAKE) clean -s -C $(LIBFT_DIR)
			@echo "\033[0;31m""Clean libft."

fclean:		localclean
			@$(MAKE) fclean -s -C $(LIBFT_DIR)
			@echo "Full clean libft."
			@$(RM) $(NAME)
			@echo "\033[0;31m""Removed executable."

re:			fclean all

.PHONY:		all clean fclean localclean re