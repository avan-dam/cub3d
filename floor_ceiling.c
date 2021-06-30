/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floor_ceiling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 17:00:09 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/22 19:07:41 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

unsigned int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void			find_ceiling_floor_hx(t_sto *mys)
{
	mys->ceilingcolor = create_trgb(0, mys->c[0], mys->c[1], mys->c[2]);
	mys->floorcolor = create_trgb(0, mys->f[0], mys->f[1], mys->f[2]);
}

void			ft_draw_ceiling(t_master *big, int y, int x, char *dst)
{
	int	i;

	i = 0;
	while (i < y)
	{
		if (big->move.counter % 2 == 0)
		{
			dst = big->img.addr + (i * big->img.line_length + x *
			(big->img.bits_per_pixel / 8));
		}
		else
		{
			dst = big->sp.addr + (i * big->img.line_length + x *
			(big->img.bits_per_pixel / 8));
		}
		*(unsigned int*)dst = big->mys.ceilingcolor;
		i++;
	}
}

void			ft_draw_floor(t_master *big, int y2, int x, char *dst)
{
	while (y2 < big->mys.r[1])
	{
		if (big->move.counter % 2 == 0)
		{
			dst = big->img.addr + (y2 * big->img.line_length + x *
			(big->img.bits_per_pixel / 8));
		}
		else
		{
			dst = big->sp.addr + (y2 * big->img.line_length + x *
			(big->img.bits_per_pixel / 8));
		}
		*(unsigned int*)dst = big->mys.floorcolor;
		y2++;
	}
}
