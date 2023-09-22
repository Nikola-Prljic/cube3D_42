/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:15:19 by rkurnava          #+#    #+#             */
/*   Updated: 2023/09/22 17:09:25 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		data->rays->off = data->rays->h_x;
		if (data->rays->up_down == -1)
			draw_walls(data, hl, data->north, 'N');
		else
			draw_walls(data, hl, data->south, 'S');
		return ;
	}
	data->rays->off = data->rays->v_y;
	if (data->rays->left_right == -1)
		draw_walls(data, vl, data->west, 'W');
	else
		draw_walls(data, vl, data->east, 'E');
}

void	save_cor_ver(double *ay, double *ax, t_data *data)
{
	if (data->rays->left_right == -1)
		*ax += 1;
	data->rays->v_x = *ax;
	data->rays->v_y = *ay;
}

void	save_cor_hor(double *ay, double *ax, t_data *data)
{
	if (data->rays->up_down == -1)
		*ay += 1;
	data->rays->h_x = *ax;
	data->rays->h_y = *ay;
}
