/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_general.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 16:26:30 by sderet            #+#    #+#             */
/*   Updated: 2018/06/28 20:46:13 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		test_inter(t_big *big, double *b, t_camera cam, t_dpos3d ang)
{
	double	d;
	double	c;
	int		count;

	count = 0;
	d = 0;
	*b = 0;
	if (big->objects[0].type)
		*b = big->intersec[big->objects[count].type -
			1](big->objects[count], ang, 0, cam.origin);
	while (big->objects[count].type)
	{
		c = big->intersec[big->objects[count].type -
			1](big->objects[count], ang, 0, cam.origin);
		if ((c >= 0 && c < *b) || *b < 0)
		{
			*b = c;
			d = count;
		}
		count++;
	}
	return (d);
}

double		light_intersections(t_big *big, int d, t_camera cam, double b)
{
	int		count;
	double	c;
	double	a;

	count = 0;
	c = big->intersec[1](big->light,
		big->light.normale, 0, cam.intersection);
	while (big->objects[count].type)
	{
		if (count != d)
		{
			a = big->intersec[big->objects[count].type - 1](big->objects[count],
				big->light.normale, 0, cam.intersection);
			if (a >= 0 && a < c)
				b = 0;
		}
		count++;
	}
	return (b);
}

t_dpos3d	normale_cylcone(t_camera cam, t_big *big, double b, int d)
{
	big->objects[d].normale = normalize(big->objects[d].normale);
	b = (scalar_product(cam.ang, big->objects[d].normale)
		* b) + scalar_product(soustraction_v(cam.origin,
		big->objects[d].origin), big->objects[d].normale);
	if (big->objects[d].type == 3)
	{
		cam.intersection_d = soustraction_v(cam.intersection,
			addition_v(big->objects[d].origin,
			multiplication_v(normalize(big->objects[d].normale),
			b)));
	}
	else if (big->objects[d].type == 4)
	{
		cam.intersection_d = soustraction_v(cam.intersection,
			addition_v(big->objects[d].origin,
			multiplication_v(big->objects[d].normale, (1 +
			pow(big->objects[d].tangent, 2)) * b)));
	}
	return (cam.intersection_d);
}

t_dpos3d	normale_calc(t_camera cam, t_big *big, double b, int d)
{
	if (big->objects[d].type == 1)
		cam.intersection_d = soustraction_v(cam.intersection,
			big->objects[d].origin);
	else if (big->objects[d].type == 2)
		cam.intersection_d = (scalar_product(cam.ang,
			big->objects[d].normale) < 0 ?
			big->objects[d].normale : soustraction_v((t_dpos3d){0, 0, 0},
			big->objects[d].normale));
	else if (big->objects[d].type == 3)
	{
		cam.intersection_d = normale_cylcone(cam, big, b, d);
	}
	else if (big->objects[d].type == 4)
	{
		cam.intersection_d = normale_cylcone(cam, big, b, d);
	}
	return (cam.intersection_d);
}

t_camera	sending_rays(t_big *big, t_camera cam, t_dpos3d ang)
{
	double		b;
	int			d;

	ang = normalize(ang);
	d = test_inter(big, &b, cam, ang);
	if (b >= 0)
	{
		cam.intersection = addition_v(cam.origin, multiplication_v(ang, b));
		big->light.normale =
			soustraction_v(big->light.origin, cam.intersection);
		cam.ang = copy_v(ang);
		cam.intersection_d = normale_calc(cam, big, b, d);
		big->light.normale = normalize(big->light.normale);
		cam.intersection_d = normalize(cam.intersection_d);
		if (big->objects[d].type != 0)
			b = scalar_product(big->light.normale, cam.intersection_d) * 0.8;
		if (b < 0)
			b = 0;
		b = light_intersections(big, d, cam, b);
		cam.point_colo[0] = big->objects[d].color.b * (0.2 + b);
		cam.point_colo[1] = big->objects[d].color.g * (0.2 + b);
		cam.point_colo[2] = big->objects[d].color.r * (0.2 + b);
	}
	return (cam);
}
