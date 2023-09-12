/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:52:09 by nprljic           #+#    #+#             */
/*   Updated: 2023/09/12 18:50:53 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETLINE_H
# define FT_GETLINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../../../includes/cub3d.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

size_t	int_strlen(char *s);
char	*ft_getline(t_data *data, int fd, char **remain, char delimiter);
char	*ft_linejoin(t_data *data, char *s1, char *s2);
char	*ft_strchr(char *s, int c);

#endif
