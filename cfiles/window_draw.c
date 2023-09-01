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

void draw_texture_y_lopp(t_data *data, t_texture_draw draw, t_img *texture)
{
	while (draw.y_ray_total < draw.top_offset)
	{
		img_pix_put(data->img, data->raycount, (double)WINDOW_HEIGT / 2.0
			- draw.total_wall / 2.0 + (double)draw.y_ray_total,
			texture->addr[((int)draw.y_texture * texture->line_len) + (int)draw.ray_x]);
		draw.y_texture += draw.y_step;
		draw.y_ray_total++;
	}
}

// need to calculate the texture in total,
// but draw just the what you see with img_pix_put
// calculate the size of one pixel with line 94. For resizing the texture
void	draw_texure_on_walls(t_data *data, double wall_strip_height, double ray_x,
		t_img *texture)
{
	double	total_wall;
	double	y_texture;
	double  y_step;
	double	top_offset;
	double	bottom_offset;
	double	y_ray_total;

	total_wall = wall_strip_height;
	if (wall_strip_height > WINDOW_HEIGT)
		wall_strip_height = WINDOW_HEIGT;
	top_offset = wall_strip_height + (total_wall - wall_strip_height) / 2.0;
	bottom_offset = (total_wall - wall_strip_height) / 2.0;
	ray_x = ((double)texture->height / (double)TILE_SIZE) * ((int)ray_x % TILE_SIZE);
	y_ray_total = bottom_offset;
	y_texture = bottom_offset / total_wall * (double)texture->height;
	y_step = 1.0 * texture->height / total_wall;
	draw_texture_y_lopp(data, (t_texture_draw){y_ray_total, top_offset, total_wall, y_texture, y_step, ray_x}, texture);
}


void	draw_walls(t_data *data, double distance, int ray_x, t_img *texture)
{
	double	fixed_distance;
	double	proj_plane;
	double	wall_strip_height;

	fixed_distance = cos(data->rays->ray_angle - data->rays->player_dir)
		* distance;
	proj_plane = ((double)WINDOW_HEIGT / 2.0) / 0.57735026919;
	wall_strip_height = ((double)TILE_SIZE / fixed_distance)
		* proj_plane;
	draw_texure_on_walls(data, wall_strip_height, ray_x, texture);
}
