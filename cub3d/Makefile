# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 15:39:00 by jqueijo-          #+#    #+#              #
#    Updated: 2024/12/12 12:48:51 by jqueijo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m # No Color

RM := -@rm -rf
CC = gcc
CFLAGS = -Wall -Werror -Wextra -O3 #-Ofast #-g3
SANITIZE = -g -fsanitize=address
VALGRIND = --leak-chek=full --show-leak-kinds=all --track-origin=yes --track-fds=yes

OBJ_DIR := obj
INCLUDES_DIR := includes
SRC_PATH := srcs
MLX		:= ./includes/minilibx-linux

SRCS := init.c \
	main.c\
	check_map.c \
	utils.c \
	utils_str.c\
	utils_alloc.c\
	mlx_init.c\
	mlx_control.c \
	hash_table.c \
	# ./raycaster.c \
	
SRCS_PATH := $(addprefix $(SRC_PATH)/, $(SRCS))
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS_PATH:.c=.o))

MLX_LNK	= -L$(MLX) -lmlx -lXext -lX11 -lm -lz
MLX_LIB	= $(addprefix $(MLX),mlx.a)

all:	$(NAME)

$(MLX_LIB):
	-make -s -C $(MLX)
	
$(OBJ_DIR)/%.o:	%.c $(MLX_LIB)
	mkdir -p $(dir $@)
	@echo "$(RED)Compiling object file $<...$(NC)"
	$(CC) $(CFLAGS) -I$(MLX) -I$(INCLUDES_DIR) -c $< -o $@ $(MLX_LNK)

$(NAME):	$(OBJS)
	@echo "$(YELLOW)Building program...$(NC)"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_LNK)
	@echo "$(GREEN)Build successful!$(NC)"

# $(OBJ_DIR)/%.o: $(SRC_PATH)/%.C
# 	@mkdir -p $(OBJ_DIR)
# 	@echo "$(YELLOW)Compiling $<...$(NC)"
# 	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@


# $(NAME): $(OBJ) $(MLX)
# 	@echo "$(YELLOW)Linking...$(NC)"
# 	$(CC) $(CFLAGS) $(OBJ) $(MINILIBX_FLAGS) -o $(NAME)
# 	@echo "$(GREEN)Build successful!$(NC)"

test:
	@echo "<Still need to set up>"

clean:
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	-make -s -C $(MLX) clean
	$(RM) $(OBJ_DIR)
# make -C $(FT) clean
#	rm -rf $(OBJ_DIR)

fclean:	clean
	@echo "$(YELLOW)Cleaning executable...$(NC)"
	-make -s -C $(MLX) fclean
	$(RM) $(NAME)


re:	fclean all

debug: CFLAGS += $(SANITIZE)
debug: re

valgrind: CFLAGS += -g
valgrind: re
	@echo "$(YELLOW)Running Valgrind...$(NC)"
	valgrind $(VALGRIND) ./$(NAME)

.PHONY: all clean fclean re debug valgrind

SRC_PATH = ./srcs
SRC = $(SRC_PATH)/main.c \
	$(SRC_PATH)/init.c \
	$(SRC_PATH)/ft_free.c \
	$(SRC_PATH)/raycasting/raycasting.c \
	$(SRC_PATH)/raycasting/raycasting_init.c \
	$(SRC_PATH)/raycasting/raycasting_utils.c \
	$(SRC_PATH)/raycasting/raycasting_trign_utils.c \
	$(SRC_PATH)/raycasting/raycasting_math_utils.c \
	$(SRC_PATH)/raycasting/raycasting_horizontal.c \
	$(SRC_PATH)/raycasting/raycasting_vertical.c \
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

