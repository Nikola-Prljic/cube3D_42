/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:56:00 by rkurnava          #+#    #+#             */
/*   Updated: 2023/08/10 19:31:16 by rkurnava         ###   ########.fr       */
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
				rays->player_x = x * 64 - 32;
				rays->player_x = y * 64 - 32;
				rays->player_exists = 1;
				rays->view_point = map[y][x];
				return ;
			}
		}
	}
}

void	angle_view_start(t_ray_cast *rays)
{
	if (rays->view_point == 'N')
	{
		rays->player_dir = PI / 2;
	}
	if (rays->view_point == 'S')
	{
		rays->player_dir = 3 * PI / 2;
	}
	if (rays->view_point == 'W')
	{
		rays->player_dir = PI;
	}
	if (rays->view_point == 'E')
	{
		rays->player_dir = 2 * PI;
	}
}

void	rays_init(t_ray_cast *rays)
{
	rays->player_x = 0;
	rays->player_y = 0;
	rays->player_exists = 0;
	rays->view_point = 'N';
	rays->player_dir_x = 0;
	rays->player_dir_y = 0;
	rays->player_dir = PI / 2;
}

int	raycasting(char **map, t_ray_cast *rays)
{
	rays_init(rays);
	get_position(map, rays);
	if (rays->player_exists == 0)
		return (0);
	angle_view_start(rays);
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
