# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 16:21:20 by christophed       #+#    #+#              #
#    Updated: 2025/01/03 09:46:34 by christophed      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
TARGET = fdf

# Répertoires
SRC_DIR = src
UTILS_DIR = utils
OBJ_DIR = obj
OBJ_DIR_MAIN = $(OBJ_DIR)/main
INC_DIR = includes
LIBFT_DIR = libft

# Fichiers source et objets
MAIN = $(SRC_DIR)/main.c
SRCS = $(filter-out $(MAIN), $(wildcard $(SRC_DIR)/*.c)) $(wildcard $(UTILS_DIR)/*.c)

OBJS = $(patsubst %.c, $(OBJ_DIR_MAIN)/%.o, $(notdir $(SRCS)))
MAIN_OBJ = $(patsubst %.c, $(OBJ_DIR_MAIN)/%.o, $(notdir $(MAIN)))

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

$(OBJ_DIR_MAIN)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR_MAIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_MAIN)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(OBJ_DIR_MAIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(TARGET)

re: fclean all

.PHONY: all bonus clean fclean re
