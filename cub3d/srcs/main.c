#include "cub3d.h"

/* ./cub3d | grep -e "\!\! " -e "ray_id_0," -e "ray_id_1," -e "ray_id_2," -e "ray_id_3," -e "ray_id_398," -e "ray_id_399," -e "ray_id_400," -e "ray_id_401," -e "ray_id_402," -e "ray_id_600," -e "ray_id_799," -e "ray_id_200" -e "ray_id_397," -e "ray_id_403,"
*/

int render()
{
	player_moves();
	return (0);
}

t_game	*ft_game()
{
	static t_game	game_s;

	return (&game_s);
}

int main(int argc, char **argv)
{


	(void)argv;
	if (argc == 1)
	{
		// printf("argc 1\n");
		ft_game()->update = 1;
	}
	else if (argc == 2)
		ft_game()->update = 0;
	// if (argc != 2)
	else
	{
		// TODO PRINT_ERROR?
		printf("Please run ./cub3d <.cub_file_path> \n");
		return (EXIT_FAILURE);
	}


	init_game(argv[1]); //TODO merge this
	raycasting();
	render();
	// free_game();
	// draw_minimap(0, 0);
	// mlx_put_image_to_window(ft_game()->mlx->mlx, ft_game()->mlx->win, ft_game()->mlx->img.img, 0, 0);
	// TODO make an function for this :
	mlx_put_image_to_window(ft_game()->mlx->mlx, ft_game()->mlx->win, ft_game()->mlx->img.img, 0, 0);
    // Triggered when a key is pressed.
    mlx_hook(ft_game()->mlx->win, 2, 1L<<0, key_press, NULL);
    // Triggered when a key is released.
    mlx_hook(ft_game()->mlx->win, 3, 1L<<1, key_release, NULL);
    // Triggered when the mouse is moved.
    mlx_hook(ft_game()->mlx->win, 6, 1L<<6, mouse_moved, NULL);
    // Triggered when a mouse button is pressed. //TODO find if i need to use this
    mlx_hook(ft_game()->mlx->win, 4, 1L<<2, handle_mouse, NULL);
    // Triggered when a mouse button is released.
    mlx_hook(ft_game()->mlx->win, 5, 1L<<3, handle_mouse, NULL);
    // Triggered cross exit is pressed
	mlx_hook(ft_game()->mlx->win, 17, 0, handle_close, NULL);
	// Set the loop to call the player_moves function
	mlx_loop_hook(ft_game()->mlx->mlx, render, NULL);
	mlx_loop(ft_game()->mlx->mlx);
	// mlx_loop_hook(ft_game()->mlx, player_moves, NULL);
	// Start the loop to listen for events
	return (0);
}
