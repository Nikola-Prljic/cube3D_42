/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raylen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:24:19 by rkurnava          #+#    #+#             */
/*   Updated: 2023/08/29 15:40:04 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	hit(t_data *data, char **map, int ay, int ax)
{

	if (ay < 0 /* || ay > WINDOW_HEIGT */ || ax < 0 /* || ax > WINDOW_WITH */)
		return (0);
	int map_y = ay / TILE_SIZE;
	int map_x = ax / TILE_SIZE;
	if(map_y >= data->map_y || map_x >= data->map_x)
		return (0);
	if (ay > 0 && ax > 0 && map[map_y][map_x] != '1')
		return (1);
	return (0);
}

void	where_we_look(t_data *data, int reseting, float angle)
{
	if (reseting)
	{
		data->rays->left_right = 0;
		data->rays->up_down = 0;
		return ;
	}
	if ((int)rad2deg(angle) >= 0 && (int)rad2deg(angle) < 180)
		data->rays->up_down = 1;
	else if ((int)rad2deg(angle) >= 180 && (int)rad2deg(angle) < 360)
		data->rays->up_down = -1;
	if ((int)rad2deg(angle) < 270 && (int)rad2deg(angle) >= 90)
		data->rays->left_right = -1;
	else if ((int)rad2deg(angle) >= 270 || (int)rad2deg(angle) < 90)
		data->rays->left_right = 1;
}

void	raylen_v(t_data *data, float angle, char **map)
{
	float	ax;
	float	ay;
	float	y_step;
	float	x_step;

	ax = (floor(data->rays->px / (float)TILE_SIZE)) * (float)TILE_SIZE;
	if (!(data->rays->left_right == -1))
		ax += (float)TILE_SIZE;
	ay = data->rays->py + (ax - data->rays->px) * tan(angle);
	x_step = (float)TILE_SIZE;
	if (data->rays->left_right == -1)
		x_step *= (float)-1;
	y_step = (float)TILE_SIZE * tan(angle);
	if (data->rays->up_down == -1 && y_step > 0)
		y_step *= (float)-1;
	if (data->rays->up_down == 1 && y_step < 0)
		y_step *= (float)-1;
	if (data->rays->left_right == -1)
		ax -= (float)1;
	while (hit(data, map, ay, ax))
	{
		ax += x_step;
		ay += y_step;
	}
	save_cor_ver(&ay, &ax, data);
}

void	raylen_h(t_data *data, float angle, char **map)
{
	float	ax;
	float	ay;
	float	y_step;
	float	x_step;

	ay = (floor(data->rays->py / (float)TILE_SIZE)) * (float)TILE_SIZE;
	if (!(data->rays->up_down == -1))
		ay += (float)TILE_SIZE;
	ax = data->rays->px + ((ay - data->rays->py) / tan(angle));
	y_step = (float)TILE_SIZE;
	if (data->rays->up_down == -1)
		y_step *= (float)-1;
	x_step = (float)TILE_SIZE / tan(angle);
	if (data->rays->left_right == -1 && x_step > 0)
		x_step *= (float)-1;
	if (data->rays->left_right == 1 && x_step < 0)
		x_step *= (float)-1;
	if (data->rays->up_down == -1)
		ay -= (float)1;
	while (hit(data, map, ay, ax))
	{
		ax += x_step;
		ay += y_step;
	}
	save_cor_hor(&ay, &ax, data);
}

void	raylen(t_data *data)
{
	data->raycount = 0;
	data->rays->ray_angle = data->rays->player_dir - (PI / 6);
	while (data->raycount < WINDOW_WITH)
	{
		if (data->rays->ray_angle > 2 * PI)
			data->rays->ray_angle -= deg2rad(360.0);
		if (data->rays->ray_angle < 0)
			data->rays->ray_angle += deg2rad(360.0);
		where_we_look(data, 0, data->rays->ray_angle);
		raylen_h(data, data->rays->ray_angle, data->map);
		raylen_v(data, data->rays->ray_angle, data->map);
		render(data);
		data->raycount++;
		data->rays->ray_angle += (float)deg2rad(60.0 / (float)WINDOW_WITH);
	}
}
