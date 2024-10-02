//HEADER

#include "raycasting.h"

void	ft_put_pixel(t_img *img, int colomn, int line, int color)
{
	*(int *)(img->addr + (line * img->length + colomn * (img->bpp / 8))) = color;
}
 
void	draw_column(t_data *data, int distance, int colomn)
{
	int	hp;
	int	i;
	int	hr;
	int	half_hp;

	i = 0;
	hr = CUB / 2;
	hp = CUB / distance * DISTANCE;
	half_hp = hp / 2;
	while (i < (hr - half_hp))
	{
		ft_put_pixel(&data->img, colomn, i, BLUE);
		i++;
	}
	while (i <= (hr + half_hp))
	{
		ft_put_pixel(&data->img, colomn, i, BROWN);
		i++;
	}
	while (i < SCREEN_HEIGHT)
	{
		ft_put_pixel(&data->img, colomn, i, GREEN);
		i++;
	}
}