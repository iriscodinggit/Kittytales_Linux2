#include "so_long.h"
#include "ft_printf.h"

void	place_player(t_complete *game, int height, int width)
{
	mlx_put_image_to_window(game->mlxpointer,
		game->winpointer, game->player, width * 160, height * 160); //Cada tile de 160x1600 pixels, las imagenes tienen que medir eso
	game->y_axis = height;
	game->x_axis = width; //update coordinates of the player
}

void	place_collectable(t_complete *game, int height, int width)
{
	mlx_put_image_to_window(game->mlxpointer,
		game->winpointer, game->collectable, width * 160, height * 160); //coordinates where the image will be placed
}

void	place_images_in_game(t_complete *game) //loads images but doesn't show them yet, just prepares them
{
	int	i;
	int	j;

	game->floor = mlx_xpm_file_to_image(game->mlxpointer,
			"textures/bigflowr.xpm", &i, &j); //i y j se rellenan automáticamente cuando envias la imagen
	game->barrier = mlx_xpm_file_to_image(game->mlxpointer,
			"textures/bigwall.xpm", &i, &j);
	game->player = mlx_xpm_file_to_image(game->mlxpointer,
			"textures/bigcatgood.xpm", &i, &j);
	game->exit = mlx_xpm_file_to_image(game->mlxpointer,
			"textures/bigdoor.xpm", &i, &j);
	game->collectable = mlx_xpm_file_to_image(game->mlxpointer,
			"textures/bigcoin.xpm", &i, &j);
}

void	adding_in_graphics(t_complete *game)
{
	int	height;
	int	width;
	
	height = 0;
	while (height < game->heightmap)
	{
		width = 0;
		while (game->map[height][width])
		{
			if (game->map[height][width] == '1')
				mlx_put_image_to_window(game->mlxpointer,
					game->winpointer, game->barrier, width * 160, height * 160);
			if (game->map[height][width] == 'C')
				place_collectable(game, height, width);
			if (game->map[height][width] == 'P')
				place_player(game, height, width);
			if (game->map[height][width] == 'E')
				mlx_put_image_to_window(game->mlxpointer,
					game->winpointer, game->exit, width * 160, height * 160); //el 3er parámetro es donde guarda la imagen
			if (game->map[height][width] == '0')
				mlx_put_image_to_window(game->mlxpointer,
					game->winpointer, game->floor, width * 160, height * 160);
			width++;
		}
		height++;
	}
}
