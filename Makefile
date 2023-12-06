# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: damachad <damachad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 10:57:36 by damachad          #+#    #+#              #
#    Updated: 2023/12/06 16:45:52 by damachad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ COLORS /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ COMMANDS /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
CC = cc
RM = rm -rf

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ FLAGS _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
CFLAGS 	= -Wall -Werror -Wextra -g
MK_FLAG = --no-print-directory
LFLAGS 	= -L ./$(LIBFT_DIR) -lft -lreadline

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ PATHS _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
INC			= includes
SRC_DIR		= srcs
OBJ_DIR		= objs
LIBFT_DIR	= libft
SUB_DIR		= builtins clean_and_error environment executor expander heredoc lexer parser prompt signals
OBJS_DIRS	= $(foreach dir, $(SUB_DIR), $(addprefix $(OBJ_DIR)/, $(dir)))

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ FILES _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
NAME 		= minishell
LIBFT		= $(LIBFT_DIR)/libft.a
FILES 		= builtins/builtin_main builtins/builtin_pwd builtins/builtin_echo builtins/builtin_env \
		builtins/builtin_cd builtins/builtin_exit builtins/builtin_unset builtins/builtin_export builtins/builtin_export_print \
		clean_and_error/clean clean_and_error/clean2 clean_and_error/clean3 clean_and_error/error \
		environment/env_utils environment/env environment/envlst_use \
		executor/executor executor/command_handling executor/executor_utils executor/path\
		expander/expander expander/expand_arg expander/expander_utils \
		heredoc/heredoc_utils heredoc/heredoc heredoc/open_pipe heredoc/open_pipe_2 \
		lexer/lexer_utils lexer/lexer \
		parser/parser_utils parser/parser \
		prompt/prompt \
		signals/signals signals/signals2 \
		main print_stuff
SRC 		= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
OBJ 		= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ RULES _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME) -I $(INC)
	@echo "[$(GREEN)$(NAME) created$(RESET)]"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJS_DIRS)
	@echo "[$(GREEN)objs directory created$(RESET)]"

$(LIBFT):
	@make $(MK_FLAG) -C ./$(LIBFT_DIR)

clean:
	@$(RM) $(OBJ_DIR) $(OBJ_BNS_DIR)
	@make $(MK_FLAG) -C ./$(LIBFT_DIR) clean
	@echo "[$(RED)objs removed$(RESET)]"
	@$(RM) output.log
	@$(RM) readline.supp

fclean: clean
	@$(RM) $(NAME) $(NAME_BNS) $(LIBFT)
	@echo "[$(RED)executables and $(LIBFT) removed$(RESET)]"

re: fclean all

# valgrind --leak-check=full -s --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes

leaks: readline.supp
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --log-file=output.log ./minishell

readline.supp:
	echo "{" > readline.supp
	echo "    leak readline" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:readline" >> readline.supp
	echo "}" >> readline.supp
	echo "{" >> readline.supp
	echo "    leak add_history" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:add_history" >> readline.supp
	echo "}" >> readline.supp

.PHONY: all clean fclean re test
