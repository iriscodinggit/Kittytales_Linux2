#include "so_long.h"
#include "ft_printf.h"

static int	width_of_map(char *string) //mide el ancho del mapa
{
	int	width;

	width = 0;
	while (string[width] != '\0')
		width++;
	if (string[width - 1] == '\n') //si el último char es \n (es invisible en el .ber porque es como pulsar enter), resta 1 a width
		width--;
	return (width);
}

static int	add_line(t_complete *game, char *line) //line lo recibe de gnl, hace un duplicado del mapa
{
	char	**temporary;
	int		i;

	if (!line) //si no recibe linea de gnl, hemos acabado de leer y retorna 0
		return (0);
	i = 0;
	game->heightmap++;//va a añadir una línea así que height aumenta +1
	temporary = (char **)malloc(sizeof(char *) * (game->heightmap + 1));//crea cajitas de y,temporary se va actualizando,  como duplicado del .ber (ya que no queremos editar sobre el original y perder info de coins y tener que dibujar el mapa de nuevo cada vez) añade + 1 porque esa última cajita contendrá NULL y será la señal de que se ha acabado el map 
	temporary[game->heightmap] = NULL; //ese + 1 en malloc era para añdir el char NULL y avisar de que ya terminó la str
	while (i < game->heightmap - 1) //heighmap menos 1 porque +1 es NULL
	{
		temporary[i] = game->map[i]; //en la primera ronda, map no tiene nada, pero luego sí y copia lo que ya llevaba al temporal
		i++;
	}
	temporary[i] = line; //añadimos en temp la línea de gnl 
	if (game->map)
		free(game->map); //elimina el mapa anterior 
	game->map = temporary; //lo cambia por el nuevo
	return (1);
}

int	map_reading(t_complete *game, char **argv) //opens map and calls gnl to send lines to do a duplicate in add_line (we can't modify the original one because then, afer we finish playing, all coins would be gone as we already ate them in the previous try)
{
	char	*readmap;
	int		line_length;
	int		heightmap;

	game->fd = open(argv[1], O_RDONLY); //abre el .ber y guarda el fd que devuelve open (el lugar donde ha abierto el mapa)
	if (game->fd < 0) //si open devuelve -1, es error porque no ha podido abrirse
		return (0);
	while (1)
	{
		readmap = get_next_line(game->fd); //guarda la línea que ha leído gnl
		if (!add_line(game, readmap)) //si no ha recibido línea, hemos acabado de leer, retorna 0 y break
			break ;
	}
	close (game->fd); //cierra el archivo .ber del que leíamos
	game->widthmap = width_of_map(game->map[0]); //llama a la función widthofmap para ver el width del mapa.
	heightmap = game->heightmap;
	while(heightmap--)
	{
		line_length = width_of_map(game->map[heightmap]);
		if (line_length != game->widthmap)
		{
			ft_printf(RED "\nError\nOh, oh! 🙈\nThe map is not rectangular!\n" RESET);
			exit_point(game);
		}
	}
	return (1);
}
