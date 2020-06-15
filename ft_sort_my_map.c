/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_my_map.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:58:27 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/12 00:28:32 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char		*ft_strdup(const char *s1)
{
	int		s;
	char	*ptr;
	int		i;

	s = ft_strlen(s1);
	i = 0;
	ptr = (char *)malloc(sizeof(char) * (s + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char		*ft_strjoin_cub3d(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (s1 == 0 || s2 == 0)
		return (0);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (str == 0)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\n';
	i++;
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

int			check_map_characters(char *map, t_sto *mys)
{
	int	i;

	i = 0;
	while (map[i] != '\0')
	{
		if ((map[i] != '0') && (map[i] != '1') &&
		(map[i] != '2') && (map[i] != 'N') &&
		(map[i] != 'E') && (map[i] != 'S') && (map[i] != 'W') &&
		(map[i] != ' ') && (map[i] != '\n'))
		{
			mys->error = "Unknown character in map";
			return (-1);
		}
		i++;
	}
	return (1);
}

int			ft_find_map(char *line, t_sto *mys)
{
	char *temp;

	if (mys->map == NULL)
	{
		mys->map = ft_strdup(line);
		return (1);
	}
	temp = mys->map;
	mys->map = ft_strjoin_cub3d(temp, line);
	free(temp);
	return (check_map_characters(mys->map, mys));
}
