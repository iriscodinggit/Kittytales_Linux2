#include "so_long.h"
#include "ft_printf.h"

static int	right_move(t_complete *game, int i, int j) //right move is any move except for a wall(1)
{
	if (game->map[j][i] == 'E') //if you reach the exit
	{
		if (game->coincount != 0) //if you haven't collected all the collectables, you can't exit
			return (0);
		ft_printf(PINK "\nThe kitty is forever grateful to you! Meow! 🐱💕\n" RESET);
		exit_point(game); //you leave the game
	}
	if (game->map[j][i] == '0') //if you step on floor
	{
		game->map[j][i] = 'P'; //update the map with the player's position
		game->x_axis = i; //update the player's coordinates
		game->y_axis = j;
		game->counter++; //this is a step counter (how many movements you've done so far)
	}
	if (game->map[j][i] == 'C') //if you step on a collectible
	{
		game->map[j][i] = 'P';
		game->x_axis = i;
		game->y_axis = j;
		game->coincount--; //one less collectible to finish!
		game->counter++;
	}
	return (1); //it returns 1 if the movement was done or 0 if it wasn't (the latter just happens when the exit is still blocked)
}

static int	keyboard_w_s(t_complete *game, int movement) //if you move up or down (y axis)
{
	int	i; //x coord
	int	j; //y coord
	int	k; //1 if its a valid move, 0 if it was an exit and therefore, not a valid move

	i = game->x_axis;
	j = game->y_axis;
	if (movement == 119) //this is the keycode for up (W)
	{
		j--; //updates pos by 1 up the screen (remember that in computers, coordinates start in the top left side)
		if (game->map[j][i] == '1') //if it's a wall
			return (0); //its invalid and doesn't move anything
		k = right_move(game, i, j); //if it's not a wall, then it's a right move and unless it's an exit, it will return 1
		if (!k) //if it doesn't exist that means it was an exit and doesn't move
			return (0);
		game->map[j + 1][i] = '0'; //if it was valid, changes the space where the player previously was (P) for a floor (0)
	}
	else if (movement == 115) //keycode for goind down (S)
	{
		j++; //updates pos by 1 down the screen
		if (game->map[j][i] == '1')
			return (0);
		k = right_move(game, i, j);
		if (!k)
			return (0);
		game->map[j - 1][i] = '0';
	}
	ft_printf("👟 Steps: %i\n", game->counter); 
	ft_printf("💛 Coins Left: %i\n", game->coincount);
	return (1);
}

static int	keyboard_a_d(t_complete *game, int movement) //if you move left or right (x axis)
{
	int	i;
	int	j;
	int	k;

	i = game->x_axis;
	j = game->y_axis;
	if (movement == 97) //has pulsado a (izquierda)
	{
		i--;
		if (game->map[j][i] == '1')
			return (0);
		k = right_move(game, i, j);
		if (!k)
			return (0);
		game->map[j][i + 1] = '0';
	}
	else if (movement == 100) //has pulsado d (derecha)
	{
		i++;
		if (game->map[j][i] == '1')
			return (0);
		k = right_move(game, i, j);
		if (!k)
			return (0);
		game->map[j][i - 1] = '0';
	}
	ft_printf("👟 Steps: %i\n", game->counter);
	ft_printf("💛 Coins Left: %i\n", game->coincount);
	return (1);
}

int	controls_working(int command, t_complete *game)
{
	int	works;
	
	if (command == 65307) //si pulsas escape
		exit_point(game);
	if (command == 119) //si pulsas w 
		works = keyboard_w_s(game, command);
	if (command == 115) //si pulsas s
		works = keyboard_w_s(game, command);
	if (command == 97) //si pulsas a (izq)
		works = keyboard_a_d(game, command);
	if (command == 100) //si pulsas d (derecha)
		works = keyboard_a_d(game, command);
	if (works) //unless you pressed escape 65307, this will work
		adding_in_graphics(game); //i guess it adds a new layer of graphics
	return (1);
}
