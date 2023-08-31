#include "../cub3d.h"

void	img_pix_put(t_img *img, int put_x, int put_y, int color)
{
	img->addr[(put_y * img->line_len) + put_x] = color;
}

void	draw_floor_sky(t_data *data, int sky_color, int ground_color)
{
	int y;
	int x;

	y = 0;
	while (y < WINDOW_HEIGT >> 1)
	{
		x = 0;
		while (x < WINDOW_WITH)
		{
			img_pix_put(data->img, x, y, sky_color);
			x++;
		}
		y++;
	}
	while (y < WINDOW_HEIGT)
	{
		x = 0;
		while (x < WINDOW_WITH)
		{
			img_pix_put(data->img, x, y, ground_color);
			x++;
		}
		y++;
	}
}

//need to calculate the texture in total,
//but draw just the what you see with img_pix_put
//calculate the size of one pixel with line 94. For resizing the texture
void	draw_texure_on_walls(t_data *data, double wallStripHeight, int ray_x,
		t_img *texture)
{
	double	tmp;
	double	top;
	double	bottom;
	double	y_texture;
	int		y_ray_total;

	tmp = wallStripHeight;
	if (wallStripHeight > WINDOW_HEIGT)
		wallStripHeight = WINDOW_HEIGT;
	y_texture = 0;
	y_ray_total = 0;
	top = wallStripHeight + (tmp - wallStripHeight) / 2;
	bottom = (tmp - wallStripHeight) / 2;
	ray_x = ray_x - ray_x / TILE_SIZE * TILE_SIZE;
	y_ray_total = (int)bottom;
	y_texture = bottom / (tmp / TILE_SIZE);
	while (y_ray_total <= top)
	{
		img_pix_put(data->img, data->raycount, (double)WINDOW_HEIGT / 2.0 - tmp
			/ 2.0 + (double)y_ray_total, texture->addr[((int)y_texture
				* texture->line_len) + ray_x]);
		y_texture += 1.0 * TILE_SIZE / tmp;
		y_ray_total++;
	}
}

void	draw_walls(t_data *data, double distance, int ray_x, t_img *texture)
{
	double	correctWallDistance;
	double	distanceProjPlane;
	double	wallStripHeight;

	correctWallDistance = cos(data->rays->ray_angle - data->rays->player_dir)
		* distance;
	distanceProjPlane = ((double)WINDOW_HEIGT / 2.0) / 0.57735026919;
	wallStripHeight = ((double)TILE_SIZE / correctWallDistance)
		* distanceProjPlane;
	draw_texure_on_walls(data, wallStripHeight, ray_x, texture);
}

/* void	draw_minimap(t_data *data)
{
	int	y;
	int	x;
	int	mini_map_tidle;

	y = 0;
	mini_map_tidle = TILE_SIZE * MAP_SIZE;
	draw_floor_sky(data, (t_rect){(data->rays->py - 3) * MAP_SIZE, (data->rays->px - 3)
			* MAP_SIZE, 15 * MAP_SIZE, 15 * MAP_SIZE, 0xFF0000});
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				ft_rect(data, (t_rect){y * mini_map_tidle, x * mini_map_tidle,
						mini_map_tidle, mini_map_tidle, 0x555555});
			x++;
		}
		y++;
	}
} */
