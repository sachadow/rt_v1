/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 16:25:49 by sderet            #+#    #+#             */
/*   Updated: 2018/06/28 20:42:56 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/rtv1.h"

t_dpos3d	normalize(t_dpos3d pos)
{
	double		norme;
	t_dpos3d	res;

	norme = sqrt((pos.x * pos.x) + (pos.y * pos.y) + (pos.z * pos.z));
	res.x = pos.x / norme;
	res.y = pos.y / norme;
	res.z = pos.z / norme;
	return (res);
}

double		sphere_c(t_primitiv sphere, t_dpos3d ang, double a, t_dpos3d origin)
{
	double		b;
	double		c;
	t_dpos3d	relative;

	ang = normalize(ang);
	relative.x = -origin.x + sphere.origin.x;
	relative.y = -origin.y + sphere.origin.y;
	relative.z = -origin.z + sphere.origin.z;
	a = scalar_product(relative, ang);
	b = pow(sphere.rayon, (double)2) -
		(scalar_product(relative, relative) - pow(a, (double)2));
	if (b < 0)
		return (-1);
	c = sqrt(b);
	return (a - c);
}

double		plan_c(t_primitiv plan, t_dpos3d ang, double a, t_dpos3d origin)
{
	t_dpos3d	relative;

	a = FLT_MIN;
	ang = normalize(ang);
	plan.normale = normalize(plan.normale);
	a = scalar_product(plan.normale, ang);
	if (a >= -FLT_MIN && a <= FLT_MIN)
		return (-1);
	relative = soustraction_v(plan.origin, origin);
	a = scalar_product(relative, plan.normale) / a;
	if (a < 0)
		return (-1);
	return (a);
}

double		cyl_c(t_primitiv cyl, t_dpos3d ang, double a, t_dpos3d origin)
{
	t_dpos3d	abc;
	t_dpos		res;
	t_dpos3d	relative;

	relative = soustraction_v(origin, cyl.origin);
	ang = normalize(ang);
	cyl.normale = normalize(cyl.normale);
	abc.x = scalar_product(ang, ang) - pow(scalar_product(ang, cyl.normale),
			(double)2);
	abc.z = scalar_product(relative, relative) - pow(scalar_product(relative,
					cyl.normale), (double)2) - (cyl.rayon * cyl.rayon);
	abc.y = 2 * (scalar_product(ang, relative) - ((scalar_product(ang,
					cyl.normale) * scalar_product(relative, cyl.normale))));
	a = (abc.y * abc.y) - (4 * abc.x * abc.z);
	if (a < 0)
		return (-1);
	res.x = (-abc.y + sqrt(a)) / (2 * abc.x);
	res.y = (-abc.y - sqrt(a)) / (2 * abc.x);
	return (res.x > 0 && res.x < res.y ? res.x : res.y);
}

double		cone_c(t_primitiv cone, t_dpos3d ang, double a, t_dpos3d origin)
{
	t_dpos3d	abc;
	t_dpos3d	relative;
	t_dpos		res;

	ang = normalize(ang);
	cone.normale = normalize(cone.normale);
	relative = soustraction_v(origin, cone.origin);
	abc.x = scalar_product(ang, ang) - (1 + (cone.tangent * cone.tangent)) *
		pow(scalar_product(ang, cone.normale), (double)2);
	abc.y = 2 * (scalar_product(ang, relative) - (1 + pow(cone.tangent, 2)) *
		scalar_product(ang, cone.normale) *
		scalar_product(relative, cone.normale));
	abc.z = scalar_product(relative, relative) - (1 + pow(cone.tangent, 2)) *
		pow(scalar_product(relative, cone.normale), (double)2);
	a = (abc.y * abc.y) - (4 * abc.x * abc.z);
	if (a < 0)
		return (-1);
	res.x = (-abc.y + sqrt(a)) / (2 * abc.x);
	res.y = (-abc.y - sqrt(a)) / (2 * abc.x);
	return (res.x > 0 && res.x < res.y ? res.x : res.y);
}
