/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_more.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 12:05:46 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/17 17:19:38 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_floor_ceiling_fill(t_sto *mys, char c, int j, int numb)
{
	if (c == 'C')
		mys->c[j] = numb;
	if (c == 'F')
		mys->f[j] = numb;
	return (0);
}

int		floor_ceiling_colour(char *line, t_sto *mys, char c, int j)
{
	int	i;
	int	number;
	int	in;

	i = 2;
	number = 0;
	while ((line[i] >= '0' && line[i] <= '9') || (line[i] == ',') ||
	(line[i] == ' ') || (line[i] == '-'))
	{
		while (line[i] == ' ' || line[i] == ',')
			i++;
		while (line[i] >= '0' && line[i] <= '9')
		{
			number = number * 10 + (line[i] - '0');
			i++;
			in = 1;
		}
		if (in == 0 || line[i] == '-')
			return (error_text(mys, "Error in floor/ceiling colour", 0));
		number = ft_floor_ceiling_fill(mys, c, j, number);
		j++;
		in = 0;
	}
	return (j);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		ft_more_checks(char *line, t_sto *mys)
{
	if (((line[0] == 'F' && mys->f[0] != -1)) ||
	((line[0] == 'C' && mys->c[1] != -1)) || (mys->map != NULL)
	|| (mys->split != NULL))
		return (error_text(mys, "Ceiling/floor in .cub file wrong", 0));
	if (floor_ceiling_colour(line, mys, line[0], 0) != 3)
		return (error_text(mys, "Error in floor/ceiling color", 0));
	return (1);
}
