
#include "../cub3d.h"

int	collision(t_data *data, char c)
{
	float	ax;
	float	ay;
	float	bx;
	float	by;

	ay = data->rays->py;
	ax = data->rays->px;
	bx = data->rays->player_dir_x;
	by = data->rays->player_dir_y;
	if (c == '+')
	{
		if (data->rays->up_down == -1)
			by = (by + 10) * -1;
		if (data->rays->up_down == 1)
			by += 10;
		if (data->rays->left_right == -1)
			bx = (bx + 10) * -1;
		if (data->rays->left_right == 1)
			bx += 10;
	}
	if (c == '-')
	{
		if (data->rays->up_down == -1)
			by += 10;
		if (data->rays->up_down == 1)
			by = (by + 10) * -1;
		if (data->rays->left_right == -1)
			bx += 10;
		if (data->rays->left_right == 1)
			bx = (bx + 10) * -1;
	}
	if (data->map[(int)((ay + 10 + by) / TILE_SIZE)][(int)((ax + bx)
			/ TILE_SIZE)] == '1')
		return (1);
	else if (data->map[(int)((ay - 10 + by) / TILE_SIZE)][(int)((ax + bx)
			/ TILE_SIZE)] == '1')
		return (1);
	else if (data->map[(int)((ay + by) / TILE_SIZE)][(int)((ax + 10 + bx)
			/ TILE_SIZE)] == '1')
		return (1);
	else if (data->map[(int)((ay + by) / TILE_SIZE)][(int)((ax - 10 + bx)
			/ TILE_SIZE)] == '1')
		return (1);
	return (0);
}

int	make_window(t_data *data, int heigt, int with)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		if (data->rays)
			free(data->rays);
		data->rays = NULL;
		return (1);
	}
	load_all_textures(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, with, heigt, "cub3D");
	if (data->win_ptr == NULL)
	{
		if (data->rays)
			free(data->rays);
		data->rays = NULL;
		return (1);
	}
	return (0);
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

int	keypress(int keysum, t_data *data)
{
	double	degrees;

	if (keysum == XK_Escape)
		return (x_close(data));
	else if (keysum == XK_a || keysum == XK_Left)
	{
		data->rays->player_dir -= deg2rad(3.0);
		if (data->rays->player_dir < 0)
			data->rays->player_dir += 2 * PI;
		data->rays->player_dir_x = cos(data->rays->player_dir) * 5;
		data->rays->player_dir_y = sin(data->rays->player_dir) * 5;
	}
	else if (keysum == XK_d || keysum == XK_Right)
	{
		data->rays->player_dir += deg2rad(3.0);
		if (data->rays->player_dir > 2 * PI)
			data->rays->player_dir -= 2 * PI;
		data->rays->player_dir_x = cos(data->rays->player_dir) * 5;
		data->rays->player_dir_y = sin(data->rays->player_dir) * 5;
	}
	else if (keysum == XK_w || keysum == XK_Up)
	{
		if (collision(data, '+') == 1)
			return (1);
		data->rays->px += data->rays->player_dir_x;
		data->rays->py += data->rays->player_dir_y;
	}
	else if (keysum == XK_s || keysum == XK_Down)
	{
		if (collision(data, '-') == 1)
			return (1);
		data->rays->px -= data->rays->player_dir_x;
		data->rays->py -= data->rays->player_dir_y;
	}
	else if (keysum == XK_x && data->zoom_faktor < 5)
		data->zoom_faktor++;
	else if (keysum == XK_c && data->zoom_faktor > 1)
		data->zoom_faktor--;
	degrees = data->rays->player_dir * (180 / PI);
	/* print_2d(data); */
	/* mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->rays->player,
			data->rays->px - 21.5, data->rays->py - 21.5); */
	/* ft_rect(data, (t_rect){0, 0, WINDOW_HEIGT, WINDOW_WITH, 0x89CFF0});
	raylen(data); */
	// draw_texture(data);
	/* mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img,
			0,
		0); */
	/* mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->north->img,
			100,
		0); */
	return (1);
}

void	create_img_addr(t_data *data)
{
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WITH, WINDOW_HEIGT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (!data->img.addr)
	{
		if (data->rays)
			free(data->rays);
		free_data_exit(data, "Error\nmlx_get_data_addr faild\n");
	}
}

int	renderCub(t_data *data)
{
	if (!data->mlx_ptr || !data->win_ptr)
		return (0);
	ft_rect(data, (t_rect){0, 0, WINDOW_HEIGT, WINDOW_WITH, 0x89CFF0});
	raylen(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0,
			0);
	return (1);
}

int	window_loop(t_data *data)
{
	ray_functions(data);
	if (make_window(data, WINDOW_HEIGT, WINDOW_WITH))
		return (1);
	create_img_addr(data);
	/* ft_rect(data, (t_rect){200, 200, 50, 50, 0xFF0000}); */
	/* prepare_player(data); */
	/* print_2d(data); */
	/* mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->rays->player,
			data->rays->px - 21.5, data->rays->py - 21.5); */
	mlx_hook(data->win_ptr, 17, 0, &x_close, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &keypress, data);
	mlx_loop_hook(data->mlx_ptr, &renderCub, data);
	mlx_loop(data->mlx_ptr);
	/* mlx_destroy_image(data->mlx_ptr, data->rays->player);
	mlx_destroy_image(data->mlx_ptr, data->rays->wall);
	mlx_destroy_image(data->mlx_ptr, data->rays->space);
	mlx_destroy_image(data->mlx_ptr, data->rays->spacev); */
	if (data->rays)
		free(data->rays);
	// mlx_destroy_display(data->mlx_ptr);
	free_data(data);
	return (0);
}
