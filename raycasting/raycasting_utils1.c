/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:15:19 by rkurnava          #+#    #+#             */
/*   Updated: 2023/08/28 17:08:52 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render(t_data *data)
{
	double	vl;
	double	hl;

	vl = sqrt(pow(data->rays->v_x - data->rays->px, 2) + pow(data->rays->v_y
				- data->rays->py, 2));
	hl = sqrt(pow(data->rays->h_x - data->rays->px, 2) + pow(data->rays->h_y
				- data->rays->py, 2));
	if (hl < vl)
	{
		/* data->distance = hl;
		data->vertrical_hit = 1;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->rays->space,
			data->rays->h_x, data->rays->h_y); */
		draw_walls(data, hl);
	}
	else
	{
		/* data->distance = vl;
		data->vertrical_hit = 0;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->rays->spacev, data->rays->v_x, data->rays->v_y); */
		draw_walls(data, vl);
	}
}

void	save_cor_ver(float *ay, float *ax, t_data *data)
{
	if (data->rays->left_right == -1)
		*ax += 1;
	data->rays->v_x = *ax;
	data->rays->v_y = *ay;
}

void	save_cor_hor(float *ay, float *ax, t_data *data)
{
	if (data->rays->up_down == -1)
		*ay += 1;
	data->rays->h_x = *ax;
	data->rays->h_y = *ay;
}
