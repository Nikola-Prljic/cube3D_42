
#include "../cub3d.h"

int	open_textures(t_data *data, t_xpm_img *xpm_img, char *path)
{
	xpm_img->img = mlx_xpm_file_to_image(data->mlx_ptr, path, &xpm_img->width,
		&xpm_img->height);
	if (!xpm_img->img)
		return (1);
	return (0);
}

void	loadtextures(t_data *data, t_xpm_img *xpm_img, char **path)
{
	if (open_textures(data, xpm_img, *path))
	{
		if (data->rays)
			free(data->rays);
		free_set_null(path);
		free_data_exit(data, "Error\nLoad texture failed\n");
	}
	free_set_null(path);
	return ;
}

void	load_all_textures(t_data *data)
{
	loadtextures(data, data->north, &data->texture->north);
	loadtextures(data, data->south, &data->texture->south);
	loadtextures(data, data->west, &data->texture->west);
	loadtextures(data, data->east, &data->texture->east);
	return ;
}
