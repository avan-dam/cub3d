/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:58:36 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/10 18:12:26 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	free_me(t_sto *mys, int m)
{
	int	i;

	i = 0;
	free(mys->map);
	while (i < m)
	{
		free(mys->split[i]);
		i++;
	}
	free(mys->split);
	return (-1);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	m;

	i = 0;
	m = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		m++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (m);
}

static char	*new_arrays(char const *s, int start, int end)
{
	char	*array;
	int		len;
	int		i;

	i = 0;
	len = end - start;
	array = 0;
	array = (char *)malloc(sizeof(char) * (len + 2));
	if (array == NULL)
		return (NULL);
	while (i <= len && s[start] != '\0')
	{
		array[i] = s[start];
		i++;
		start++;
	}
	array[i] = '\0';
	return (array);
}

static int	find_first_last(char const *s, char c, t_sto *mys)
{
	int	i;
	int	m;
	int	start;
	int	end;

	i = 0;
	m = 0;
	while (s[i] != '\0')
	{
		if (i == 0 && s[i] != c)
			start = i;
		else if (s[i] == c && s[i + 1] != '\0' && s[i + 1] != c)
			start = i + 1;
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
		{
			end = i;
			mys->split[m] = new_arrays(s, start, end);
			if (mys->split[m] == NULL)
				return (free_me(mys, m));
			m++;
		}
		i++;
	}
	return (1);
}

int			ft_split_cub3d(char const *s, char c, t_sto *mys)
{
	int	words;
	int	i;

	if (s == 0)
		return (-1);
	i = 0;
	words = count_words(s, c);
	mys->row = words;
	mys->split = (char**)malloc(sizeof(char*) * (words + 1));
	if (mys->split == NULL)
		return (-1);
	if (words == 0)
	{
		mys->split[0] = 0;
		free(mys->map);
		return (-1);
	}
	if (find_first_last(s, c, mys) == 0)
		return (-1);
	mys->split[words] = NULL;
	return (1);
}
