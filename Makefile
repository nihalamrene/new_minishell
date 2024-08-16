
NAME		=	minishell
CC			=	cc

CFLAGS		=	 -Werror -Wextra -Wall -lreadline #-fsanitize=address -g3
RM			=	rm -rf
SRCS		=	main.c my_malloc.c src/lexer/tokenizer_line.c src/tools/lst_addback_m.c \
				src/tools/lst_env.c src/envir/environment.c src/expand/expansion.c \
				src/expand/expansion2.c src/expand/expansion3.c  \
				src/lexer/checks.c src/parse/parsing.c src/parse/parsing2.c src/tools/lst_redir.c \
				src/tools/lst_cmd.c \
				src/exec/exe_cmd.c src/exec/exec.c src/exec/handel_redi.c 

OBJS		= ${SRCS:.c=.o}

all			:	$(NAME)

$(NAME)		: $(SRCS)
			@printf "$(YELLOW)\rMinishell loading ...⏳\n$(RESET)"
			@make -C libft
			@$(CC) $(CFLAGS) $(SRCS) libft/libft.a -o $(NAME) -lreadline 
			@printf "$(GREEN)\rMinishell Ready \n$(RESET)"    #### why /r ??
			
clean		:
			@printf "$(RED)\rCleaning ... 🗑️\n"
			@$(RM) $(OBJS)
			@make clean -C libft

fclean		: clean
			@$(RM) $(NAME)
			@make fclean -C libft

re			: fclean all

.PHONY: all clean fclean re