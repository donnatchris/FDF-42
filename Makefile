# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 16:21:20 by christophed       #+#    #+#              #
#    Updated: 2025/01/23 01:41:29 by chdonnat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# OS detection
UNAME := $(shell uname)

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
# minilibx for MacOS or Linux
ifeq ($(UNAME), Darwin)
	MLX_DIR = mlx_mac
else ifeq ($(UNAME), Linux)
	MLX_DIR = mlx_linux
endif

# Main file for mandatory part
MAIN = $(SRC_DIR)/main.c

# Main file for bonus part
BONUS_MAIN = $(BONUS_SRC_DIR)/main.c

# Sources files for mandatory part
SRC = \
	$(SRC_DIR)/error_manager.c \
	$(SRC_DIR)/points.c \
	$(SRC_DIR)/read_and_extract.c \
	$(SRC_DIR)/window_manager.c \
	$(SRC_DIR)/draw.c \
	$(SRC_DIR)/color_manager.c \
	$(SRC_DIR)/key_handler.c \
	$(SRC_DIR)/color_animation.c \
	$(UTILS_DIR)/count_function.c \
	$(UTILS_DIR)/free_functions.c \
	$(UTILS_DIR)/utils_functions.c \
	$(UTILS_DIR)/test_functions.c \
	$(MAIN)

# Sources files for bonus part
BONUS_SRC =	\
	$(BONUS_SRC_DIR)/bonus_error_manager.c \
	$(BONUS_SRC_DIR)/bonus_limits.c \
	$(BONUS_SRC_DIR)/bonus_points.c \
	$(BONUS_SRC_DIR)/bonus_read_and_extract.c \
	$(BONUS_UTILS_DIR)/bonus_count_function.c \
	$(BONUS_UTILS_DIR)/bonus_free_functions.c \
	$(BONUS_UTILS_DIR)/bonus_ft_atoi_long.c \
	$(BONUS_UTILS_DIR)/bonus_test_functions.c \
	$(BONUS_MAIN)

# Objects files for mandatory part
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Objects files for bonus part
BONUS_OBJ = $(BONUS_SRC:$(BONUS_SRC_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)


# Compilation options for MacOS or Linux
ifeq ($(UNAME), Darwin)
	CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR) -I/opt/homebrew/opt/libx11/include -I/opt/homebrew/opt/libxext/include
	LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -L/opt/homebrew/opt/libx11/lib -L/opt/homebrew/opt/libxext/lib -lX11 -lXext -lm -framework OpenGL -framework AppKit
else ifeq ($(UNAME), Linux)
	CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR) -I/usr/include/X11 -I/usr/include/X11/extensions
	LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -L/usr/lib/X11/extensions -lX11 -lXext -lm -lGL -lGLU
endif

# Compiler
CC = cc

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
	rm -f $(TARGET) $(BONUS)

# Rule to recompile the project
re: fclean all

# Phony rule
.PHONY: all clean fclean re bonus
