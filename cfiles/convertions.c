
#include "../cub3d.h"

float	deg2rad(double degrees)
{
	return (degrees * (PI / 180.0));
}

float	rad2deg(double radians)
{
	return (radians * (180.0 / PI));
}

int	x_close(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}
