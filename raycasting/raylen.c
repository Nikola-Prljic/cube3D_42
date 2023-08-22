/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raylen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:24:19 by rkurnava          #+#    #+#             */
/*   Updated: 2023/08/22 16:36:01 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	raylen_h(t_data *data, float alpha)
{
	int	old_y;
	int	old_x;

	old_x = data->rays->pcor_x + (-1 * (cos(alpha) * 30));
	old_y = data->rays->pcor_y + (-1 * (sin(alpha) * 30));
	data->rays->h_x = old_x;
	data->rays->h_y = old_y;
}

void	raylen(t_data *data)
{
	float	ray_angle;

	ray_angle = data->rays->player_dir;
	printf("player angle in radians : %f\n", ray_angle);
	raylen_h(data, ray_angle);
	printf("y and x positions for mlx : %i	%i\n", data->rays->h_y,
				data->rays->h_x);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->rays->space,
			data->rays->h_x, data->rays->h_y);
}
