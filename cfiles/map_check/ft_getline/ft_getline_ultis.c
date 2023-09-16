/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline_ultis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:53:33 by nprljic           #+#    #+#             */
/*   Updated: 2023/09/16 13:58:33 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getline.h"

static char	*ft_cpynonull(char *dest, char const *s1, int i)
{
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	return (dest);
}

static char	*ft_cpynonull_s2(char *dest, char const *s2, size_t s2_len,
		size_t s1_len)
{
	size_t	i;

	i = 0;
	while (i < s2_len)
	{
		dest[s1_len] = s2[i];
		s1_len++;
		i++;
	}
	return (dest);
}

void	check_s1(t_data *data, char **s1, char **s2)
{
	*s1 = (char *)malloc(1 * sizeof(char));
	if (!*s1)
	{
		free_set_null(s2);
		free_data_exit(data, "Error\nMalloc failed at ft_linejoin\n", 1);
	}
	*s1[0] = '\0';
}

void	check_dest(t_data *data, char **s1, char **s2)
{
	free_set_null(s1);
	free_set_null(s2);
	free_data_exit(data, "Error\nMalloc failed at ft_linejoin\n", 1);
}

char	*ft_linejoin(t_data *data, char *s1, char *s2)
{
	size_t	i;
	char	*dest;
	int		s1_len;
	size_t	s2_len;
	int		dest_len;

	if (!s1)
		check_s1(data, &s1, &s2);
	if (!s1 || !s2)
		return (NULL);
	i = 0;
	s1_len = int_strlen(s1);
	s2_len = int_strlen(s2);
	dest_len = s1_len + s2_len;
	dest = (char *)malloc(dest_len * sizeof(char) + 1);
	if (!dest)
		check_dest(data, &s1, &s2);
	ft_cpynonull(dest, s1, i);
	ft_cpynonull_s2(dest, s2, s2_len, s1_len);
	dest[dest_len] = '\0';
	free(s1);
	return (dest);
}
