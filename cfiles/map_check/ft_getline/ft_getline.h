/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:52:09 by nprljic           #+#    #+#             */
/*   Updated: 2023/09/16 19:10:35 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETLINE_H
# define FT_GETLINE_H

# include "../../../includes/cub3d.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

size_t	int_strlen(char *s);
void	map_size_check_and_read_protaction(t_data *data, char *buf,
			char *remain, int ret);
char	*ft_getline(t_data *data, int fd, char **remain, char delimiter);
char	*ft_linejoin(t_data *data, char *s1, char *s2);
char	*ft_strchr(char *s, int c);

#endif
