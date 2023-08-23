
#include "../cub3d.h"

void	init_xpm_imgs(t_data *data, t_xpm_img *xpm_imgs)
{
	data->north = &xpm_imgs[0];
	data->south = &xpm_imgs[1];
	data->west = &xpm_imgs[2];
	data->east = &xpm_imgs[3];
	data->north->img = NULL;
	data->south->img = NULL;
	data->west->img = NULL;
	data->east->img = NULL;
}

void	init_data(t_data *data)
{
	data->px = -1;
	data->py = -1;
	data->map_y = -1;
	data->map_x = -1;
	data->map = NULL;
	data->map_copy = NULL;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->rays = NULL;
	data->texture->north = NULL;
	data->texture->south = NULL;
	data->texture->west = NULL;
	data->texture->east = NULL;
}

void	free_imgs(t_data *data)
{
	if (!data->mlx_ptr)
		return ;
	if (data->north->img)
		mlx_destroy_image(data->mlx_ptr, data->north->img);
	if (data->west->img)
		mlx_destroy_image(data->mlx_ptr, data->east->img);
	if (data->east->img)
		mlx_destroy_image(data->mlx_ptr, data->west->img);
	if (data->south->img)
		mlx_destroy_image(data->mlx_ptr, data->south->img);
}

int	free_data(t_data *data)
{
	if (data->map)
	{
		free2d(data->map);
		data->map = NULL;
	}
	if (data->map_copy)
	{
		free2d(data->map_copy);
		data->map_copy = NULL;
	}
	free_set_null(&data->texture->north);
	free_set_null(&data->texture->south);
	free_set_null(&data->texture->west);
	free_set_null(&data->texture->east);
	free_imgs(data);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		data->mlx_ptr = NULL;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_data		data;
	t_texture	texture;
	t_xpm_img	xpm_imgs[4];

	fd = -1;
	data.texture = &texture;
	init_data(&data);
	init_xpm_imgs(&data, xpm_imgs);
	if (input_handle(argc, argv, &fd))
		return (1);
	if (map_check(&data, fd) || window_loop(&data))
		return (free_data(&data));
	free_data(&data);
	return (0);
}
