/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raylen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:24:19 by rkurnava          #+#    #+#             */
/*   Updated: 2023/08/24 10:20:31 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	where_we_look(t_data *data, int reseting, float angle)
{
	if (reseting)
	{
		data->rays->left_right = 0;
		data->rays->up_down = 0;
		return ;
	}
	if ((int)rad2deg(angle) > 0 && (int)rad2deg(angle) < 180)
	{
		printf("down\n");
		data->rays->up_down = 1;
	}
	else if ((int)rad2deg(angle) > 180 && (int)rad2deg(angle) < 359)
	{
		printf("up\n");
		data->rays->up_down = -1;
	}
	else
		data->rays->up_down = 0;
	if ((int)rad2deg(angle) < 270 && (int)rad2deg(angle) > 90)
	{
		printf("left\n");
		data->rays->left_right = -1;
	}
	else if ((int)rad2deg(angle) > 270 || (int)rad2deg(angle) < 90)
	{
		printf("right\n");
		data->rays->left_right = 1;
	}
	else
		data->rays->left_right = 0;
}

void	raylen_v(t_data *data, float angle, char **map)
{
	int	ax;
	int	ay;
	int	y_step;
	int	x_step;

	ax = ((int)(data->rays->px / TILE_SIZE)) * TILE_SIZE + 64;
	if (data->rays->left_right == -1)
		ax = ((int)(data->rays->py / TILE_SIZE)) * TILE_SIZE - 1;
	ay = data->rays->py + ((ax - data->rays->px) * tan(angle));
	x_step = TILE_SIZE;
	if (data->rays->left_right == -1)
		x_step *= -1;
	y_step = TILE_SIZE * tan(angle);
	if (data->rays->up_down == -1 && y_step > 0)
		y_step *= -1;
	if (data->rays->up_down == 1 && y_step < 0)
		y_step *= -1;
	while (ay >= 0 && ay <= WINDOW_HEIGT && ax >= 0 && ax <= WINDOW_WITH
		&& map[ay / 64][ax / 64] != '1')
	{
		ax += x_step;
		ay += y_step;
	}
	data->rays->v_x = ax;
	data->rays->v_y = ay;
}

void	raylen_h(t_data *data, float angle, char **map)
{
	int	ax;
	int	ay;
	int	y_step;
	int	x_step;

	ay = ((int)(data->rays->py / TILE_SIZE)) * TILE_SIZE + 64;
	if (data->rays->up_down == -1)
		ay = ((int)(data->rays->py / TILE_SIZE)) * TILE_SIZE - 1;
	ax = data->rays->px + ((ay - data->rays->py) / tan(angle));
	y_step = TILE_SIZE;
	if (data->rays->up_down == -1)
		y_step *= -1;
	x_step = TILE_SIZE / tan(angle);
	if (data->rays->left_right == -1 && x_step > 0)
		x_step *= -1;
	if (data->rays->left_right == 1 && x_step < 0)
		x_step *= -1;
	while (ay >= 0 && ay <= WINDOW_HEIGT && ax >= 0 && ax <= WINDOW_WITH
		&& map[ay / 64][ax / 64] != '1')
	{
		ax += x_step;
		ay += y_step;
	}
	data->rays->h_x = ax;
	data->rays->h_y = ay;
}

void	raylen(t_data *data)
{
	int vl;
	int hl;
	int raycount;
	float ray_angle;

	raycount = 0;
	ray_angle = data->rays->player_dir - (PI / 6);
	while (raycount < WINDOW_HEIGT)
	{
		where_we_look(data, 0, ray_angle);
		raylen_h(data, ray_angle, data->map);
		raylen_v(data, ray_angle, data->map);
		vl = sqrt(pow(data->rays->px - data->rays->v_x, 2) + pow(data->rays->py
					- data->rays->v_y, 2));
		hl = sqrt(pow(data->rays->px - data->rays->h_x, 2) + pow(data->rays->py
					- data->rays->h_y, 2));
		if (hl < vl)
		{
			printf("horizontal\n");
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->rays->space, data->rays->h_x, data->rays->h_y);
		}
		else
		{
			printf("vertical\n");
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->rays->space, data->rays->v_x, data->rays->v_y);
		}
		raycount++;
		ray_angle += (float)deg2rad(60.0 / (float)WINDOW_WITH);
	}
}
