# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 15:39:00 by jqueijo-          #+#    #+#              #
#    Updated: 2024/11/25 16:18:53 by jqueijo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = $(SRC_PATH)/main.c \


CC = cc
MINILIBX_FLAGS= -Lminilibx-linux -l:libmlx_Linux.a -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -Ofast
CFLAGS = -Wall -Werror -Wextra -O3 #-Ofast #-g3
SANITIZE = -g -fsanitize=address
VALGRIND = --leak-chek=full --show-leak-kinds=all --track-origin=yes --track-fds=yes

SRC_PATH = ./srcs
OBJ_DIR = ./obj

OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_DIR)%.o)

MLX_DIR = ./includes/minilibx-linux
MLX = make -C $(MLX_DIR)

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m # No Color

all: $(NAME)

$(NAME): $(OBJ) $(MLX)
	@echo "$(YELLOW)Linking...$(NC)"
	$(CC) $(CFLAGS) $(OBJ) $(MINILIBX_FLAGS) -o $(NAME)
	@echo "$(GREEN)Build successful!$(NC)"

$(OBJ_DIR)%.o: $(SRC_PATH)/%.C
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(YELLOW)Cleaning executable...$(NC)"
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS += $(SANITIZE)
debug: re

valgrind: CFLAGS += -g
valgrind: re
	@echo "$(YELLOW)Running Valgrind...$(NC)"
	valgrind $(VALGRIND) ./$(NAME)

.PHONY: all clean fclean re debug valgrind

