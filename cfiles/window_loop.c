
#include "../cub3d.h"

int	make_window(t_data *data, int heigt, int with)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, with, heigt, "cub3d");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		return (1);
	}
	return (0);
}

int	x_close(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}

int	keypress(int keysum, t_data *data)
{
	double	degrees;

	degrees = data->rays->player_dir * (180.0 / PI);
	printf("X & Y position of the player : %i	%i\n", data->rays->player_x,
		data->rays->player_y);
	printf("player view direction in degrees : %f\n", degrees);
	printf("---------------------------------------------------\n");
	if (keysum == XK_Escape)
		return (x_close(data));
	else if (keysum == XK_A || keysum == XK_Left)
	{
		data->rays->player_dir -= 0.1;
		if (data->rays->player_dir < 0)
			data->rays->player_dir += 2 * PI;
		data->rays->player_dir_x = cos(data->rays->player_dir) * 5;
		data->rays->player_dir_y = sin(data->rays->player_dir) * 5;
	}
	else if (keysum == XK_D || keysum == XK_Right)
	{
		data->rays->player_dir += 0.1;
		if (data->rays->player_dir > 2 * PI)
			data->rays->player_dir -= 2 * PI;
		data->rays->player_dir_x = cos(data->rays->player_dir) * 5;
		data->rays->player_dir_y = sin(data->rays->player_dir) * 5;
	}
	else if (keysum == XK_W || keysum == XK_Up)
	{
		data->rays->player_x -= data->rays->player_dir_x;
		data->rays->player_y -= data->rays->player_dir_y;
	}
	else if (keysum == XK_S || keysum == XK_Down)
	{
		data->rays->player_x += data->rays->player_dir_x;
		data->rays->player_y += data->rays->player_dir_y;
	}
	degrees = data->rays->player_dir * (180.0 / PI);
	printf("X & Y position of the player : %i	%i\n", data->rays->player_x,
		data->rays->player_y);
	printf("player view direction in degrees : %f\n", degrees);
	printf("\n\n");
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	print_2d(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->rays->player,
		data->rays->player_x - 21.5, data->rays->player_y - 21.5);
	raylen(data);
	return (1);
}

int	window_loop(t_data *data)
{
	ray_functions(data);
	if (make_window(data, WINDOW_HEIGT, WINDOW_WITH))
		return (1);
	prepare_player(data);
	print_2d(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->rays->player,
		data->rays->player_x - 21.5, data->rays->player_y - 21.5);
	mlx_hook(data->win_ptr, 17, 0, &x_close, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &keypress, data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_image(data->mlx_ptr, data->rays->player);
	if (data->rays)
		free(data->rays);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return (0);
}
