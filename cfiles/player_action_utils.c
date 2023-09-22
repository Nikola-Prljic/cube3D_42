/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_action_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:02:15 by nprljic           #+#    #+#             */
/*   Updated: 2023/09/22 17:50:45 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	outside(t_data *data)
{
	int	pos_x;
	int	pos_y;

	pos_x = data->rays->px / TILE_SIZE;
	pos_y = data->rays->py / TILE_SIZE;
	if (pos_x > data->map_x || pos_x < 0)
	{
		data->rays->px = data->rays->px_init;
		data->rays->py = data->rays->py_init;
	}
	else if (pos_y > data->map_y || pos_y < 0)
	{
		data->rays->py = data->rays->py_init;
		data->rays->px = data->rays->px_init;
	}
}
