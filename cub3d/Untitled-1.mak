SRC_PATH = ./srcs
SRC = $(SRC_PATH)/main.c \

MINILIBX_FLAGS= -L./includes/minilibx-linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -Ofast
CFLAGS = -Wall -Werror -Wextra -O3 #-Ofast #-g3
SANITIZE = -g -fsanitize=address
VALGRIND = valgrind --leak-check=yes --show-leak-kinds=all --track-origins=yes

OBJ_DIR = ./obj
OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_DIR)/%.o)
MLX_DIR = ./includes/minilibx-linux


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
