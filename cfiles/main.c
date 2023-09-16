/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:03:27 by rkurnava          #+#    #+#             */
/*   Updated: 2023/09/16 17:15:35 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_xpm_imgs(t_data *data, t_img *xpm_imgs)
{
	data->north = &xpm_imgs[0];
	data->south = &xpm_imgs[1];
	data->west = &xpm_imgs[2];
	data->east = &xpm_imgs[3];
	data->img = &xpm_imgs[4];
	data->north->img = NULL;
	data->south->img = NULL;
	data->west->img = NULL;
	data->east->img = NULL;
	data->img->img = NULL;
}

void	init_data(t_data *data)
{
	data->px = -1;
	data->py = -1;
	data->map_y = -1;
	data->map_x = -1;
	data->map = NULL;
	data->map_copy = NULL;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->rays = NULL;
	data->texture->north = NULL;
	data->texture->south = NULL;
	data->texture->west = NULL;
	data->texture->east = NULL;
	data->floor_rgb = -1;
	data->sky_rgb = -1;
	data->read_size = 0;
}

int	main(int argc, char **argv)
{
	int			fd;
	t_data		data;
	t_texture	texture;
	t_img		xpm_imgs[5];

	fd = -1;
	data.texture = &texture;
	init_data(&data);
	init_xpm_imgs(&data, xpm_imgs);
	if (input_handle(argc, argv, &fd))
		return (1);
	if (map_check(&data, fd) || window_loop(&data))
		return (free_data(&data));
	free_data(&data);
	return (0);
}
