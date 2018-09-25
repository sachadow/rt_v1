/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives_intersection2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:53:04 by sderet            #+#    #+#             */
/*   Updated: 2018/09/25 19:10:02 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/rtv1.h"

double		disk_c(t_primitiv disk, t_dpos3d ang, double a, t_dpos3d origin)
{
	t_dpos3d    relative;
	t_dpos3d	intersec;
	double		dist;

	a = FLT_MIN;
	ang = normalize(ang);
	disk.normale = normalize(disk.normale);
	a = scalar_product(disk.normale, ang);
	if (a >= -FLT_MIN && a <= FLT_MIN)
		return (-1);
	relative = soustraction_v(disk.origin, origin);
	a = scalar_product(relative, disk.normale) / a;
	if (a < 0)
		return (-1);
	intersec = addition_v(origin, multiplication_v(ang, a));
	intersec = soustraction_v(intersec, disk.origin);
	dist = scalar_product(intersec, intersec);
	if ((double)sqrt(dist) >= (double)disk.rayon)
		return (-1);
	else
		return (a);
}
