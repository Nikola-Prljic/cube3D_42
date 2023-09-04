
#include "../cub3d.h"

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

void	left_right(t_data *data, float move, int keysum)
{
	if (keysum == XK_a || keysum == XK_Left)
	{
		data->rays->player_dir -= 0.0523599;
		if (data->rays->player_dir < 0)
			data->rays->player_dir += 6.283186;
		data->rays->player_dir_x = cos(data->rays->player_dir) * move;
		data->rays->player_dir_y = sin(data->rays->player_dir) * move;
	}
	else if (keysum == XK_d || keysum == XK_Right)
	{
		data->rays->player_dir += 0.0523599;
		if (data->rays->player_dir > 6.283186)
			data->rays->player_dir -= 6.283186;
		data->rays->player_dir_x = cos(data->rays->player_dir) * move;
		data->rays->player_dir_y = sin(data->rays->player_dir) * move;
	}
}

void	up_down(t_data *data, int keysum)
{
	if (keysum == XK_w || keysum == XK_Up)
	{
		if (collision(data, '+') == 1)
			return ;
		data->rays->px += data->rays->player_dir_x;
		data->rays->py += data->rays->player_dir_y;
	}
	else if (keysum == XK_s || keysum == XK_Down)
	{
		if (collision(data, '-') == 1)
			return ;
		data->rays->px -= data->rays->player_dir_x;
		data->rays->py -= data->rays->player_dir_y;
	}
}

int	keypress(int keysum, t_data *data)
{
	float	move;

	move = TILE_SIZE / 5;
	if (keysum == XK_Escape)
		return (x_close(data));
	else if (keysum == XK_a || keysum == XK_Left)
		left_right(data, move, keysum);
	else if (keysum == XK_d || keysum == XK_Right)
		left_right(data, move, keysum);
	else if (keysum == XK_w || keysum == XK_Up)
		up_down(data, keysum);
	else if (keysum == XK_s || keysum == XK_Down)
		up_down(data, keysum);
	renderCub(data);
	return (1);
}