/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:18:55 by sderet            #+#    #+#             */
/*   Updated: 2018/06/28 19:13:17 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
#include "rtv1.h"
#include "libft/libft.h"
#include <stdlib.h>

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

void		raytracing(t_camera cam, t_big *big)
{
	t_pos		screen;
	t_dpos3d	ang;

	ang = soustraction_v(cam.upleft, cam.origin);
	cam.pas.second_p = multiplication_v(cam.vec_vertic,
		((double)FOVX / (double)WINDOW_X));
	cam.pas.first_p.x = cam.vec_horiz.x * ((double)FOVX / (double)WINDOW_X);
	cam.pas.first_p.z = cam.vec_horiz.z * ((double)FOVX / (double)WINDOW_X);
	screen.x = -1;
	while (++screen.x < WINDOW_X)
	{
		screen.y = -1;
		ang.y = cam.upleft.y - cam.origin.y;
		ang.x = cam.upleft.x - cam.origin.x + (cam.pas.first_p.x * screen.x);
		ang.z = cam.upleft.z - cam.origin.z + (cam.pas.first_p.z * screen.x);
		while (++screen.y < WINDOW_Y)
		{
			cam.point_colo[0] = 0;
			cam.point_colo[1] = 0;
			cam.point_colo[2] = 0;
			cam = sending_rays(big, cam, ang);
			print_pixel(&(big->img), &screen, cam.point_colo);
			ang = soustraction_v(ang, cam.pas.second_p);
		}
	}
}

t_camera	init_cam(t_camera cam)
{
	cam.vec_horiz.x = -cam.direction.z;
	cam.vec_horiz.y = 0;
	cam.vec_horiz.z = cam.direction.x;
	if (cam.vec_horiz.x == 0 && cam.vec_horiz.z == 0)
		cam.vec_horiz.z = 1;
	cam.vec_vertic.x = -((cam.direction.y * cam.vec_horiz.z) -
		(cam.direction.z * cam.vec_horiz.y));
	cam.vec_vertic.y = -((cam.direction.z * cam.vec_horiz.x) -
		(cam.direction.x * cam.vec_horiz.z));
	cam.vec_vertic.z = -((cam.direction.x * cam.vec_horiz.y) -
		(cam.direction.y * cam.vec_horiz.x));
	cam.vecdir = normalize(cam.direction);
	cam.vec_horiz = normalize(cam.vec_horiz);
	cam.vec_vertic = normalize(cam.vec_vertic);
	cam.upleft.x = cam.origin.x + ((cam.vecdir.x * cam.distance) +
			(cam.vec_vertic.x * (FOVY / 2))) - (cam.vec_horiz.x * (FOVX / 2));
	cam.upleft.y = cam.origin.y + ((cam.vecdir.y * cam.distance) +
			(cam.vec_vertic.y * (FOVY / 2))) - (cam.vec_horiz.y * (FOVX / 2));
	cam.upleft.z = cam.origin.z + ((cam.vecdir.z * cam.distance) +
			(cam.vec_vertic.z * (FOVY / 2))) - (cam.vec_horiz.z * (FOVX / 2));
	return (cam);
}

int			quit_button(t_big *big)
{
	free(big->objects);
	exit(EXIT_SUCCESS);
	return (0);
}

int			main(void)
{
	t_big		big;

	big.camera.distance = 0;
	ft_get_conf(&big);
	if (big.camera.direction.x == 0 && big.camera.direction.y == 0 &&
			big.camera.direction.z == 0)
		exit(0);
	big.camera.distance = 40;
	big.intersec[0] = &sphere_c;
	big.intersec[1] = &plan_c;
	big.intersec[2] = &cyl_c;
	big.intersec[3] = &cone_c;
	big.camera = init_cam(big.camera);
	big.mlx.mlx = mlx_init();
	window_creation(&(big.img), &(big.mlx), &big);
	raytracing(big.camera, &big);
	mlx_put_image_to_window(big.mlx.mlx, big.mlx.win, big.mlx.image, 0, 0);
	mlx_hook(big.mlx.win, 17, 0, quit_button, &big);
	mlx_loop(big.mlx.mlx);
	return (0);
}
