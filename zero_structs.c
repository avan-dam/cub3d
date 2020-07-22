/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   zero_structs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:57:43 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/22 19:05:42 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_zero_tray(t_ray *ray)
{
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->plane_x = 0;
	ray->plane_y = 0;
	ray->camera_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->w = 0;
	ray->pos_x = 0;
	ray->pos_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->perpwalldist = 0;
	ray->side = 0;
	ray->color = 0;
}

void	ft_zero_t_move(t_move *move)
{
	move->up = 0;
	move->down = 0;
	move->rotate_left = 0;
	move->rotate_right = 0;
	move->move_right = 0;
	move->move_left = 0;
	move->counter = 0;
}

void	ft_more_zero(t_sto *mys)
{
	mys->no = 0;
	mys->so = 0;
	mys->we = 0;
	mys->ea = 0;
	mys->s = 0;
	mys->map = NULL;
	mys->split = NULL;
	mys->copy = NULL;
	mys->row = 0;
	mys->tilesize = 0;
	mys->save = 0;
	mys->error = NULL;
}

void	ft_zero_sprite_struct(t_sprite *sp, int i)
{
	if (i == 1)
	{
		sp->z_buf = NULL;
		sp->height = 0;
		sp->stripe = 0;
		sp->order = 0;
		sp->sprites = NULL;
		sp->numbsprite = 0;
	}
	sp->x = 0;
	sp->y = 0;
	sp->inv_det = 0;
	sp->trans_x = 0;
	sp->trans_y = 0;
	sp->screen_x = 0;
	sp->draw_start_y = 0;
	sp->draw_end_y = 0;
	sp->width = 0;
	sp->draw_start_x = 0;
	sp->draw_end_x = 0;
	sp->addr = NULL;
	sp->img = NULL;
	sp->v = 0;
}

void	ft_zero_struct(t_sto *mys)
{
	int i;

	i = 2;
	while (i >= 0)
	{
		mys->r[i] = 0;
		i--;
	}
	i = 3;
	while (i >= 0)
	{
		mys->f[i] = -1;
		i--;
	}
	i = 3;
	while (i >= 0)
	{
		mys->c[i] = -1;
		i--;
	}
	ft_more_zero(mys);
}
