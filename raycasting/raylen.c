/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raylen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:24:19 by rkurnava          #+#    #+#             */
/*   Updated: 2023/08/22 19:32:58 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	raylen(t_data *data)
{
	float	ray_angle;

	ray_angle = data->rays->player_dir;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->rays->space,
		data->rays->pcor_x + cos(ray_angle) * 30 - 5, data->rays->pcor_y
		+ sin(ray_angle) * 30 - 5);
}
