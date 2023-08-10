/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:56:00 by rkurnava          #+#    #+#             */
/*   Updated: 2023/08/10 17:17:17 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef struct s_ray_cast
{
	char	view_point;
	int		view_dir;
	int		view_left;
	int		view_right;
	int		player_x;
	int		player_y;
	int		player_exists;
}			t_ray_cast;

void	free_raycasting(char **map, t_ray_cast *rays)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(&map);
	free(rays);
}

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
		rays->view_left = 120;
		rays->view_right = 60;
		rays->view_dir = 90;
	}
	if (rays->view_point == 'S')
	{
		rays->view_left = 300;
		rays->view_right = 240;
		rays->view_dir = 270;
	}
	if (rays->view_point == 'W')
	{
		rays->view_left = 210;
		rays->view_right = 150;
		rays->view_dir = 180;
	}
	if (rays->view_point == 'E')
	{
		rays->view_left = 30;
		rays->view_right = 330;
		rays->view_dir = 0;
	}
}

void	rays_init(t_ray_cast *rays)
{
	rays->player_x = 0;
	rays->player_y = 0;
	rays->player_exists = 0;
	rays->view_point = 'N';
	rays->view_left = 120;
	rays->view_right = 60;
}

int	raycasting(char **map, t_ray_cast *rays)
{
	rays_init(rays);
	get_position(map, rays);
	if (rays->player_exists == 0)
	{
		free_raycasting(map, rays);
		return (0);
	}
	angle_view_start(rays);
}

int	main(void)
{
	int			i;
	char		**map;
	t_ray_cast	*rays;

	i = -1;
	rays = malloc(sizeof(t_ray_cast));
	if (!rays)
		return (0);
	map = malloc(8 * sizeof(char *));
	if (!map)
	{
		free(rays);
		return (0);
	}
	while (++i < 8)
	{
		map[i] = malloc(9);
		if (!map[i])
		{
			while (--i > -1)
				free(map[i]);
			free(rays);
			return (0);
		}
	}
	map[0] = "1, 1, 1, 1, 1, 1, 1, 1";
	map[1] = "1, 0, 0, 0, 0, 0, 0, 1";
	map[2] = "1, 0, 0, 0, 0, S, 0, 1";
	map[3] = "1, 0, 0, 0, 0, 0, 0, 1";
	map[4] = "1, 0, 1, 1, 0, 0, 0, 1";
	map[5] = "1, 0, 1, 1, 0, 0, 0, 1";
	map[6] = "1, 0, 1, 0, 0, 0, 0, 1";
	map[7] = "1, 1, 1, 1, 1, 1, 1, 1";
	return (raycasting(rays, map));
}
