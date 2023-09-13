/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:02:49 by rkurnava          #+#    #+#             */
/*   Updated: 2023/09/13 19:08:29 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_extension(char *map_path)
{
	int	i;

	i = 0;
	while (map_path[i])
		i++;
	if (i < 4)
		return (1);
	i--;
	if (map_path[i] == 'b' && map_path[i - 1] == 'u' && map_path[i - 2] == 'c'
		&& map_path[i - 3] == '.')
		return (0);
	return (1);
}

int	check_input(char *map_path, int *fd)
{
	if (!map_path || map_path == NULL)
		return (1);
	*fd = open(map_path, O_RDONLY);
	if (*fd <= 0)
	{
		puterror("Error\nCan't find/access map!\n");
		puterror("Make sure you have correct rights / name of the map!\n");
		puterror("Map file has to be placed in maps folder\n");
		return (1);
	}
	if (map_extension(map_path))
	{
		close(*fd);
		return (puterror("Error\nInvalid map extension!\n"));
	}
	return (0);
}

int	input_handle(int argc, char **argv, int *fd)
{
	char	*map_file;

	if (argc != 2)
		return (puterror("Error\nInvalid number of parameters\n"));
	if (argv[1][0] == 0 && ft_strlen(argv[1]) == 0)
		return (puterror("Error\nArgv[1] is an empty string\n"));
	map_file = ft_strj("maps/", argv[1]);
	if (map_file == NULL)
	{
		puterror("Error\nMalloc in input_handle failed!\n");
		return (1);
	}
	if (check_input(map_file, fd))
	{
		free(map_file);
		return (1);
	}
	if (map_file != NULL)
		free(map_file);
	return (0);
}
