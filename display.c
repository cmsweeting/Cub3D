//HEADER

#include "raycasting.h"

int	close_win(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

int	escape(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_win(data);
	return (0);
}

void	get_first_ray_angle(t_data *data)
{
	int	P_angle;

	if (data->map[data->Py][data->Px] == 'N')
		P_angle = 0;
	// else if (data->map[data->Py][data->Px] == 'E')
	// 	P_angle = 90;
	// else if (data->map[data->Py][data->Px] == 'S')
	// 	P_angle = 180;
	// else if (data->map[data->Py][data->Px] == 'W')
	// 	P_angle = 270;
	data->angle = P_angle - (FOV / 2);
}


int	init_display(char **map)
{
	t_data	data;

	data.map = map;
	data.Px = 3;
	data.Py = 2;
	get_first_ray_angle(&data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	 	return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!data.win_ptr)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}
	mlx_loop_hook(data.mlx_ptr, &raycasting, &data);
	mlx_hook(data.win_ptr, 17, 0, &close_win, &data);
	mlx_hook(data.win_ptr, 3, 1L<<1, &escape, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	data.win_ptr = NULL;
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}