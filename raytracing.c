/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:53:41 by sderet            #+#    #+#             */
/*   Updated: 2018/03/20 18:57:25 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

t_posd	horiz_intersec(t_char ray, t_map map)
{
	t_posd	a;
	t_posd	b;
	t_posd	c;
	t_pos	d;

	if (ray.direction < 180)
		a.y = (int)(ray.pos.y / BLOC_SIZE) * BLOC_SIZE - 1;
	else
		a.y = (int)(ray.pos.y / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
	a.x = ray.pos.x + (ray.pos.y - a.y) / (tan(RAD(ray.direction)));
	b.y = (ray.direction > 180 ? BLOC_SIZE : -BLOC_SIZE);
	b.x = (-b.y) / (tan(RAD(ray.direction)));
	c.x = a.x;
	c.y = a.y;
	d.x = c.x / BLOC_SIZE;
	d.y = c.y / BLOC_SIZE;
	while (check_wall(d, map) == 0 && d.x >= 0 && d.y >= 0 && d.x < map.len &&
			d.y < map.hgt)
	{
		c.x += b.x;
		c.y += b.y;
		d.x = c.x / BLOC_SIZE;
		d.y = c.y / BLOC_SIZE;
	}
	return (c);
}

t_posd	vertic_intersec(t_char ray, t_map map)
{
	t_posd	a;
	t_posd	b;
	t_posd	c;
	t_pos	d;

	a.x = (int)(ray.pos.x / BLOC_SIZE) * BLOC_SIZE + (ray.direction > 90 &&
			ray.direction < 270 ? -1 : BLOC_SIZE);
	a.y = ray.pos.y + (ray.pos.x - a.x) * (tan(RAD(ray.direction)));
	b.x = (ray.direction < 270 && ray.direction > 90 ?
			-BLOC_SIZE : BLOC_SIZE);
	b.y = (-b.x) * (tan(RAD(ray.direction)));
	c.x = a.x;
	c.y = a.y;
	d.x = c.x / BLOC_SIZE;
	d.y = c.y / BLOC_SIZE;
	while (check_wall(d, map) == 0 && d.x >= 0 && d.y >= 0 && d.x < map.len &&
			d.y < map.hgt)
	{
		c.x += b.x;
		c.y += b.y;
		d.x = c.x / BLOC_SIZE;
		d.y = c.y / BLOC_SIZE;
	}
	return (c);
}

int		dist(t_char ray, t_posd c, t_posd d, int *cot)
{
	double a;
	double b;

	a = sqrt(pow(ray.pos.x - c.x, 2) + pow(ray.pos.y - c.y, 2));
	b = sqrt(pow(ray.pos.x - d.x, 2) + pow(ray.pos.y - d.y, 2));
	if (ABS(a) < ABS(b))
	{
		*cot = 0;
		return (ABS(a));
	}
	else
	{
		*cot = 1;
		return (ABS(b));
	}
}

void	print_slice(t_image *img, int a, int slice, t_dposd cot)
{
	int		b;
	int		c;
	int		end;
	t_pos	pos;

	b = 0;
	if (slice >= 0)
		b = (slice < WINDOW_Y ? (WINDOW_Y - slice) / 2 : 0);
	else
		slice = 0;
	end = (slice > WINDOW_Y ? slice - ((slice - WINDOW_Y) / 2) : slice);
	c = (slice > WINDOW_Y ? (slice - WINDOW_Y) / 2 : 0);
	while (c < end)
	{
		pos.x = a;
		pos.y = b;
		if (a >= 0 && b >= 0)
			print_pixelc(img, &pos, &cot, slice);
		c++;
		b++;
	}
}

void	raycast(t_char player, t_map map, t_image *img)
{
	double	pas;
	int		a;
	double	distance;
	t_dposd	c;
	t_char	ray;

	clean_map(img);
	ray = player;
	img->ang = player.direction - (FOV / 2);
	img->ang += (img->ang < 0 ? 360 : 0);
	pas = (double)FOV / (double)WINDOW_X;
	a = 0;
	while (a < WINDOW_X)
	{
		ray.direction = img->ang;
		c.c = vertic_intersec(ray, map);
		c.d = horiz_intersec(ray, map);
		distance = dist(ray, c.c, c.d, &(c.cot)) * cos(RAD(player.direction -
					img->ang));
		map.slice = ((double)BLOC_SIZE / (double)distance) * map.distance;
		print_slice(img, a, map.slice, c);
		a++;
		img->ang += pas;
		img->ang -= (img->ang > 360 ? 360 : 0);
	}
}
