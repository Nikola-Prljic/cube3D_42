/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_colors_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:08:11 by rkurnava          #+#    #+#             */
/*   Updated: 2023/09/12 19:08:38 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	string_rgb_to_int(char **color_rgb, int *color)
{
	int	r;
	int	g;
	int	b;

	if (is_number(color_rgb[0], &r))
		return (1);
	if (is_number(color_rgb[1], &g))
		return (1);
	if (is_number(color_rgb[2], &b))
		return (1);
	*color = (r << 16) + (g << 8) + b;
	return (0);
}
