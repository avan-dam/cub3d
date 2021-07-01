/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 17:01:47 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/17 15:44:53 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int		error_text(t_sto *mys, char *error, int i)
{
	if (mys->error == NULL && error != NULL)
		mys->error = ft_strdup(error);
	if (i == 1)
		return (ft_error(mys));
	return (-1);
}

int		ft_error(t_sto *mys)
{
	ft_putstr("Error\n");
	ft_putstr(mys->error);
	if ((mys->error == NULL) || (mys->error == 0))
		ft_putstr("error in .cub file");
	mys->error = NULL;
	ft_zero_struct(mys);
	return (-1);
}

int		free_storage(char **storage, t_sto *mys)
{
	if (mys->error == NULL)
		mys->error = "problem with map";
	if (*storage)
	{
		free(*storage);
		*storage = 0;
	}
	return (-1);
}

int		closeme(int keycode, t_master *big)
{
	if (keycode == 53)
	{
		mlx_clear_window(big->img.mlx, big->img.mlx_win);
		mlx_destroy_window(big->img.mlx, big->img.mlx_win);
		ft_zero_all(big);
		free(big->img.mlx);
		exit(0);
	}
	return (0);
}

int		exit_program(t_master *big)
{
	mlx_destroy_window(big->img.mlx, big->img.mlx_win);
	exit(0);
	ft_zero_all(big);
	free(big->img.mlx);
	return (0);
}
