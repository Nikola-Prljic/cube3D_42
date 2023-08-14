
#include "../cub3d.h"

void	raylen(t_data *data, float rd, int *re)
{
	int		rx;
	int		ry;
	int		dof;
	int		mx;
	int		my;
	double	itan;
	double	yoff;
	double	xoff;

	(void)rd;
	(void)re;
	itan = tan(data->rays->player_dir);
	dof = 0;
	if (data->rays->player_dir > 0.001)
	{
		rx = (((int)data->rays->player_x >> 6) << 6) + 64;
		ry = (data->rays->player_x - rx) * itan + data->rays->player_y;
		xoff = 64;
		yoff = -xoff * itan;
	}
	else if (data->rays->player_dir < -0.001)
	{
		ry = (((int)data->rays->player_y >> 6) << 6) - 0.0001;
		rx = (data->rays->player_y - ry) * itan + data->rays->player_x;
		yoff = -64;
		xoff = (yoff * -1) * itan;
	}
	else
	{
		rx = data->rays->player_x;
		ry = data->rays->player_y;
		dof = 8;
	}
	while (dof < 8)
	{
		mx = (int)rx >> 6;
		my = (int)ry >> 6;
		if (mx >= 0 && my >= 0 && data->map[mx][my] == '1')
			dof = 8;
		else
		{
			rx += xoff;
			ry += yoff;
			dof += 1;
		}
	}
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, rx, ry, 0x00FF0000);
}
