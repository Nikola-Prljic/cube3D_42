/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:39:55 by nprljic           #+#    #+#             */
/*   Updated: 2023/09/12 21:07:47 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_imgs(t_data *data)
{
	if (!data->mlx_ptr)
		return ;
	if (data->north->img)
		mlx_destroy_image(data->mlx_ptr, data->north->img);
	if (data->west->img)
		mlx_destroy_image(data->mlx_ptr, data->west->img);
	if (data->east->img)
		mlx_destroy_image(data->mlx_ptr, data->east->img);
	if (data->south->img)
		mlx_destroy_image(data->mlx_ptr, data->south->img);
}

void	free_mlx_data(t_data *data)
{
	free_imgs(data);
	if (data->img->img)
	{
		mlx_destroy_image(data->mlx_ptr, data->img->img);
		data->img->img = NULL;
	}
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	data->mlx_ptr = NULL;
}

int	free_data(t_data *data)
{
	if (data->map)
	{
		free2d(data->map);
		data->map = NULL;
	}
	if (data->map_copy)
	{
		free2d(data->map_copy);
		data->map_copy = NULL;
	}
	free_set_null(&data->texture->north);
	free_set_null(&data->texture->south);
	free_set_null(&data->texture->west);
	free_set_null(&data->texture->east);
	if (data->mlx_ptr)
	{
		free_mlx_data(data);
	}
	return (1);
}
