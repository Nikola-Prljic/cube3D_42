
#include "../cub3d.h"

void	raylen(t_data *data, float rd, int *re)
{
	int	rx;
	int	rx_2;
	int	ry;
	int	ry_2;

	(void)re;
	(void)rd;
	rx_2 = data->rays->player_x;
	ry_2 = data->rays->player_y;
	rx = rx_2 - data->rays->player_dir_x * 5;
	ry = ry_2 - data->rays->player_dir_y * 5;
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, rx, ry, 0x00FF0000);
}
