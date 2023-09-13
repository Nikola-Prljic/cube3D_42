/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_action_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:03:29 by rkurnava          #+#    #+#             */
/*   Updated: 2023/09/13 14:15:05 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	angle_left_right(t_data *data, int keysum, double move)
{
	if (keysum == XK_Left)
	{
		data->rays->player_dir -= 0.0523599;
		if (data->rays->player_dir < 0)
			data->rays->player_dir += 6.283186;
		data->rays->player_dir_x = cosf(data->rays->player_dir) * move;
		data->rays->player_dir_y = sinf(data->rays->player_dir) * move;
	}
	else if (keysum == XK_Right)
	{
		data->rays->player_dir += 0.0523599;
		if (data->rays->player_dir > 6.283186)
			data->rays->player_dir -= 6.283186;
		data->rays->player_dir_x = cosf(data->rays->player_dir) * move;
		data->rays->player_dir_y = sinf(data->rays->player_dir) * move;
	}
}

int	left_right(t_data *data, double change, double move)
{
	double	x;
	double	y;

	data->rays->player_dir += change;
	x = cosf(data->rays->player_dir) * move;
	y = sinf(data->rays->player_dir) * move;
	if (collision(data) == 1)
	{
		data->rays->player_dir += -change;
		return (1);
	}
	data->rays->player_dir += -change;
	data->rays->px += x;
	data->rays->py += y;
	return (0);
}

int	up(t_data *data, double move)
{
	double	x;
	double	y;

	x = cosf(data->rays->player_dir) * move;
	y = sinf(data->rays->player_dir) * move;
	if (collision(data) == 1)
		return (1);
	data->rays->px += x;
	data->rays->py += y;
	return (0);
}

int	down(t_data *data, double move)
{
	double	x;
	double	y;
	double	dir;

	if (data->rays->up_down == -1)
		dir = 3.14159;
	else
		dir = -3.14159;
	data->rays->player_dir += dir;
	x = cosf(data->rays->player_dir) * move;
	y = sinf(data->rays->player_dir) * move;
	if (collision(data) == 1)
	{
		data->rays->player_dir += -dir;
		return (1);
	}
	data->rays->player_dir += -dir;
	data->rays->px += x;
	data->rays->py += y;
	return (0);
}

int	keypress(int keysum, t_data *data)
{
	int		res;
	double	move;

	res = 0;
	move = TILE_SIZE / 5;
	if (keysum == XK_Escape)
		return (x_close(data));
	else if (keysum == XK_Left)
		angle_left_right(data, keysum, move);
	else if (keysum == XK_Right)
		angle_left_right(data, keysum, move);
	else if (keysum == XK_w || keysum == XK_W)
		res = up(data, move);
	else if (keysum == XK_s || keysum == XK_S)
		res = down(data, move);
	else if (keysum == XK_d || keysum == XK_D)
		res = left_right(data, 1.57079, move);
	else if (keysum == XK_a || keysum == XK_A)
		res = left_right(data, -1.57079, move);
	if (res == 1)
		return (1);
	rendercub(data);
	return (1);
}
