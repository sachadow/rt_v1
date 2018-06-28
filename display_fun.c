/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:11:13 by sderet            #+#    #+#             */
/*   Updated: 2018/06/28 16:17:03 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdlib.h>

void	print_pixel(t_image *img, t_pos *pos, int *colo)
{
	int		a;

	a = 0;
	if (colo != 0)
	{
		while (a < 3)
		{
			img->map[(((int)pos->x * 4) + a) +
				((int)pos->y * img->line_len)] = (char)colo[a];
			a++;
		}
		img->map[(((int)pos->x * 4) + a) +
			((int)pos->y * img->line_len)] = (char)0;
		return ;
	}
	while (a < 3)
	{
		img->map[(((int)pos->x * 4) + a) +
			((int)pos->y * img->line_len)] = (char)250;
		a++;
	}
	img->map[(((int)pos->x * 4) + a) +
		((int)pos->y * img->line_len)] = (char)0;
}

int		std_err(int err, t_map *map)
{
	int a;

	if (map != NULL && map->map != NULL)
	{
		a = -1;
		while (map->map[++a] != 0)
			free(map->map[a]);
		free(map->map);
	}
	if (err == 1)
		ft_putendl("usage :	./rtv1");
	if (err == 2)
	{
		ft_putstr("Error : source file format may be incorrect or ");
		ft_putendl("file doesn't exist.");
	}
	return (1);
}
