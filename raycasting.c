//HEADER

#include "raycasting.h"

get_vertical_intersection(t_data *data)
{
	int	Xa;
	int	Ya;
	int	Bx;
	int	By;
	int	PB;

	Ya = 0;
	if (data->angle != 90)
		Ya = CUB * tan(data->angle);
	Xa = CUB;
	if (data->angle < 90)
	{
		Xa *= -1;
		Bx = (int)((data->Py * CUB) / CUB) * CUB - 1; //besoin de connaitre position joueur en pixel
	}
	else if (data->angle > 90)
		Bx = (int)((data->Py * CUB) / CUB) * CUB + 64;
	else
		Bx = data->Px * 64;
	By = (data->Px * 64) + (abs((data->Px * 64) - Bx) * tan(data->angle));
	while (data->map[By / CUB][Bx / CUB] != '1')
	{
		Bx += Xa;
		By += Ya;
	}
	PB = abs(data->Px * 64 - Bx) / cos(data->angle);
	return (PB);
}

int	get_horizontal_intersection(t_data *data)
{
	int	Xa;
	int	Ya;
	int	Ax;
	int	Ay;
	int	PA;

	Xa = 0;
	if (data->angle != 90)
		Xa = CUB / tan(data->angle);
	if (data->angle < 90)
		Xa *= -1;
	Ya = -CUB;
	Ay = (int)((data->Py * CUB) / CUB) * CUB - 1; //besoin de connaitre position joueur en pixel
	// else
	// {
	// 	Ya = CUB;
	// 	Ay = (int)((data->Py * CUB) / CUB) * CUB + 64;
	// }
	Ax = (data->Px * 64) + (((data->Py * 64) - Ay) / tan(data->angle));
	while (data->map[Ay / CUB][Ax / CUB] != '1')
	{
		Ax += Xa;
		Ay += Ya;
	}
	PA = abs(data->Px * 64 - Ax) / cos(data->angle);
	return (PA);
}

int	get_correct_distance(int horizontal, int vertical, t_data *data)
{
	int	distance;
	int	smallest;

	if (horizontal < vertical)
		smallest = horizontal;
	else
		smallest = vertical;
	if (data->angle < 90)
		distance = smallest * cos(30);
	else if (data->angle > 90)
		distance = smallest * cos(-30);
	return (distance);
}

int	raycasting(t_data *data)
{
	int	i;
	int	horizontal;
	int	vertical;
	int	distance;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		horizontal = get_horizontal_intersection(data);
		vertical = get_vertical_intersection(data);
		distance = get_correct_distance(horizontal, vertical, data);
		draw_column(distance);
		i++;
		data->angle += (i * ANGLE_BT_RAYS);
	}
	return (0);
}
