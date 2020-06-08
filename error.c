/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 17:01:47 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/08 17:52:40 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		error_text(t_sto *mys, char *error, int i)
{
	if (mys->error == NULL)
		mys->error = error;
	if (i == 1)
        return (ft_error(mys));
    return (-1);
}

int		ft_error(t_sto *mys)
{
	ft_putstr("Error\n");
	ft_putstr(mys->error);
	if (mys->error == NULL)
		ft_putstr("error in .cub file");
	return (-1);
}

int		free_storage(char **storage, t_sto *mys)
{
	if (mys->error == NULL)
		mys->error = "Failed to get next line";
	if (*storage)
	{
		free(*storage);
		*storage = 0;
	}
	return (-1);
}
