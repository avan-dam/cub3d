/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_info.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 17:00:14 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/11 23:36:58 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libgnl.h"

int		fill_res(char *line, t_sto *mys, int i, int j)
{
	long int		number;

	number = 0;
	if (mys->map != NULL || mys->r[0] != 0)
		return (error_text(mys, "Error in resolution", 0));
	while (line[i] == ' ' || (line[i] >= '0' && line[i] <= '9'))
	{
		while (line[i] == ' ')
			i++;
		while (line[i] >= '0' && line[i] <= '9')
		{
			number = number * 10 + (line[i] - '0');
			i++;
		}
		mys->r[j] = number;
		number = 0;
		j++;
		if (j > 2)
			return (error_text(mys, "Error in resolution", 0));
	}
	mys->r[j] = '\0';
	if (line[i] == '\0')
		return (1);
	return (error_text(mys, "Error in resolution", 0));
}

int		ft_texture_correct(char *line, t_sto *mys, char *texture)
{
	if (line[0] == 'N' && line[1] == 'O')
	{
		if (mys->no != 0)
			return (error_text(mys, "Error in north texture", 0));
		mys->no = texture;
	}
	if (line[0] == 'S' && line[1] == 'O')
	{
		if (mys->so != 0)
			return (error_text(mys, "Error in south texture", 0));
		mys->so = texture;
	}
	if (line[0] == 'W' && line[1] == 'E')
	{
		if (mys->we != 0)
			return (error_text(mys, "Error in west texture", 0));
		mys->we = texture;
	}
	if (line[0] == 'E' && line[1] == 'A')
	{
		if (mys->ea != 0)
			return (error_text(mys, "Error in east texture", 0));
		mys->ea = texture;
	}
	return (1);
}

int		fill_texture(char *line, t_sto *mys)
{
	int		length;
	char	*texture;
	int		i;

	i = 3;
	while (line[i] == ' ')
		i++;
	length = ft_len(line) - i;
	texture = ft_substrr(line, i, length);
	if (mys->map != NULL)
		return (error_text(mys, "Error in order of .cub file", 0));
	if ((ft_texture_correct(line, mys, texture)) == -1)
		return (-1);
	return (1);
}

int		sprite_path(char *line, t_sto *mys)
{
	int		length;
	char	*texture;
	int		i;

	i = 2;
	while (line[i] == ' ')
		i++;
	length = ft_len(line) - i;
	texture = ft_substrr(line, i, length);
	if (mys->map != NULL || mys->s != NULL)
		return (error_text(mys, "Error in order of .cub file", 0));
	mys->s = texture;
	return (1);
}

void	ft_putstr(char *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}
