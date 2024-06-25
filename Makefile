NAME := so_long

CC := gcc

CFLAGS := -Wall -Wextra -Werror -Iheaders

SOURCE := game_logic/controls.c game_logic/errors.c game_logic/graphics.c game_logic/map.c 
SOURCE2 := game_logic/so_long.c game_logic/validroute.c 
GETNEXTLINE := gnliris/get_next_line_utilsi.c gnliris/get_next_linei.c
FT_PRINTF := printf/ft_printf.c printf/printf_utils.c

# Libraries for Linux
//LIBRARY := -L./minilibx-linux -lminilibx_linux -lXext -lX11
//MINILIBX := minilibx-linux/

all:
	make -C mlx_linux all
	$(CC) $(CFLAGS) $(SOURCE) $(SOURCE2) $(GETNEXTLINE) $(FT_PRINTF) -o $(NAME) -Imlx_linux -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11

clean:
	make clean -C mlx_linux clean
	rm -rf $(NAME)

fclean: clean
	make clean -C mlx_linux clean
	rm -rf $(NAME)

re: fclean all
