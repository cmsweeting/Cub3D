//HEADER

#include "raycasting.h"

int	handle_R(void)
{
	return (0);
}

int	stop_loop(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

int	escape(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		stop_loop(data);
	return (0);
}

int	init_display()
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	 	return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1050, 550, "Cub3D");
	if (!data.win_ptr)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}
	mlx_loop_hook(data.mlx_ptr, &handle_R, NULL);
	mlx_hook(data.win_ptr, 17, 0, &stop_loop, &data);
	mlx_hook(data.win_ptr, 3, 1L<<1, &escape, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	data.win_ptr = NULL;
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}