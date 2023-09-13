/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:03:04 by nprljic           #+#    #+#             */
/*   Updated: 2023/09/13 15:11:24 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "ft_getline/ft_getline.h"

void	have_3_color_values(t_data *data, t_map *file, char **color_rgb)
{
	int	i;

	i = 0;
	while (color_rgb[i])
		i++;
	if (i == 3)
		return ;
	free2d(color_rgb);
	free_texture_lines(data->data_line);
	free_map_exit(data, file, "Error\nNeed 3 color values.\n");
}

int	save_color(t_data *data, t_map *file, char *line)
{
	int		color_hex;
	char	**color_rgb;

	color_rgb = ft_split(line, ',');
	if (!color_rgb)
	{
		free_texture_lines(data->data_line);
		free_map_exit(data, file, "Error\nft_split failed\n");
	}
	have_3_color_values(data, file, color_rgb);
	if (string_rgb_to_int(color_rgb, &color_hex))
	{
		free2d(color_rgb);
		free_texture_lines(data->data_line);
		return (free_map_exit(data, file, NULL));
	}
	free2d(color_rgb);
	return (color_hex);
}
