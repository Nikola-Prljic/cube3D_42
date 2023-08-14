
#include "../cub3d.h"

void	raylen(t_data *data, float rd, int *re)
{
	int	rx;
	int	ry;

	(void)re;
	(void)rd;
	rx = data->rays->player_x - data->rays->player_dir_x * 5;
	ry = data->rays->player_y - data->rays->player_dir_y * 5; 
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, rx, ry, 0x00FF0000);
}
