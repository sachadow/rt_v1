/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:11:13 by sderet            #+#    #+#             */
/*   Updated: 2018/06/20 19:26:49 by sderet           ###   ########.fr       */
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
/*
void	pre_ppc(int *colo, t_image *img, t_dposd *c, int slice)
{
	int a;
	int res;
	int y_start;

	y_start = (WINDOW_Y - slice) / 2;
	a = -1;
	while (++a < 3)
	{
		if (c->cot == 1)
			res = (int)((((int)(((double)((int)c->d.x %
				BLOC_SIZE) / BLOC_SIZE) * img->spritesizex) * 4) + a) +
				((int)(((double)((int)img->pos->y - y_start) /
				slice) * img->spritesizey) * img->trash));
		if (c->cot == 0)
			res = (int)((((int)(((double)((int)c->c.y %
				BLOC_SIZE) / BLOC_SIZE) * img->spritesizex) * 4) + a) +
				((int)(((double)((int)img->pos->y - y_start) /
				slice) * img->spritesizey) * img->trash));
		if (c->cot == 1)
			colo[a] = (int)((img->ang < 180 ? img->sp1 : img->sp2)[res]);
		else if (c->cot == 0)
			colo[a] = (int)((img->ang < 270 && img->ang > 90 ? img->sp3 :
						img->sp4)[res]);
	}
}

void	print_pixelc(t_image *img, t_pos *pos, t_dposd *c, int slice)
{
	int colo[3];
	int a;

	a = -1;
	while (++a < 3)
		colo[a] = 0;
	if (c != 0)
	{
		img->pos = pos;
		pre_ppc(colo, img, c, slice);
		a = -1;
		if (((ABS((int)c->d.x) % BLOC_SIZE >= BLOC_SIZE - (BLOC_SIZE / 25)
				|| ABS((int)c->d.x) % BLOC_SIZE <= (BLOC_SIZE / 25)) &&
				c->cot == 1) || ((ABS((int)c->c.y) % BLOC_SIZE >= BLOC_SIZE
				- (BLOC_SIZE / 25) || ABS((int)c->c.y) % BLOC_SIZE <=
				(BLOC_SIZE / 25)) && c->cot == 0))
			while (++a < 3)
				colo[a] = 255;
	}
	if (pos->x >= 0 && pos->x < WINDOW_X && pos->y >= 0 && pos->y < WINDOW_Y)
		print_pixel(img, pos, colo);
}
*/
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
