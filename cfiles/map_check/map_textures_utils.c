/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:40:26 by nprljic           #+#    #+#             */
/*   Updated: 2023/09/22 13:50:06 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "ft_getline/ft_getline.h"

int	rm_space_in_front(t_handle_textures *d)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (!d->texture_path || !d->texture_path[0] || d->texture_path[0] != ' ')
		return (0);
	while (d->texture_path[i] == ' ')
		i++;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(d->texture_path) - i
				+ 1));
	if (!new_str)
		return (1);
	while (d->texture_path[i])
	{
		new_str[j] = d->texture_path[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	free(d->texture_path);
	d->texture_path = new_str;
	return (0);
}
