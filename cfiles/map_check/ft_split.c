/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:07:43 by nprljic           #+#    #+#             */
/*   Updated: 2023/09/13 15:11:13 by nprljic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_substr(char const *s, int start, int len)
{
	char	*dest;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	if (ft_strlen(s) < start)
		len = 0;
	else if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (i < len && s[i])
	{
		dest[i] = s[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	count_words(const char *s, char c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (*s)
	{
		if (*s != c && x == 0)
		{
			x = 1;
			i++;
		}
		else if (*s == c)
			x = 0;
		s++;
	}
	return (i);
}

static int	len_just_str(const char *s, int start, char c)
{
	int	i;

	i = 0;
	while (s[start] != c && start < (int)ft_strlen(s))
	{
		start++;
		i++;
	}
	return (i);
}

static char	**head(char **s2d, char const *s, char c)
{
	int	i;
	int	x;
	int	len;

	i = 0;
	x = 0;
	len = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && i != ft_strlen(s))
		{
			len = len_just_str(s, i, c);
			s2d[x] = ft_substr(s, i, len);
			if (!s2d[x])
			{
				free2d(s2d);
				return (NULL);
			}
			i += len;
			x++;
			s2d[x] = NULL;
		}
		i++;
	}
	return (s2d);
}

char	**ft_split(char const *s, char c)
{
	char	**s2d;

	if (!s)
		return (0);
	s2d = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s2d)
		return (0);
	return (head(s2d, s, c));
}
