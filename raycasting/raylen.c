
#include "../cub3d.h"

void	raylen_h(t_data *data, int alpha)
{
	int	old_y_x[2];
	int	new_y_x[2];
	int	y;
	int	x;

	if (data->rays->player_dir < PI)
		new_y_x[0] = (data->rays->pcor_y / 64) * (64) - 1;
	else if (data->rays->player_dir > PI)
		new_y_x[0] = (data->rays->pcor_y / 64) * (64) + 64;
	new_y_x[1] = data->rays->pcor_x + (data->rays->pcor_y - new_y_x[0])
		/ tan(alpha);
	printf("Horizontal wall new_y && new_x : %i	%i\n", new_y_x[0] / 64,
				new_y_x[1] / 64);
	while (data->map[new_y_x[0] / 64][new_y_x[1] / 64] != '1')
	{
		old_y_x[0] = new_y_x[0];
		old_y_x[1] = new_y_x[1];
		if (data->rays->player_dir > PI)
			y = -64;
		else if (data->rays->player_dir < PI)
			y = 64;
		x = 64 / tan(alpha);
		new_y_x[0] = old_y_x[0] + y;
		new_y_x[1] = old_y_x[1] + x;
	}
	data->rays->h_y = new_y_x[0];
	data->rays->h_x = new_y_x[1];
}

void	raylen_v(t_data *data, int alpha)
{
	int	old_y_x[2];
	int	new_y_x[2];
	int	y;
	int	x;

	if (data->rays->player_dir < 90 && data->rays->player_dir > 270)
		new_y_x[1] = (data->rays->pcor_x / 64) * (64) + 64;
	else if (data->rays->player_dir > 90 && data->rays->player_dir < 270)
		new_y_x[1] = (data->rays->pcor_x / 64) * (64) - 1;
	new_y_x[0] = data->rays->pcor_y + ((data->rays->pcor_x - new_y_x[1])
			* tan(alpha));
	printf("Vertical wall new_y && new_x : %i	%i\n", new_y_x[0] / 64,
				new_y_x[1] / 64);
	while (data->map[new_y_x[0] / 64][new_y_x[1] / 64] != '1')
	{
		old_y_x[0] = new_y_x[0];
		old_y_x[1] = new_y_x[1];
		if (data->rays->player_dir > PI)
			y = -64;
		else if (data->rays->player_dir < PI)
			y = 64;
		x = 64 / tan(alpha);
		new_y_x[0] = old_y_x[0] + y;
		new_y_x[1] = old_y_x[1] + x;
	}
	data->rays->v_y = new_y_x[0];
	data->rays->v_x = new_y_x[1];
}

void	raylen(t_data *data)
{
	int		ray;
	double	pd_v;
	double	pd_h;

	ray = data->rays->player_dir;
	raylen_h(data, ray);
	raylen_v(data, ray);
	pd_h = sqrt(pow((data->rays->pcor_x - data->rays->h_x), 2)
			+ pow((data->rays->pcor_y - data->rays->h_y), 2));
	pd_v = sqrt(pow((data->rays->pcor_x - data->rays->v_x), 2)
			+ pow((data->rays->pcor_y - data->rays->v_y), 2));
	if (pd_h < pd_v)
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->rays->h_x,
				data->rays->h_y, 0xFF0000);
	else
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->rays->v_x,
				data->rays->v_y, 0xFF0000);
}
