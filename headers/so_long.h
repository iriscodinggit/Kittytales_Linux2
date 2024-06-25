#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h> //para el write de gnl
# include <stdio.h> //para perror
# include <fcntl.h> //para open y close
# include "get_next_linei.h"
# include "../mlx_linux/mlx.h"

typedef struct t_start
{
	int		fd;
	int		heightmap;
	int		widthmap;
	int		playercount;
	int		coinparse; //just checks how many coins CAN be collected
	int		coincount;
	int		exitparse; //checks how many exits CAN be accessed
	int		exitcount;
	int		x_axis; //x players coordinates
	int		y_axis; //y players coordinates
	int		counter; //esto que cuenta

	char	**map;

	void	*floor;
	void	*barrier;
	void	*player;
	void	*exit;
	void	*collectable;
	void	*mlxpointer;
	void	*winpointer;

}	t_complete;

int		exit_point(t_complete *game);
int		map_reading(t_complete *game, char **argv);
int		controls_working(int command, t_complete *game);
void	valid_route(t_complete *game);
void	adding_in_graphics(t_complete *game);
void	place_images_in_game(t_complete *game);
void	check_errors(t_complete *game);
void	check_extension(t_complete *game, char *path);

// Colours
# define RED "\033[0;31m" //the \033 is the escape character (signals the start), 31 is the color code, m is mode
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define PINK "\033[38;5;218m" //has more numbers because it's int RGB, ANSI palette is limited
# define CYAN "\033[0;36m"
# define WHITE "\033[0;97m"
# define RESET "\033[0m"

#endif
