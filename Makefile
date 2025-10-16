# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: your_username <your_email>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 12:00:00 by your_username    #+#    #+#              #
#    Updated: 2025/01/15 12:00:00 by your_username   ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = fdf

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -DGL_SILENCE_DEPRECATION
INCLUDES = -I. -I./lib/libft -I./lib/get_next_line -I./lib/minilibx

# Libraries
LIBFT_DIR = ./lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

GNL_DIR = ./lib/get_next_line
GNL_FILES = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
GNL_OBJS = $(GNL_FILES:.c=.o)

MLX_DIR = ./lib/minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# Source files
SRC_DIR = ./src
SRCS = fdf.c \
       $(SRC_DIR)/map_parsing.c \
       $(SRC_DIR)/map_utils.c \
       $(SRC_DIR)/graphics_init.c \
       $(SRC_DIR)/projection.c \
       $(SRC_DIR)/drawing.c \
       $(SRC_DIR)/events.c \
       $(SRC_DIR)/memory.c

# Object files
OBJS = $(SRCS:.c=.o)

# Colors for pretty output
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

# Main target
all: $(NAME)

# Build the program
$(NAME): $(LIBFT) $(GNL_OBJS) $(OBJS) $(MLX_LIB)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -lm -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

# Build libft
$(LIBFT):
	@echo "$(BLUE)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)✓ libft compiled!$(RESET)"

# Build MiniLibX
$(MLX_LIB):
	@echo "$(BLUE)Building MiniLibX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR)
	@echo "$(GREEN)✓ MiniLibX compiled!$(RESET)"

# Compile .c files to .o files
%.o: %.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS) $(GNL_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

# Clean everything
fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)✓ Everything cleaned!$(RESET)"

# Rebuild everything
re: fclean all

# Test target for basic MLX functionality
test: $(NAME)
	@echo "$(BLUE)Testing with 42.fdf...$(RESET)"
	@./$(NAME) test_maps/42.fdf

# Debug target
debug: CFLAGS += -g3 -fsanitize=address
debug: $(NAME)

# Check for memory leaks
leaks: $(NAME)
	@echo "$(BLUE)Checking for memory leaks...$(RESET)"
	@leaks --atExit -- ./$(NAME) test_maps/42.fdf

.PHONY: all clean fclean re test debug leaks mlx
