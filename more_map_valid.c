/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   more_map_valid.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 17:00:19 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/16 18:17:42 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int		ft_duplicate_map(t_sto *mys)
{
	int i;
	int j;
	int length;

	i = 0;
	j = 0;
	mys->copy = (char**)malloc(sizeof(char*) * (mys->row + 1));
	if (mys->copy == NULL)
		return (-1);
	while (i < mys->row)
	{
		length = ft_strlen(mys->split[i]);
		mys->copy[i] = (char *)malloc(sizeof(char) * (length + 1));
		while (j < ft_strlen(mys->split[i]))
		{
			mys->copy[i][j] = mys->split[i][j];
			j++;
		}
		mys->copy[i][j] = '\0';
		j = 0;
		i++;
	}
	mys->copy[mys->row] = NULL;
	return (1);
}

int		ft_free_copy(t_sto *mys, int i)
{
	int x;

	x = 0;
	while (x < mys->row)
	{
		if (mys->copy[x])
		{
			free(*mys->copy);
			*mys->copy = 0;
		}
		x++;
	}
	return (i);
}
