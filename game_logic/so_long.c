#include "so_long.h"
#include "ft_printf.h"

static void	*ft_memset(void *b, int c, size_t length) //memset llena toda la struct game de 0, coge desde que posición empieza a rellenar, con que símbolo rellena y cuántos símbolos
{
	unsigned char	*p; //un cursor

	p = (unsigned char *)b; //iguala el cursor a donde empezar a rellenar
	while (length--) //hasta llegar a 0
		*p++ = (unsigned char)c; //rellena con ese char
	return (b);
}

int	exit_point(t_complete *game) //para el juego: cierra la ventana y libera memoria(puntero a la mlx, línea a línea del mapa y el mapa (incluido la línea de NULL)
{
	int	line;

	line = 0;
	if (game->winpointer)
		mlx_destroy_window(game->mlxpointer, game->winpointer);
	free(game->mlxpointer);
	while (line < game->heightmap - 1)
		free(game->map[line++]);
	free(game->map);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_complete	game; //que es game?

	if (argc != 2) //solo puede haber 2 params, el nombre del programa y la ruta del mapa
	{
		ft_printf(RED "\nError\nWrong arguments!🙈" RESET);
		return (0);
	}
	ft_memset(&game, 0, sizeof(t_complete)); //initialises the game structure to zeros before it is populated with data
	check_extension(&game, argv[1]); //se asegura de que la extensión sea .ber (no vale .c)
	map_reading(&game, argv); //abre el .ber y añade líneas una a una al mapa
	check_errors(&game); //mira errores
	valid_route(&game); //mira si la exit y todos los collectables son reachable
	game.mlxpointer = mlx_init(); //empieza el tinglado
	game.winpointer = mlx_new_window(game.mlxpointer, (game.widthmap * 160),
			(game.heightmap * 160), "KittyTales by Iris <3"); //crea la window
	place_images_in_game(&game); //loads images but doeesn't show them yet
	adding_in_graphics(&game); //actually places images in the game for us to see
	mlx_key_hook(game.winpointer, controls_working, &game);//espera a que el jugador pulsa alguna teclas y llama a controls para ver si es a,w,s o d o escape
	mlx_hook(game.winpointer, 33, 0, (void *)exit, 0); //esto es por si pulsas la cruz roja, 33 es el keycode de la cruz roja, 0 es la mask (en ios da igual), exit es la función a la que llamar cuando sucede (en este caso exit, se para) y el otro 0 no nos interesa así que blank
	mlx_loop(game.mlxpointer); //espera en loop a ver si pasa el key_hook
}
