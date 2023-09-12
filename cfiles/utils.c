/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:03:31 by rkurnava          #+#    #+#             */
/*   Updated: 2023/09/12 19:06:02 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strj(char const *s1, char const *s2)
{
	char	*jstr;
	char	*str1;
	char	*str2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	if (!s1 || !s2)
		return (NULL);
	jstr = malloc((ft_strlen(str1) + ft_strlen(str2)) + 1);
	if (!jstr)
		return (NULL);
	while (str1[i])
		jstr[j++] = str1[i++];
	i = 0;
	while (str2[i])
		jstr[j++] = str2[i++];
	jstr[j] = '\0';
	return (jstr);
}

int	puterror(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

void	printmap(char **map)
{
	int	y;
	int	x;

	if (!map)
		return ;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			write(1, &map[y][x], 1);
		write(1, "\n", 1);
	}
}

void	free2d(char **map)
{
	int	y;

	if (!map)
		return ;
	y = -1;
	while (map[++y])
		free(map[y]);
	free(map);
}
