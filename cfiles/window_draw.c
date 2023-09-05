#include "../cub3d.h"

void	img_pix_put(t_img *img, int put_x, int put_y, int color)
{
	img->addr[(put_y * img->line_len) + put_x] = color;
}

void	draw_floor_sky(t_data *data, int sky_color, int ground_color)
{
	int	y;
	int	x;

	y = 0;
	while (y < WINDOW_HEIGT >> 1)
	{
		x = -1;
		while (++x < WINDOW_WITH)
			img_pix_put(data->img, x, y, sky_color);
		y++;
	}
	while (y < WINDOW_HEIGT)
	{
		x = -1;
		while (++x < WINDOW_WITH)
			img_pix_put(data->img, x, y, ground_color);
		y++;
	}
}

void	draw_texture_y_lopp(t_data *data, t_texture_draw draw, t_img *texture)
{
	float	y_step;
	float	y_top;
	int		color;
	float	color_y;
	float	color_plus;

	y_top = ((float)WINDOW_HEIGT / 2.0) - (draw.total_wall / 2.0);
	y_step = (float)texture->height / draw.total_wall;
	color_plus = draw.top / draw.total_wall * texture->height;
	while (draw.top <= draw.bottom)
	{
		color_y = ((int)color_plus * texture->line_len) + (int)draw.ray_x;
		color = color_y;
		img_pix_put(data->img, data->raycount, y_top + draw.top,
			texture->addr[color]);
		color_plus += y_step;
		draw.top += 1.0;
	}
}

// need to calculate the texture in total,
// but draw just the what you see with img_pix_put
// calculate the size of one pixel with line 94. For resizing the texture
void	draw_texure_on_walls(t_data *data, float wall_strip_height, float ray_x,
		t_img *texture)
{
	float	total_wall;
	int		top;
	int		bottom;

	total_wall = wall_strip_height;
	if (wall_strip_height > WINDOW_HEIGT)
		wall_strip_height = (float)WINDOW_HEIGT;
	top = (total_wall - wall_strip_height) / 2.0;
	bottom = wall_strip_height + top;
	ray_x = ((float)TILE_SIZE / (float)texture->height) * ((int)ray_x
			% TILE_SIZE);
	draw_texture_y_lopp(data, (t_texture_draw){top, total_wall, ray_x,
		wall_strip_height, bottom}, texture);
}

void	draw_walls(t_data *data, float distance, float ray_x, t_img *texture)
{
	float	fixed_distance;
	float	proj_plane;
	float	wall_strip_height;

	fixed_distance = cosf(data->rays->ray_angle - data->rays->player_dir)
		* distance;
	proj_plane = ((float)WINDOW_WITH / 2.0) / 0.523599;
	wall_strip_height = ((float)TILE_SIZE / fixed_distance) * proj_plane;
	draw_texure_on_walls(data, wall_strip_height, ray_x, texture);
}
