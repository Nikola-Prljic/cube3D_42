/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:56:00 by rkurnava          #+#    #+#             */
/*   Updated: 2023/08/23 17:32:33 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
				rays->px = x * 64 - 32;
				rays->py = y * 64 - 32;
				rays->player_exists = 1;
				rays->view_point = map[y][x];
				map[y][x] = 'P';
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
	rays->plane = WINDOW_WITH;
}

void	rays_init(t_ray_cast *rays)
{
	rays->h_x = 0;
	rays->h_y = 0;
	rays->v_x = 0;
	rays->v_y = 0;
	rays->up_down = 0;
	rays->left_right = 0;
	rays->px = 0;
	rays->py = 0;
	rays->plane = WINDOW_WITH;
	rays->player_exists = 0;
	rays->view_point = 'N';
	rays->player_dir_x = 0;
	rays->player_dir_y = 0;
	rays->player_dir = 0;
}

int	raycasting(char **map, t_ray_cast *rays)
{
	rays_init(rays);
	get_position(map, rays);
	angle_view_start(rays);
	rays->player_dir_x = cos(rays->player_dir) * 5;
	rays->player_dir_y = sin(rays->player_dir) * 5;
	if (rays->player_exists == 0)
		return (0);
	return (0);
}

int	ray_functions(t_data *data)
{
	t_ray_cast	*my_rays;

	if (!data->rays)
	{
		data->rays = malloc(sizeof(t_ray_cast));
		if (!data->rays)
			return (1);
	}
	my_rays = data->rays;
	raycasting(data->map, my_rays);
	return (0);
}
