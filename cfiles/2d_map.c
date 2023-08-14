
#include "../cub3d.h"

void	prepare_player(t_data *data)
{
	int	size;

	data->rays->player = mlx_xpm_file_to_image(data->mlx_ptr,
			"./2d_imgs/player.xpm", &size, &size);
	data->rays->wall = mlx_xpm_file_to_image(data->mlx_ptr,
			"./2d_imgs/wall.xpm", &size, &size);
	data->rays->space = mlx_xpm_file_to_image(data->mlx_ptr,
			"./2d_imgs/space.xpm", &size, &size);

}

void	print_2d(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == '0' || data->map[y][x] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->rays->space, (x * 43), (y * 43));
			else if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->rays->wall, (x * 43), (y * 43));
		}
	}
}
