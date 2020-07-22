/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:59:22 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/22 19:08:11 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	ft_more_side(t_master *big)
{
	if (big->ray.side == 0 && big->ray.ray_dir_x >= 0)
	{
		big->img.good_width = big->img.img_width3;
		big->img.good_height = big->img.img_height3;
		big->img.goodtex = big->img.texture3;
		big->img.goodaddrtex = big->img.addrtexture3;
		big->img.goodline_length = big->img.line_length3;
		big->img.good_bits_pixel = big->img.bits_per_pixel3;
	}
	if (big->ray.side == 1 && big->ray.ray_dir_y >= 0)
	{
		big->img.good_width = big->img.img_width4;
		big->img.good_height = big->img.img_height4;
		big->img.goodtex = big->img.texture4;
		big->img.goodaddrtex = big->img.addrtexture4;
		big->img.goodline_length = big->img.line_length4;
		big->img.good_bits_pixel = big->img.bits_per_pixel4;
	}
}

void	ft_find_out_side(t_master *big)
{
	if (big->ray.side == 0 && big->ray.ray_dir_x < 0)
	{
		big->img.good_width = big->img.img_width1;
		big->img.good_height = big->img.img_height1;
		big->img.goodtex = big->img.texture1;
		big->img.goodaddrtex = big->img.addrtexture1;
		big->img.goodline_length = big->img.line_length1;
		big->img.good_bits_pixel = big->img.bits_per_pixel1;
	}
	if (big->ray.side == 1 && big->ray.ray_dir_y < 0)
	{
		big->img.good_width = big->img.img_width2;
		big->img.good_height = big->img.img_height2;
		big->img.goodtex = big->img.texture2;
		big->img.goodaddrtex = big->img.addrtexture2;
		big->img.goodline_length = big->img.line_length2;
		big->img.good_bits_pixel = big->img.bits_per_pixel2;
	}
	ft_more_side(big);
}

void	ft_find_me_color(t_master *big, int y, int x)
{
	char	*dst;

	dst = big->img.goodaddrtex + (x * big->img.goodline_length + y *
	(big->img.good_bits_pixel / 8));
	big->img.color = *(unsigned int *)dst;
}

void	ver_dot(int x, int y, t_master *big)
{
	char	*dst;

	if (big->move.counter % 2 == 0)
	{
		dst = big->img.addr + (y * big->img.line_length + x *
		(big->img.bits_per_pixel / 8));
	}
	else
	{
		dst = big->sp.addr + (y * big->img.line_length + x *
		(big->img.bits_per_pixel / 8));
	}
	*(unsigned int*)dst = big->img.color;
}

void	ft_texturing(t_master *big, int start, int end, int x)
{
	ft_find_out_side(big);
	big->img.wall_x = big->ray.pos_x + big->ray.perpwalldist *
	big->ray.ray_dir_x;
	if (big->ray.side == 0)
		big->img.wall_x = big->ray.pos_y + big->ray.perpwalldist
		* big->ray.ray_dir_y;
	big->img.wall_x -= (int)big->img.wall_x;
	big->img.tex_y = (int)(big->img.wall_x * (float)big->img.good_width);
	if (big->ray.side == 0 && big->ray.ray_dir_x > 0)
		big->img.tex_y = big->img.good_width - big->img.tex_y - 1;
	if (big->ray.side == 1 && big->ray.ray_dir_y < 0)
		big->img.tex_y = big->img.good_width - big->img.tex_y - 1;
	big->img.tex_step = 1.0 * big->img.good_height /
	big->img.line_height;
	big->img.tex_pos = (start - big->mys.r[1] / 2 + big->img.line_height / 2)
	* big->img.tex_step;
	while (start < end)
	{
		big->img.tex_x = (int)big->img.tex_pos;
		big->img.tex_pos = big->img.tex_pos + big->img.tex_step;
		ft_find_me_color(big, big->img.tex_y, big->img.tex_x);
		ver_dot(x, start, big);
		start++;
	}
}
