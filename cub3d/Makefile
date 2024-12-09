# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 15:39:00 by jqueijo-          #+#    #+#              #
#    Updated: 2024/12/08 17:21:05 by fandre-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 21:06:41 by fandre-b          #+#    #+#              #
#    Updated: 2024/02/16 21:06:41 by fandre-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME := fractol
NAME = cub3d

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m # No Color

RM := -@rm -rf
CC = cc
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
	./utils.c \
	# ./contols.c \
	./raycaster.c \
	
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

# PHONY:	all $(NAME) test clean fclean re
.PHONY: all clean fclean re debug valgrind

