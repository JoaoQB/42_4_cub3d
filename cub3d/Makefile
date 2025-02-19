# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 15:39:00 by jqueijo-          #+#    #+#              #
#    Updated: 2025/02/19 13:40:37 by jqueijo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# TODO extract minilibx-linux to includes?
NAME = cub3d
BONUS_NAME = bonus_cub3d

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
CCXX = cc
CXXFLAGS = -Wall -Werror -Wextra -O3 #-Ofast #-g3
SANITIZE = -g -fsanitize=address
VALGRIND = --leak-chek=full --show-leak-kinds=all --track-origin=yes --track-fds=yes

# MLX Compile flags
MLX_LIB	= $(MLX)/libmlx_Linux.a
MLX_LNK	= -L$(MLX) -lmlx -lXext -lX11 -lm -lz

SRCS := ./main.c \
		./init.c \
		./ft_free.c \
		./debug.c \
		./raycasting/raycasting_utils.c \
		./raycasting/raycasting.c \
		./raycasting/trigonometry.c \
		./parsing/parser.c \
		./parsing/parsing_utils.c \
		./parsing/check_map.c \
		./utils/utils_game.c \
		./utils/utils_alloc.c \
		./utils/utils_str.c \
		./utils/utils_str_mod.c \
		./utils/utils_str_search.c \
		./mlx_utils/mlx_utils.c \
		./mlx_utils/mlx_control_toggle.c \
		./mlx_utils/mlx_control.c \
		./mlx_utils/mlx_ui.c \
		./mlx_utils/mlx_draw.c \

SRCS_PATH := $(addprefix $(SRC_PATH)/, $(SRCS))
OBJS = $(SRCS_PATH:%.c=$(OBJ_DIR)/%.o)

all:	$(NAME)

bonus:	fclean
bonus:	$(BONUS_NAME)

$(MLX_LIB):
	-make -s -C $(MLX)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	@echo "$(RED)Compiling object file $<...$(NC)"
	$(CCXX) $(CXXFLAGS) -I$(INCLUDES_DIR) -I$(MLX) -c $< -o $@

$(NAME):	$(OBJS) $(MLX_LIB) $(INCLUDES_DIR)/cub3d.h
	@echo "$(YELLOW)Building program...$(NC)"
	$(CCXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(MLX_LNK)
	@echo "$(GREEN)Build successful!$(NC)"

$(BONUS_NAME):	$(OBJS) $(MLX_LIB) $(INCLUDES_DIR)/cub3d.h
	@echo "$(YELLOW)Building program...$(NC)"
	$(CCXX) $(CXXFLAGS) $(OBJS) -o $(BONUS_NAME) $(MLX_LNK)
	@echo "$(GREEN)Build successful!$(NC)"

valgrind: CXXFLAGS += -g
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
	-make -s -C $(MLX) clean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)


re:	fclean all

debug: CXXFLAGS += $(SANITIZE)
debug: re

.PHONY: all clean fclean re debug valgrind
