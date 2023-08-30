/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline_ultis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <rkurnava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:53:33 by nprljic           #+#    #+#             */
/*   Updated: 2023/08/30 15:56:16 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getline.h"

size_t	int_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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

char	*ft_linejoin(t_data *data, char *s1, char *s2)
{
	size_t	i;
	char	*dest;
	int		s1_len;
	size_t	s2_len;
	int		dest_len;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		if(!s1)
		{
			free_set_null(&s2);
			free_data_exit(data, "Error\nMalloc failed at ft_linejoin");
		}
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	i = 0;
	s1_len = int_strlen(s1);
	s2_len = int_strlen(s2);
	dest_len = s1_len + s2_len;
	dest = malloc(dest_len * sizeof(char) + 1);
	if (!dest)
	{
		free_set_null(&s1);
		free_set_null(&s2);
		free_data_exit(data, "Error\nMalloc failed at ft_linejoin");
	}
	ft_cpynonull(dest, s1, i);
	ft_cpynonull_s2(dest, s2, s2_len, s1_len);
	dest[dest_len] = '\0';
	free(s1);
	return (dest);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)(&s[int_strlen(s)]));
	while (*s)
	{
		if (*s == (char)(c))
			return ((char *)(s));
		s++;
	}
	return (NULL);
}
