#include "so_long.h"
#include "get_next_linei.h"
#include "ft_printf.h"

//MUCHAS STATIC, PARA QUE MANTENGAN EL VALOR INDEPENDIENTEMENTE DE QUE ACABE LA FUNCIÓN, NO HACE FALTA STATIC CREO PORQUE LAS DOS PRIMERAS SOLO LAS LLAMO 1 VEZ

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

void check_extension(t_complete *game, char *path) //checks if extension is .ber
{
    int len;
    char *expected_extension = ".ber";

    len = ft_strlen(path); //measures length of the argument (maps/map2.ber would be 13)
    if (len < 4 || ft_strncmp(path + len - 4, expected_extension, 4) != 0) //if len is less than 4, .ber doesn't fit cause it has 4, and then it compares .ber with the four last chars of path (should be .ber)
    {
        ft_printf(RED "\nError\nMap's extension must be \".ber\"🙈" RESET);
	exit_point(game);
    }
}

static int	horizontalwall(t_complete *game) //mira a ver si hay muros en las filas de arriba de abajo (rodeado de muros
{
	int	x;

	x = 0;
	while (x < game->widthmap) //mientras que no nos pasemos cajitas de width 
	{
		if (!(game->map[0][x] == '1' && game->map[game->heightmap - 1][x] == '1')) //si no son muros, devuelve 0, es inválido
			return (0); //mapa no válido
		x++;
	}
	return (1); //mapa sí es válido
}

static int	verticalwall(t_complete *game) //comprueba que haya paredes en las columnas exteriores verticales (por lo de que esté rodeado de muros)
{
	int	y;

	y = 0;
	while (y < game->heightmap) //mientras que no nos pasemos de cajitas de height
	{
		if (!(game->map[y][0] == '1' && game->map[y][game->widthmap - 1] == '1')) //si no son muros, devuelve 0, es inválido
			return (0); //mapa no válido
		y++;
	}
	return (1); //mapa válido
}

static void	if_walls(t_complete *game)
{
	int	verticalwalls;
	int	horizontalwalls;

	verticalwalls = verticalwall(game); //mira a ver si están las paredes verticales
	horizontalwalls = horizontalwall(game); //mira a ver si están las paredes horizontales
	if (!verticalwalls || !horizontalwalls) //Si alguna de las dos retorna 0, mandar error de que no es válido
	{
		ft_printf("RED \nError\n🚧 Oh, crumbs! The map is not surrounded by walls! 🚧\n" RESET);
		exit_point(game);
	}
}

static void	count_checker(t_complete *game, int height, int width) //checks for invalid chars and counts how many there are of each
{
	//Checks if there's any invalid char in the map like "F" or "%"
	if (game->map[height][width] != '1' &&
		game->map[height][width] != '0' &&
		game->map[height][width] != 'P' &&
		game->map[height][width] != 'E' &&
		game->map[height][width] != 'C' &&
		game->map[height][width] != '\n') //Vale, el actually de a continucación es erróneo, he probaado a quitarlo y no funciona, supongo que porque aunque tu no escribas \n literalmente en el .ber, el hecho de pulsar enter crea una new line y se interpreta como tal. ACTUALLY, creo que no es necesario porque no puedes ponerlo en el mapa.  no olvides el newline, también es un char válido (para avisar que acabaste la fila)
	{
		ft_printf(RED "\nError\nOh, oh! 🙈\nThere's an invalid character in the map: %c\n", game->map[height][width], RESET); //Tells you where the wrong char is
		exit_point(game);
	}
	if (game->map[height][width] == 'C')
			game->coincount++; //Counts how many collectables there are (i think) should rename it to collectablecount
	if (game->map[height][width] == 'P') //AQUI PUEDO AÑADIR LAS COORDENADAS DEL PLAYER CREANDO UN NUEVO ELEMENTO EN STRUCT
	{
		game->y_axis = height;
		game->x_axis = width;
		game->playercount++; //counts how many players there are (there can only be one)
	}
	if (game->map[height][width] == 'E')
			game->exitcount++; //counts how many exits there are (there can only be one)
} //no hace falta que retorne nada porque es 

void	character_valid(t_complete *game)
{
	int	height;
	int	width;

	height = 0;
	while (height < game->heightmap - 1) //hasta que no nos pasemos de cajitas de y
	{
		width = 0;
		while (width <= game->widthmap) //hasta que no nos pasemos de cajitas de x
		{
			count_checker(game, height, width); //va checkeando char por char, fila por fila
			width++;
		}
		height++;
	}
	if (!(game->playercount == 1 && game->coincount >= 1
			&& game->exitcount == 1)) //solo puede haber 1 jugador, al menos 1 collectible? y solo 1 exit
	{
		ft_printf(RED "\nError\nOh, oh! 🙈\nThe map's route or number of players, exits or collectables is wrong!\n" RESET);
		exit_point(game);
	}
}

void	check_errors(t_complete *game)
{
	if_walls(game); //esta función checkea que el mapa este rodeado de muros (1)
	character_valid(game); //checkea que no haya chars invalidos y cuenta que haya el número correcto de cada
}
