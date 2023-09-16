/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:03:36 by rkurnava          #+#    #+#             */
/*   Updated: 2023/09/16 14:07:25 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	img_pix_put(t_img *img, int put_x, int put_y, int color)
{
	img->addr[(img->line_len * put_y) + put_x] = color;
}

void	draw_texture_y_lopp(t_data *data, t_texture_draw draw, t_img *texture)
{
	int	i;
	int	y_off;
	int	y_top;
	int	color;

	i = 0;
	while (i < draw.top)
	{
		img_pix_put(data->img, data->raycount, i, data->sky_rgb);
		i++;
	}
	while (draw.top < draw.bottom)
	{
		y_top = draw.top + (draw.wall_strip / 2.0) - (WINDOW_HEIGT / 2);
		y_off = y_top * ((double)texture->height / draw.wall_strip);
		color = ((texture->height * y_off) + draw.ray_x);
		img_pix_put(data->img, data->raycount, draw.top, texture->addr[color]);
		draw.top++;
	}
	while (draw.top < WINDOW_HEIGT)
	{
		img_pix_put(data->img, data->raycount, draw.top, data->floor_rgb);
		draw.top++;
	}
}

void	draw_texure_on_walls(t_data *data, double wall_strip_height,
		t_img *texture, char dir)
{
	int	top;
	int	bottom;
	int	ray_x;
	int	rev_x;

	top = (WINDOW_HEIGT / 2) - (wall_strip_height / 2);
	if (top < 0)
		top = 0;
	bottom = (WINDOW_HEIGT / 2) + (wall_strip_height / 2);
	if (bottom > WINDOW_HEIGT)
		bottom = WINDOW_HEIGT;
	ray_x = ((double)texture->width / (double)TILE_SIZE) * ((int)data->rays->off
			% TILE_SIZE);
	rev_x = ((double)texture->width / (double)TILE_SIZE) * TILE_SIZE - ray_x
		- 1;
	if (dir == 'W' || dir == 'S')
		ray_x = rev_x;
	draw_texture_y_lopp(data, (t_texture_draw){top, ray_x, wall_strip_height,
		bottom}, texture);
}

void	draw_walls(t_data *data, double distance, t_img *texture, char dir)
{
	double	fixed_distance;
	double	wall_strip_height;

	fixed_distance = cos(data->rays->ray_angle - data->rays->player_dir)
		* distance;
	wall_strip_height = (TILE_SIZE / fixed_distance) * data->rays->plane;
	draw_texure_on_walls(data, wall_strip_height, texture, dir);
}
