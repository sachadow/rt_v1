/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_fun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 16:25:15 by sderet            #+#    #+#             */
/*   Updated: 2018/06/28 20:41:18 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		scalar_product(t_dpos3d a, t_dpos3d b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_dpos3d	copy_v(t_dpos3d pos)
{
	return (pos);
}

t_dpos3d	addition_v(t_dpos3d pos1, t_dpos3d pos2)
{
	pos1.x += pos2.x;
	pos1.y += pos2.y;
	pos1.z += pos2.z;
	return (pos1);
}

t_dpos3d	soustraction_v(t_dpos3d pos1, t_dpos3d pos2)
{
	pos1.x -= pos2.x;
	pos1.y -= pos2.y;
	pos1.z -= pos2.z;
	return (pos1);
}

t_dpos3d	multiplication_v(t_dpos3d pos1, double a)
{
	pos1.x *= a;
	pos1.y *= a;
	pos1.z *= a;
	return (pos1);
}
