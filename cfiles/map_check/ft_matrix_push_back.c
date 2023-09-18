/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_push_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:59:04 by nprljic           #+#    #+#             */
/*   Updated: 2023/09/18 16:59:26 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "ft_getline/ft_getline.h"

int	free_map_exit(t_data *data, t_map *file, char *msg)
{
	free_data(data);
	if (file->buffer)
	{
		free(file->buffer);
		file->buffer = NULL;
	}
	if (msg)
		puterror(msg);
	if (file->fd != -1)
	{
		close(file->fd);
		file->fd = -1;
	}
	exit(1);
}

void	ft_strdup_protaction(t_data *data, t_map *file, char *str,
		char *new_matrix)
{
	if (!new_matrix)
	{
		free_set_null(&str);
		free_map_exit(data, file,
			"Error\nMalloc failed in ft_matrix_push_back\n");
	}
}

void	new_matrix_malloc_protaction(t_data *data, t_map *file,
		char **new_matrix, char *str)
{
	if (!new_matrix)
	{
		free_set_null(&str);
		free_map_exit(data, file,
			"Error\nMalloc failed in ft_matrix_push_back\n");
	}
}

int	ft_matrix_push_back(t_data *data, t_map *file, char *str)
{
	int		i;
	char	**new_matrix;

	i = 0;
	if (!str)
		return (1);
	while (data->map[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 2));
	new_matrix_malloc_protaction(data, file, new_matrix, str);
	i = -1;
	while (data->map[++i])
	{
		new_matrix[i] = ft_strdup(data->map[i]);
		ft_strdup_protaction(data, file, str, new_matrix[i]);
	}
	new_matrix[i] = ft_strdup(str);
	ft_strdup_protaction(data, file, str, new_matrix[i]);
	new_matrix[i + 1] = NULL;
	free2d(data->map);
	data->map = new_matrix;
	return (0);
}
