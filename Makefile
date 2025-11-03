NAME = fdf

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -DGL_SILENCE_DEPRECATION
INCLUDES = -I. -I./lib/libft -I./lib/get_next_line -I./lib/ft_printf -I./lib/minilibx

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR = lib/ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

GNL_DIR = lib/get_next_line
GNL_FILES = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
GNL_OBJS = $(GNL_FILES:.c=.o)

MLX_DIR = lib/minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC_DIR = ./src
SRCS = fdf.c \
       $(SRC_DIR)/map_parsing.c \
       $(SRC_DIR)/map_utils.c \
       $(SRC_DIR)/graphics_init.c \
       $(SRC_DIR)/projection.c \
       $(SRC_DIR)/drawing.c \
       $(SRC_DIR)/drawing_utils.c \
       $(SRC_DIR)/events.c \
       $(SRC_DIR)/mouse.c \
       $(SRC_DIR)/keyboard.c \
       $(SRC_DIR)/memory.c \
       $(SRC_DIR)/color.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(FT_PRINTF) $(GNL_OBJS) $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(MLX_FLAGS) -L$(FT_PRINTF_DIR) -lftprintf -L$(LIBFT_DIR) -lft -lm -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(GNL_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

test: $(NAME)
	./$(NAME) test_maps/42.fdf

debug: CFLAGS += -g3 -fsanitize=address
debug: $(NAME)

leaks: $(NAME)
	leaks --atExit -- ./$(NAME) test_maps/42.fdf

.PHONY: all clean fclean re test debug leaks
