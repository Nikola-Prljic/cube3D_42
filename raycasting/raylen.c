/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raylen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:24:19 by rkurnava          #+#    #+#             */
/*   Updated: 2023/08/15 20:10:20 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	raylen_h(t_data *data, float alpha)
{
	int	old_y_x[2];
	int	new_y_x[2];
	int	y;
	int	x;

	x = 64 / tanf(alpha);
	y = 64;
	if (alpha < PI && alpha > 0)
	{
		new_y_x[0] = (data->rays->pcor_y / 64) * (64) - 1;
		y = -64;
	}
	else if (alpha >= PI && alpha < 2 * PI)
		new_y_x[0] = (data->rays->pcor_y / 64) * (64) + 64;
	new_y_x[1] = data->rays->pcor_x + ((data->rays->pcor_y - new_y_x[0]) /
			-tanf(alpha));
	data->rays->f_h_y = new_y_x[0];
	data->rays->f_h_x = new_y_x[1];
	if (new_y_x[0] > 64 * 8 || new_y_x[0] < 64 || new_y_x[1] > 64 * 8
		|| new_y_x[1] < 64)
		return ;
	while (1)
	{
		old_y_x[0] = new_y_x[0];
		old_y_x[1] = new_y_x[1];
		new_y_x[0] = old_y_x[0] + y;
		new_y_x[1] = old_y_x[1] + x;
		if (new_y_x[0] > 64 * 8 || new_y_x[0] < 64 || new_y_x[1] > 64 * 8
			|| new_y_x[1] < 64)
			return ;
		if (data->map[(new_y_x[0] / 64)][(new_y_x[1] / 64)] != '1')
			break ;
	}
	data->rays->h_y = new_y_x[0];
	data->rays->h_x = new_y_x[1];
}

void	raylen_v(t_data *data, float alpha)
{
	int	old_y_x[2];
	int	new_y_x[2];
	int	y;
	int	x;

	x = 64;
	y = 64 * -tanf(alpha);
	new_y_x[0] = data->rays->pcor_y;
	if (alpha > (PI / 2) && alpha < 3 * PI / 2)
	{
		new_y_x[1] = (data->rays->pcor_x / 64) * (64) + 64;
		y = y * -1;
	}
	else
		new_y_x[1] = (data->rays->pcor_x / 64) * (64) - 1;
	while (1)
	{
		old_y_x[0] = new_y_x[0];
		old_y_x[1] = new_y_x[1];
		new_y_x[0] = old_y_x[0] + y;
		new_y_x[1] = old_y_x[1] + x;
		if (new_y_x[0] > 64 * 8 || new_y_x[0] < 64 || new_y_x[1] > 64 * 8
			|| new_y_x[1] < 64)
			return ;
		if (data->map[new_y_x[0] / 64][new_y_x[1] / 64] != '1')
			break ;
	}
	data->rays->v_y = new_y_x[0];
	data->rays->v_x = new_y_x[1];
}

void	raylen(t_data *data)
{
	float	ray_angle;
	double	pd_h;
	double	pd_v;

	pd_h = 0;
	pd_v = 0;
	ray_angle = data->rays->player_dir;
	raylen_h(data, ray_angle);
	raylen_v(data, ray_angle);
	pd_h = fabs(data->rays->pcor_x - data->rays->h_x / cos(ray_angle));
	pd_v = fabs(data->rays->pcor_x - data->rays->v_x / cos(ray_angle));
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->rays->space,
			data->rays->h_x, data->rays->h_y);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->rays->space,
			data->rays->v_x, data->rays->v_y);
}
