
#include "../cub3d.h"

void	prepare_player(t_data *data)
{
	int	size;

	data->rays->player = mlx_xpm_file_to_image(data->mlx_ptr,
			"./2d_imgs/player.xpm", &size, &size);
	if (data->rays->player)
		write (2, "Player image for 2d not found!\n", 25);
}
