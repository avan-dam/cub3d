/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites_more.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:58:41 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/23 12:32:58 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	ft_store_sprite(t_master *big)
{
	int	x;
	int	y;
	int	j;

	x = 0;
	y = 0;
	j = 0;
	while (x < big->mys.row)
	{
		while (big->mys.split[x][y] != '\0')
		{
			if (big->mys.split[x][y] == '2')
			{
				big->sp.sprites[j][0] = x;
				big->sp.sprites[j][1] = y;
				j++;
			}
			y++;
		}
		y = 0;
		x++;
	}
}

void	ft_numb_sprites(t_master *big)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < big->mys.row)
	{
		while (big->mys.split[x][y] != '\0')
		{
			if (big->mys.split[x][y] == '2')
				big->sp.numbsprite++;
			y++;
		}
		y = 0;
		x++;
	}
	big->sp.sprites = (int**)malloc(sizeof(int*) *
	(big->sp.numbsprite + 1));
	x = 0;
	while (x < big->sp.numbsprite)
	{
		big->sp.sprites[x] = (int *)malloc(sizeof(int) * 2);
		x++;
	}
	ft_store_sprite(big);
}

void	ft_find_me_sprite_color(t_master *big, int tex_x, int y)
{
	char	*dst;
	int		d;
	int		tex_y;

	dst = NULL;
	d = (y - big->sp.v) * 2 - big->mys.r[1] + big->sp.height;
	tex_y = (int)(((d * big->img.img_height5) / big->sp.height) / 2);
	dst = big->img.addrsprite + (tex_y * big->img.line_length5 + tex_x *
	(big->img.bits_per_pixel5 / 8));
	big->img.color_sprite = *(unsigned int *)dst;
}

void	ver_dot_sprite(int x, int y, t_master *big)
{
	char	*dst;

	dst = NULL;
	if (big->img.color_sprite != 0x00000000)
	{
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
		*(unsigned int*)dst = big->img.color_sprite;
	}
}

char	*ft_substr(char *s, int start, int len)
{
	char	*substr;
	int		j;
	int		slen;

	j = 0;
	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_strdup(""));
	if (start + len > slen)
		len = ft_strlen(s) - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	while (j < len && s[start] != '\0')
	{
		substr[j] = s[start];
		j++;
		start++;
	}
	substr[j] = '\0';
	return (substr);
}
