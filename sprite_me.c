/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_me.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:59:04 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/12 01:14:05 by Amber         ########   odam.nl         */
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
			if (sprite_dist[big->sprite.order[j]] <
			sprite_dist[big->sprite.order[j + 1]])
			{
				temp = big->sprite.order[j];
				big->sprite.order[j] = big->sprite.order[j + 1];
				big->sprite.order[j + 1] = temp;
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
	big->sprite.inv_det = 1.0 / (big->ray.plane_x * big->ray.dir_y -
	big->ray.dir_x * big->ray.plane_y);
	big->sprite.trans_x = big->sprite.inv_det * (big->ray.dir_y *
	big->sprite.x - big->ray.dir_x * big->sprite.y);
	big->sprite.trans_y = big->sprite.inv_det * (-big->ray.plane_y *
	big->sprite.x + big->ray.plane_x * big->sprite.y);
	big->sprite.screen_x = (int)((big->mys.r[0] / 2) *
	(1 + big->sprite.trans_x / big->sprite.trans_y));
	big->sprite.height = abs((int)(big->mys.r[1] / (big->sprite.trans_y)));
	big->sprite.draw_start_y = -big->sprite.height / 2 + big->mys.r[1] / 2;
	if (big->sprite.draw_start_y < 0)
		big->sprite.draw_start_y = 0;
	big->sprite.draw_end_y = (big->sprite.height / 2 + big->mys.r[1] / 2);
	if (big->sprite.draw_end_y >= big->mys.r[1])
		big->sprite.draw_end_y = big->mys.r[1] - 1;
	big->sprite.width = abs((int)(big->mys.r[1] / (big->sprite.trans_y)));
	big->sprite.draw_start_x = -big->sprite.width / 2 +
	big->sprite.screen_x;
	if (big->sprite.draw_start_x < 0)
		big->sprite.draw_start_x = 0;
	big->sprite.draw_end_x = (int)(big->sprite.width / 2 +
	big->sprite.screen_x);
	if (big->sprite.draw_end_x >= big->mys.r[0])
		big->sprite.draw_end_x = big->mys.r[0] - 1;
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

	big->sprite.stripe = big->sprite.draw_start_x;
	while (big->sprite.stripe < big->sprite.draw_end_x)
	{
		tex_x = (int)((256 * (big->sprite.stripe - (-big->sprite.width / 2 +
		big->sprite.screen_x)) * big->img.img_width5 / big->sprite.width)
		/ 256);
		if (big->sprite.trans_y > 0 && big->sprite.stripe > 0
		&& big->sprite.stripe < big->mys.r[0] && big->sprite.trans_y
		< big->sprite.z_buf[big->sprite.stripe])
		{
			y = (int)big->sprite.draw_start_y;
			while (y < big->sprite.draw_end_y)
			{
				ft_find_me_sprite_color(big, tex_x, y);
				ver_dot_sprite(big->sprite.stripe, y, big);
				y++;
			}
		}
		big->sprite.stripe++;
	}
}

int		ft_sprite_put(t_master *big, int i)
{
	int			order[big->sprite.numbsprite];
	float		sprite_dist[big->sprite.numbsprite];

	big->sprite.order = order;
	while (i < big->sprite.numbsprite)
	{
		big->sprite.order[i] = i;
		sprite_dist[i] = ((big->ray.pos_x - big->sprite.sprites[i][1]) *
		(big->ray.pos_x - big->sprite.sprites[i][1]) + (big->ray.pos_y -
		big->sprite.sprites[i][0]) * (big->ray.pos_y -
		big->sprite.sprites[i][0]));
		i++;
	}
	i = sort_sprites(sprite_dist, big->sprite.numbsprite, big);
	while (i < big->sprite.numbsprite)
	{
		big->sprite.x = big->sprite.sprites[big->sprite.order[i]][1]
		- big->ray.pos_x + 0.5;
		big->sprite.y = big->sprite.sprites[big->sprite.order[i]][0]
		- big->ray.pos_y + 0.5;
		start_value_sprite(big);
		sprite_working(big);
		i++;
	}
	return (1);
}
