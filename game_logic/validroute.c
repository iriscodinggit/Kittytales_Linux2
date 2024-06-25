#include "so_long.h"
#include "ft_printf.h"

void	fill(t_complete *game, char **tab, int width, int height, int y_player, int x_player, char to_fill)
{
	if (y_player < 0 || y_player >= height|| x_player < 0 || x_player >= width || tab[y_player][x_player] == to_fill || tab[y_player][x_player] == '1') //Si es P o 1 no pasa ya por ahí 
		return; //gestionar lo de arriba porque la primera vez begin sí es P
	if (tab[y_player][x_player] == 'C')
		game->coinparse++;
	if (tab[y_player][x_player] == 'E')
	{
		game->exitparse++;
		return; //porque si es exit, en el caso de que hubiera CEP, no puedes pasar sobre la E de exit
	}
	tab[y_player][x_player] = 'P'; //rellena con Ps
	fill(game, tab, width, height, y_player, (x_player - 1), to_fill);
	fill(game, tab, width, height, y_player, (x_player + 1), to_fill);
	fill(game, tab, width, height, (y_player - 1), x_player, to_fill);
	fill(game, tab, width, height, (y_player + 1), x_player, to_fill);
}

void	flood_fill(t_complete *game, char **tab, int width, int height, int y_player, int x_player) //check args
{
	fill(game, tab, width, height, y_player, x_player, 'P');
}

char** make_area(t_complete *game, char** zone)
{
	char** new;
    
	new = malloc(sizeof(char*) * game->heightmap);
	for (int i = 0; i < game->heightmap; ++i)
	{
		new[i] = malloc(sizeof(char) * (game->widthmap + 1));
		for (int j = 0; j < game->widthmap; ++j)
			new[i][j] = zone[i][j];
		new[i][game->widthmap] = '\0';	
	}
	return (new);
	}

void valid_route(t_complete *game)
{
	char**  area = make_area(game, game->map); //crea una copia sobre la que modificar el mapaCAMBIAR ZONE POR EL PATH DE FAB, VER DE DONDE SACA PATH FAB
	area[game->y_axis][game->x_axis] = 'B'; //cambio P por B porque si no, en fill, como es una P, retornaría 0 en el primer if
    flood_fill(game, area, game->widthmap, game->heightmap, game->y_axis, game->x_axis); //change begin for player pos, llena todo de Ps
 	if (game->coincount != game->coinparse

                        || game->exitcount != game->exitparse)
        {
                ft_printf(RED"\nError\nOh, oh! 🙈\nThe exit or some collectables are not accessible!\n"RESET);
                exit_point(game);
        }
}

//si hay al menos 1 collectable llama a esta función (después de la que cuenta chars de cada tipo)
//hace un floodfill llenando todo de Ps y cada vez que hay un collectible, suma 1 y si toca salida, también +1. Devuelve si encuentra una P o un 1(muro)
//al final mira a ver si el número de collectibles es igual al inicial y si el de salida es 1
//si sí, es válido, si no, es erróneo