/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raylen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:24:19 by rkurnava          #+#    #+#             */
/*   Updated: 2023/08/23 15:13:47 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	raylen_h(t_data *data, float angle, char **map)
{
	int	ax;
	int	ay;
	int	y_step;
	int	x_step;

	y_step = TILE_SIZE;
	ay = ((int)(data->rays->pcor_y / TILE_SIZE)) * TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	if (rad2deg(angle) < 359 && rad2deg(angle) > 180)
	{
		ay = ((int)(data->rays->pcor_y / TILE_SIZE)) * TILE_SIZE - 1;
		y_step = (-1 * y_step);
		x_step = -(TILE_SIZE / tan(angle));
	}
	ax = data->rays->pcor_x + ((data->rays->pcor_y - ay) / tan(angle));
	while (map[ay / 64][ax / 64] != '1' && map[ay / 64][ax / 64])
	{
		ax += x_step;
		ay += y_step;
	}
	printf("ay & ax : %i & %i\n", ay, ax);
	data->rays->h_x = ax;
	data->rays->h_y = ay;
}
void	raylen(t_data *data)
{
	float	ray_angle;

	ray_angle = data->rays->player_dir;
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->rays->space,
	// 		data->rays->pcor_x + cos(ray_angle) * 30 - 5, data->rays->pcor_y
	// 		+ sin(ray_angle) * 30 - 5);
	raylen_h(data, ray_angle, data->map);
	printf("y & x for mlx : %i & %i\n", data->rays->h_y, data->rays->h_x);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->rays->space,
			data->rays->h_x, data->rays->h_y);
}
