
#include "../cub3d.h"

int	make_window(t_data *data, int heigt, int with)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		if (data->rays)
			free(data->rays);
		data->rays = NULL;
		return (1);
	}
	load_all_textures(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, with, heigt, "cub3D");
	if (data->win_ptr == NULL)
	{
		if (data->rays)
			free(data->rays);
		data->rays = NULL;
		return (1);
	}
	return (0);
}

int	renderCub(t_data *data)
{
	if (!data->mlx_ptr || !data->win_ptr)
		return (0);
	draw_floor_sky(data, data->sky_rgb, data->floor_rgb);
	raylen(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img, 0, 0);
	return (1);
}

void	create_img_addr(t_data *data, t_img *img)
{
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	img->line_len /= 4;
	if (!img->addr)
	{
		if (data->rays)
			free(data->rays);
		free_data_exit(data, "Error\nMlx_get_data_addr failed\n");
	}
}

int	window_loop(t_data *data)
{
	ray_functions(data);
	if (make_window(data, WINDOW_HEIGT, WINDOW_WITH))
		return (1);
	data->img->img = mlx_new_image(data->mlx_ptr, WINDOW_WITH, WINDOW_HEIGT);
	create_img_addr(data, data->img);
	create_img_addr(data, data->north);
	create_img_addr(data, data->east);
	create_img_addr(data, data->west);
	create_img_addr(data, data->south);
	renderCub(data);
	mlx_hook(data->win_ptr, 17, 0, &x_close, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &keypress, data);
	mlx_loop(data->mlx_ptr);
	if (data->rays)
		free(data->rays);
	free_data(data);
	return (0);
}
