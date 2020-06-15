/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sav_bp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:58:50 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/12 01:01:48 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int		ft_save(t_master *big)
{
	if (big->mys.save == 1)
	{
		open("screenshot.bmp", O_RDWR | O_CREAT | O_SYNC);
		return (1);
	}
	return (0);
}
