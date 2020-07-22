/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_me.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:59:04 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/22 19:04:45 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int		ft_load_sprite(t_master *big)
{
	char	*end;

	end = ft_substr(big->mys.s, ft_strlen(big->mys.s) - 3, 3);
	if (ft_strcmp("png", end) == 0)
	{
		big->img.sprite = mlx_png_file_to_image(big->img.mlx, big->mys.s,
		&big->img.img_width5, &big->img.img_height5);
	}
	else if (ft_strcmp("xpm", end) == 0)
	{
		big->img.sprite = mlx_xpm_file_to_image(big->img.mlx, big->mys.s,
		&big->img.img_width5, &big->img.img_height5);
	}
	else
		return (error_text(&big->mys, "error in loading sprite", 0));
	free(end);
	big->img.addrsprite = mlx_get_data_addr(big->img.sprite,
	&big->img.bits_per_pixel5, &big->img.line_length5, &big->img.endian2);
	return (1);
}

int		sort_sprites(float *sprite_dist, int numb, t_master *big)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	j = 0;
	while (i < numb - 1)
	{
		while (j < numb - i - 1)
		{
			if (sprite_dist[big->sp.order[j]] <
			sprite_dist[big->sp.order[j + 1]])
			{
				temp = big->sp.order[j];
				big->sp.order[j] = big->sp.order[j + 1];
				big->sp.order[j + 1] = temp;
				j = -1;
				i = 0;
			}
			j++;
		}
		i++;
	}
	return (0);
}

/*
** [inv_det for correct matrix multiplication]
** [using "transformY" instead of the real distance prevents fisheye]
*/

void	start_value_sprite(t_master *big)
{
	big->sp.inv_det = 1.0 / (big->ray.plane_x * big->ray.dir_y -
	big->ray.dir_x * big->ray.plane_y);
	big->sp.trans_x = big->sp.inv_det * (big->ray.dir_y *
	big->sp.x - big->ray.dir_x * big->sp.y);
	big->sp.trans_y = big->sp.inv_det * (-big->ray.plane_y *
	big->sp.x + big->ray.plane_x * big->sp.y);
	big->sp.v = (int)(250 / big->sp.trans_y);
	big->sp.screen_x = (int)((big->mys.r[0] / 2) *
	(1.0 + big->sp.trans_x / big->sp.trans_y));
	big->sp.height = fabs((int)(big->mys.r[1] / (big->sp.trans_y)) * 0.825);
	big->sp.draw_start_y = -big->sp.height / 2 + big->mys.r[1] / 2 + big->sp.v;
	if (big->sp.draw_start_y < 0)
		big->sp.draw_start_y = 0;
	big->sp.draw_end_y = big->sp.height / 2 + big->mys.r[1] / 2 + big->sp.v;
	if (big->sp.draw_end_y >= big->mys.r[1])
		big->sp.draw_end_y = big->mys.r[1] - 1;
	big->sp.width = fabs((int)(big->mys.r[1] / (big->sp.trans_y)) * 0.825);
	big->sp.draw_start_x = (int)(-big->sp.width / 2 +
	big->sp.screen_x);
	if (big->sp.draw_start_x < 0)
		big->sp.draw_start_x = 0;
	big->sp.draw_end_x = (int)(big->sp.width / 2 +
	big->sp.screen_x);
	if (big->sp.draw_end_x >= big->mys.r[0])
		big->sp.draw_end_x = big->mys.r[0] - 1;
}

/*
** [IF: (1) it's in front of (you/) camera plane]
** [(2) it's on the screen (left) (3) right]
** [(4) ZBuffer, with perpendicular distance]
** [256 and 128 factors to avoid floats]
*/

void	sprite_working(t_master *big)
{
	int		tex_x;
	int		y;

	big->sp.stripe = big->sp.draw_start_x;
	while (big->sp.stripe < big->sp.draw_end_x)
	{
		tex_x = (int)((256 * (big->sp.stripe - (-big->sp.width / 2 +
		big->sp.screen_x)) * big->img.img_width5 / big->sp.width)
		/ 256);
		if (big->sp.trans_y > 0 && big->sp.stripe > 0
		&& big->sp.stripe < big->mys.r[0] && big->sp.trans_y
		< big->sp.z_buf[big->sp.stripe])
		{
			y = (int)big->sp.draw_start_y;
			while (y < big->sp.draw_end_y)
			{
				ft_find_me_sprite_color(big, tex_x, y);
				ver_dot_sprite(big->sp.stripe, y, big);
				y++;
			}
		}
		big->sp.stripe++;
	}
}

int		ft_sprite_put(t_master *big, int i)
{
	int			order[big->sp.numbsprite];
	float		sprite_dist[big->sp.numbsprite];

	big->sp.order = order;
	while (i < big->sp.numbsprite)
	{
		big->sp.order[i] = i;
		sprite_dist[i] = ((big->ray.pos_x - big->sp.sprites[i][1]) *
		(big->ray.pos_x - big->sp.sprites[i][1]) + (big->ray.pos_y -
		big->sp.sprites[i][0]) * (big->ray.pos_y -
		big->sp.sprites[i][0]));
		i++;
	}
	i = sort_sprites(sprite_dist, big->sp.numbsprite, big);
	while (i < big->sp.numbsprite)
	{
		big->sp.x = big->sp.sprites[big->sp.order[i]][1]
		- big->ray.pos_x + 0.5;
		big->sp.y = big->sp.sprites[big->sp.order[i]][0]
		- big->ray.pos_y + 0.5;
		start_value_sprite(big);
		sprite_working(big);
		i++;
	}
	return (1);
}
