/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:03:18 by rkurnava          #+#    #+#             */
/*   Updated: 2023/09/16 14:07:34 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	deg2rad(double degrees)
{
	return (degrees * (PI / 180.0));
}

double	rad2deg(double radians)
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
	if (data->rays)
		free(data->rays);
	free_data_exit(data, NULL, 0);
	return (0);
}
