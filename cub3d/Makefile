# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 15:39:00 by jqueijo-          #+#    #+#              #
#    Updated: 2024/12/18 15:25:53 by jqueijo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC_PATH = ./srcs
SRC = $(SRC_PATH)/main.c \
	$(SRC_PATH)/init.c \
	$(SRC_PATH)/ft_free.c \
	$(SRC_PATH)/utils.c \
	$(SRC_PATH)/raycasting/raycasting.c \
	$(SRC_PATH)/raycasting/raycasting_init.c \
	$(SRC_PATH)/raycasting/raycasting_utils.c \
	$(SRC_PATH)/raycasting/raycasting_trign_utils.c \
	$(SRC_PATH)/raycasting/draw_utils.c \

CC = cc
MINILIBX_FLAGS= -L./includes/minilibx-linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -Ofast
CFLAGS = -Wall -Werror -Wextra -O3 #-Ofast #-g3
SANITIZE = -g -fsanitize=address
VALGRIND = valgrind --leak-check=yes --show-leak-kinds=all --track-origins=yes

OBJ_DIR = ./obj
OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_DIR)/%.o)
MLX_DIR = ./includes/minilibx-linux

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m # No Color

all: $(NAME)

$(NAME): $(OBJ) $(MLX_DIR)/libmlx_Linux.a
	@echo "$(YELLOW)Linking...$(NC)"
	$(CC) $(CFLAGS) $(OBJ) $(MINILIBX_FLAGS) -o $(NAME)
	@echo "$(GREEN)Build successful!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

$(MLX_DIR)/libmlx_Linux.a:
	@echo "$(YELLOW)Building MiniLibX...$(NC)"
	$(MAKE) -C $(MLX_DIR)

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

