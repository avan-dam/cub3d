/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   zero_structs_more.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:59:11 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/22 19:07:54 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_zero_all(t_master *big)
{
	ft_zero_struct(&big->mys);
	ft_zero_sprite_struct(&big->sp, 1);
	ft_zero_t_move(&big->move);
	ft_zero_tray(&big->ray);
	ft_zero_tdata(&big->img);
}

void	ft_zero_tdata_more_more(t_data *img)
{
	img->img_height1 = 0;
	img->img_width2 = 0;
	img->img_height2 = 0;
	img->img_width3 = 0;
	img->img_height3 = 0;
	img->img_width4 = 0;
	img->img_height4 = 0;
	img->img_width5 = 0;
	img->img_height5 = 0;
}

void	ft_zero_tdata_more(t_data *img)
{
	img->bits_per_pixel1 = 0;
	img->bits_per_pixel2 = 0;
	img->bits_per_pixel3 = 0;
	img->bits_per_pixel4 = 0;
	img->bits_per_pixel5 = 0;
	img->good_width = 0;
	img->good_height = 0;
	img->goodtex = 0;
	img->goodaddrtex = 0;
	img->goodline_length = 0;
	img->good_bits_pixel = 0;
	img->wall_x = 0;
	img->tex_step = 0;
	img->line_height = 0;
	img->addr = NULL;
	img->tex_x = 0;
	img->mlx = NULL;
	img->mlx_win = NULL;
	ft_zero_tdata_more_more(img);
}

void	ft_zero_tdata(t_data *img)
{
	img->img = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->line_length1 = 0;
	img->line_length2 = 0;
	img->line_length3 = 0;
	img->line_length4 = 0;
	img->line_length5 = 0;
	img->endian = 0;
	img->color = 0;
	img->color_sprite = 0;
	img->texture1 = 0;
	img->addrtexture1 = 0;
	img->texture2 = 0;
	img->addrtexture2 = 0;
	img->texture3 = 0;
	img->addrtexture3 = 0;
	img->texture4 = 0;
	img->addrtexture4 = 0;
	img->sprite = 0;
	img->addrsprite = 0;
	img->img_width1 = 0;
	img->tex_y = 0;
	img->tex_pos = 0;
	ft_zero_tdata_more(img);
}
