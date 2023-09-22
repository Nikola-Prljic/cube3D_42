/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:56:00 by rkurnava          #+#    #+#             */
/*   Updated: 2023/09/22 17:09:24 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_position(char **map, t_ray_cast *rays)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				rays->view_point = map[y][x];
				return ;
			}
		}
	}
}

void	angle_view_start(t_ray_cast *rays)
{
	if (rays->view_point == 'N')
		rays->player_dir = deg2rad(270.0);
	if (rays->view_point == 'S')
		rays->player_dir = deg2rad(90.0);
	if (rays->view_point == 'W')
		rays->player_dir = deg2rad(180.0);
	if (rays->view_point == 'E')
		rays->player_dir = deg2rad(0.0);
}

void	rays_init(t_data *data)
{
	data->rays->fov = deg2rad(60);
	data->rays->plane = ((WINDOW_WITH / 2) / tan(data->rays->fov / 2));
	data->rays->off = 0;
	data->rays->hl = 10000;
	data->rays->vl = 10000;
	data->rays->h_x = 0;
	data->rays->h_y = 0;
	data->rays->v_x = 0;
	data->rays->v_y = 0;
	data->rays->up_down = 0;
	data->rays->left_right = 0;
	data->rays->px = (data->px + 1) * TILE_SIZE - (TILE_SIZE / 2);
	data->rays->px_init = data->rays->px;
	data->rays->py = (data->py + 1) * TILE_SIZE - (TILE_SIZE / 2);
	data->rays->py_init = data->rays->py;
	data->rays->view_point = 'N';
	data->rays->player_dir_x = 0;
	data->rays->player_dir_y = 0;
	data->rays->player_dir = 0;
}

int	raycasting(char **map, t_data *data)
{
	double	move;

	move = TILE_SIZE / 15;
	rays_init(data);
	get_position(map, data->rays);
	angle_view_start(data->rays);
	data->rays->player_dir_x = cos(data->rays->player_dir) * move;
	data->rays->player_dir_y = sin(data->rays->player_dir) * move;
	return (0);
}

int	ray_functions(t_data *data)
{
	if (!data->rays)
	{
		data->rays = malloc(sizeof(t_ray_cast));
		if (!data->rays)
			return (1);
	}
	raycasting(data->map, data);
	return (0);
}
