/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadtextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:03:25 by rkurnava          #+#    #+#             */
/*   Updated: 2023/09/16 13:59:43 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	open_textures(t_data *data, t_img *xpm_img, char *path)
{
	xpm_img->img = mlx_xpm_file_to_image(data->mlx_ptr, path, &xpm_img->width,
			&xpm_img->height);
	if (!xpm_img->img)
		return (1);
	return (0);
}

void	loadtextures(t_data *data, t_img *xpm_img, char **path)
{
	if (open_textures(data, xpm_img, *path))
	{
		if (data->rays)
			free(data->rays);
		free_set_null(path);
		free_data_exit(data, "Error\nLoad texture failed\n", 1);
	}
	free_set_null(path);
	return ;
}

void	load_all_textures(t_data *data)
{
	loadtextures(data, data->north, &data->texture->north);
	loadtextures(data, data->south, &data->texture->south);
	loadtextures(data, data->west, &data->texture->west);
	loadtextures(data, data->east, &data->texture->east);
	return ;
}
