# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 16:21:20 by christophed       #+#    #+#              #
#    Updated: 2025/01/28 16:42:16 by chdonnat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Mac compilation
ifeq ($(UNAME), Darwin)
	CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR) -I/opt/homebrew/opt/libx11/include -I/opt/homebrew/opt/libxext/include
endif
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -L/opt/homebrew/opt/libx11/lib -L/opt/homebrew/opt/libxext/lib -lX11 -lXext -lm -framework OpenGL -framework AppKit
# else ifeq ($(UNAME), Linux)

# Name of the executable for mandatory part
TARGET = fdf

# Name of the executable for bonus part
BONUS = fdf_bonus

# Directories for mandatory part
SRC_DIR = mandatory/src
UTILS_DIR = mandatory/utils
INC_DIR = mandatory/include
OBJ_DIR = obj/mandatory

# Directories for bonus part
BONUS_SRC_DIR = bonus/src
BONUS_UTILS_DIR = bonus/utils
BONUS_INC_DIR = bonus/include
BONUS_OBJ_DIR = obj/bonus

# Directories for common part
LIBFT_DIR = libft
# minilibx for Linux
MLX_DIR = mlx_linux

# Main file for mandatory part
MAIN = $(SRC_DIR)/main.c

# Main file for bonus part
BONUS_MAIN = $(BONUS_SRC_DIR)/main.c

# Sources files for mandatory part	$(SRC_DIR)/iso.c
SRC = \
	$(SRC_DIR)/error_manager.c \
	$(SRC_DIR)/render.c \
	$(SRC_DIR)/menu.c \
	$(SRC_DIR)/iso.c \
	$(SRC_DIR)/perspective.c \
	$(SRC_DIR)/read_and_extract.c \
	$(SRC_DIR)/initialize.c \
	$(SRC_DIR)/draw.c \
	$(SRC_DIR)/color_manager.c \
	$(SRC_DIR)/key_handler.c \
	$(SRC_DIR)/color_animation.c \
	$(UTILS_DIR)/count_function.c \
	$(UTILS_DIR)/free_functions.c \
	$(UTILS_DIR)/utils_functions.c \
	$(MAIN)

# Sources files for bonus part
BONUS_SRC =	\
	$(BONUS_SRC_DIR)/error_manager.c \
	$(BONUS_SRC_DIR)/render.c \
	$(BONUS_SRC_DIR)/menu.c \
	$(BONUS_SRC_DIR)/iso.c \
	$(BONUS_SRC_DIR)/perspective.c \
	$(BONUS_SRC_DIR)/read_and_extract.c \
	$(BONUS_SRC_DIR)/initialize.c \
	$(BONUS_SRC_DIR)/draw.c \
	$(BONUS_SRC_DIR)/color_manager.c \
	$(BONUS_SRC_DIR)/key_handler.c \
	$(BONUS_SRC_DIR)/color_animation.c \
	$(BONUS_UTILS_DIR)/count_function.c \
	$(BONUS_UTILS_DIR)/free_functions.c \
	$(BONUS_UTILS_DIR)/utils_functions.c \
	$(BONUS_MAIN)

# Objects files for mandatory part
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Objects files for bonus part
BONUS_OBJ = $(BONUS_SRC:$(BONUS_SRC_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)


# Compilation options for Linux
CFLAGS = -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR) -I/usr/include/X11 -I/usr/include/X11/extensions

# Compiler
CC = cc -g

# Rule to compile the mandatory part
all: $(TARGET)
$(TARGET): $(OBJ) $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

# Rule to compile the bonus part
bonus: $(BONUS)
$(BONUS): $(BONUS_OBJ) $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) -o $(BONUS) $^ $(LDFLAGS)

# Rule to compile libft
$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

# Rule to compile mlx
$(MLX_DIR)/libmlx.a:
	$(MAKE) -C $(MLX_DIR)

# Rules to compile the objects files of the mandatory part
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rules to compile the objects files of the bonus part
$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_UTILS_DIR)/%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the objects files
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf obj

# Rule to clean the objects files and the executables
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(TARGET) $(BONUS)

# Rule to recompile the project
re: fclean all

# Phony rule
.PHONY: all clean fclean re bonus
