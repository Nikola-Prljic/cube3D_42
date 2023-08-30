/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <rkurnava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:15:19 by rkurnava          #+#    #+#             */
/*   Updated: 2023/08/30 17:47:44 by rkurnava         ###   ########.fr       */
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
		if (data->rays->up_down == -1)
			draw_walls(data, hl, data->rays->h_x, data->north);
		else
			draw_walls(data, hl, data->rays->h_x, data->south);
	}
	else
	{
		if (data->rays->left_right == -1)
			draw_walls(data, vl, data->rays->v_y, data->east);
		else
			draw_walls(data, vl, data->rays->v_y, data->west);
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
