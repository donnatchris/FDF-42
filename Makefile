# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 16:21:20 by christophed       #+#    #+#              #
#    Updated: 2025/01/02 14:45:01 by christophed      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
TARGET = fdf
BONUS_TARGET = NAME OF BONUS

# Répertoires
SRC_DIR = src
UTILS_DIR = utils
OBJ_DIR = obj
OBJ_DIR_MAIN = $(OBJ_DIR)/main
OBJ_DIR_BONUS = $(OBJ_DIR)/bonus
INC_DIR = includes
LIBFT_DIR = libft
BONUS_DIR = bonus

# Fichiers source et objets
MAIN = $(SRC_DIR)/main.c
BONUS_MAIN = $(BONUS_DIR)/main.c
SRCS = $(filter-out $(MAIN), $(wildcard $(SRC_DIR)/*.c)) $(wildcard $(UTILS_DIR)/*.c)
BONUS_SRCS = $(filter-out $(BONUS_MAIN), $(wildcard $(BONUS_DIR)/*.c)) $(filter-out $(MAIN), $(wildcard $(SRC_DIR)/*.c)) $(wildcard $(UTILS_DIR)/*.c)

OBJS = $(patsubst %.c, $(OBJ_DIR_MAIN)/%.o, $(notdir $(SRCS)))
BONUS_OBJS = $(patsubst %.c, $(OBJ_DIR_BONUS)/%.o, $(notdir $(BONUS_SRCS)))
MAIN_OBJ = $(patsubst %.c, $(OBJ_DIR_MAIN)/%.o, $(notdir $(MAIN)))
BONUS_MAIN_OBJ = $(patsubst %.c, $(OBJ_DIR_BONUS)/%.o, $(notdir $(BONUS_MAIN)))

# Options de compilation
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)/includes

# Spécifier le compilateur
CC = gcc

# Options de l'éditeur de liens
LDFLAGS = -L$(LIBFT_DIR) -lft

# Règles
all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN_OBJ) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

bonus: $(BONUS_TARGET)

$(BONUS_TARGET): $(BONUS_OBJS) $(BONUS_MAIN_OBJ) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR_MAIN)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR_MAIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_MAIN)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(OBJ_DIR_MAIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(TARGET) $(BONUS_TARGET)

re: fclean all

.PHONY: all bonus clean fclean re
