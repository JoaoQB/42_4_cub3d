# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 15:39:00 by jqueijo-          #+#    #+#              #
#    Updated: 2025/01/02 20:47:41 by jqueijo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# TODO extract minilibx-linux to includes?
NAME = cub3d

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m # No Color

# Folders
SRC_PATH := srcs
OBJ_DIR := obj
INCLUDES_DIR := includes
MLX := ./includes/minilibx-linux

# Compile flags
RM := -@rm -rf
CC = cc
CFLAGS = -Wall -Werror -Wextra -O3 #-Ofast #-g3
SANITIZE = -g -fsanitize=address
VALGRIND = --leak-chek=full --show-leak-kinds=all --track-origin=yes --track-fds=yes

# MLX Compile flags
MLX_LIB	= $(MLX)/libmlx_Linux.a
MLX_LNK	= -L$(MLX) -lmlx -lXext -lX11 -lm -lz

SRCS := main.c \
		init.c \
		init_utils.c \
		init_test.c \
		ft_free.c \
		mlx_utils/mlx_control.c \
		mlx_utils/mlx_init.c \
		mlx_utils/mlx_utils.c \
		parsing/check_map.c \
		parsing/parsing_utils.c \
		raycasting/draw_utils.c \
		raycasting/raycasting.c \
		raycasting/raycasting_debug.c \
		raycasting/raycasting_init.c \
		raycasting/raycasting_trign_utils.c \
		raycasting/raycasting_utils.c \
		raycasting/texture_init.c \
		utils/utils.c \
		utils/utils_str.c \
		utils/utils_str_2.c \
		utils/utils_alloc.c \
		utils/hash_table.c \

SRCS_PATH := $(addprefix $(SRC_PATH)/, $(SRCS))
# OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS_PATH:.c \=.o))
OBJS = $(SRCS_PATH:%.c=$(OBJ_DIR)/%.o)


all:	$(NAME)

$(MLX_LIB):
	-make -s -C $(MLX)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	@echo "$(RED)Compiling object file $<...$(NC)"
	$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -I$(MLX) -c $< -o $@

$(NAME):	$(OBJS) $(MLX_LIB) $(INCLUDES_DIR)/cub3d.h
	@echo "$(YELLOW)Building program...$(NC)"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_LNK)
	@echo "$(GREEN)Build successful!$(NC)"

valgrind: CFLAGS += -g
valgrind: re
	@echo "$(YELLOW)Running Valgrind...$(NC)"
	valgrind $(VALGRIND) ./$(NAME)

test:
	@echo "<Still need to set up>"

clean:
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	-make -s -C $(MLX) clean
	$(RM) $(OBJ_DIR)

fclean:	clean
	@echo "$(YELLOW)Cleaning executable...$(NC)"
	-make -s -C $(MLX) fclean
	$(RM) $(NAME)


re:	fclean all

debug: CFLAGS += $(SANITIZE)
debug: re

.PHONY: all clean fclean re debug valgrind


