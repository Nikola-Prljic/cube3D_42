
#include "../cub3d.h"

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
	if(data->texture->north)
	{
		free(data->texture->north);
		data->texture->north = NULL;
	}
	if(data->texture->south)
		free(data->texture->south);
	if(data->texture->west)
		free(data->texture->west);
	if(data->texture->east)
		free(data->texture->east);
	return (1);
}

int	main(int argc, char **argv)
{
	int fd;
	t_data	data;
	t_texture texture;

	fd = -1;
	data.texture = &texture;
	init_data(&data);
	if (input_handle(argc, argv, &fd))
		return (1);
	if (map_check(&data, fd) || window_loop(&data))
		return (free_data(&data));
	free_data(&data);
	return (0);
}
