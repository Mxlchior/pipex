# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: megrelli <melchior.grellier42@gmail.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/07 03:23:55 by megrelli          #+#    #+#              #
#    Updated: 2026/03/12 04:48:45 by megrelli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CFLAGS = -Wall -Werror -Wextra
Libft = ./libft/libft.a
OBJ_DIR = objs

# --- COLORS ---
GREEN	= \033[0;32m
CYAN	= \033[1;36m
RED		= \033[0;31m
BLUE	= \033[0;94m
RESET	= \033[0m

# --- SRCS ---
SRCS = srcs/main.c srcs/path.c srcs/child.c srcs/utils.c srcs/split.c

# --- OBJS ---
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# --- RULES ---
all: $(NAME)

$(Libft):
	@echo "$(CYAN)┌── $(BLUE)Compiling Libft...$(RESET)"
	@make -C ./libft > /dev/null
	@echo "$(CYAN)└── $(BLUE)Libft OK$(RESET)"

$(NAME): $(OBJS) $(Libft)
	@echo "\n$(GREEN)Building $(NAME)...$(RESET)"
	@cc $(CFLAGS) $(OBJS) $(Libft) -o $(NAME)
	@echo "$(GREEN)Done! $(NAME) is ready $(RESET)\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)│ $(BLUE) Compiling $<...$(RESET)"
	@cc $(CFLAGS) -c $< -o $@

clean:
	@echo "\n$(GREEN)Cleaning objects...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C ./libft clean > /dev/null

fclean: clean
	@echo "$(RED)Cleaning executables...$(RESET)"
	@rm -f $(NAME)
	@make -C ./libft fclean > /dev/null

re: fclean all

.PHONY: all clean fclean re
