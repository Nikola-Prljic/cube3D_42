/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:03:33 by rkurnava          #+#    #+#             */
/*   Updated: 2023/09/12 19:29:00 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	help_collision(t_data *data)
{
	float	vl;
	float	hl;

	vl = sqrt(pow(data->rays->v_x - data->rays->px, 2) + pow(data->rays->v_y
				- data->rays->py, 2));
	hl = sqrt(pow(data->rays->h_x - data->rays->px, 2) + pow(data->rays->h_y
				- data->rays->py, 2));
	if (hl <= data->rays->hl)
		data->rays->hl = hl;
	if (vl <= data->rays->vl)
		data->rays->vl = vl;
}

void	wall_collision(t_data *data, double ray_angle)
{
	data->raycount = 0;
	if (data->rays->px < 0)
		data->rays->px = 1;
	if (data->rays->py < 0)
		data->rays->py = 1;
	ray_angle -= 0.523599;
	while (data->raycount < WINDOW_WITH)
	{
		if (ray_angle > 6.28319)
			ray_angle -= 6.28319;
		if (ray_angle < 0)
			ray_angle += 6.28319;
		where_we_look(data, 0, ray_angle);
		raylen_h(data, ray_angle, data->map);
		raylen_v(data, ray_angle, data->map);
		data->raycount++;
		ray_angle += (float)deg2rad(60.0 / (float)WINDOW_WITH);
		help_collision(data);
	}
}

int	collision(t_data *data)
{
	float	distance;
	float	ray_angle;

	distance = TILE_SIZE * 0.32;
	ray_angle = data->rays->player_dir;
	data->rays->hl = TILE_SIZE;
	data->rays->vl = TILE_SIZE;
	wall_collision(data, ray_angle);
	if (data->rays->hl < distance || data->rays->vl < distance)
		return (1);
	return (0);
}
