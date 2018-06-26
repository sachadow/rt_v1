/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:18:55 by sderet            #+#    #+#             */
/*   Updated: 2018/06/26 20:00:15 by sderet           ###   ########.fr       */
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
	t_dpos3d	normalized_ang;
	double		b;
	double		c;
	t_dpos3d	relative;

	normalized_ang = normalize(ang);
	relative.x = -origin.x + sphere.origin.x;
	relative.y = -origin.y + sphere.origin.y;
	relative.z = -origin.z + sphere.origin.z;
	a = scalar_product(relative, normalized_ang);
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
	t_dpos3d	normalized_ang;

	a = FLT_MIN;
	normalized_ang = normalize(ang);
	plan.normale = normalize(plan.normale);
	a = scalar_product(plan.normale, normalized_ang);
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
	double		d;
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
	d = (abc.y * abc.y) - ( 4 * abc.x * abc.z);
	res.x = (-abc.y + sqrt(d)) / (2 * abc.x);
	res.y = (-abc.y - sqrt(d)) / (2 * abc.x);
	return (res.x > 0 && res.x < res.y ? res.x : res.y);
}

void		raytracing(t_camera cam, t_big *big)
{
	t_pos		screen;
	t_dpos3d	ang;
	t_dpos3d	normalized_ang;
	double		a;
	double		b;
	double		c;
	int			d;
	int			count;
	int			second_count;
	t_primitiv	light;

	light.origin.x = 30;
	light.origin.z = -20;
	light.origin.y = 10;
	ang = soustraction_v(cam.upleft, cam.origin);
	cam.pas.second_p = multiplication_v(cam.vec_vertic, ((double)FOVX / (double)WINDOW_X));
	cam.pas.first_p.x = cam.vec_horiz.x * ((double)FOVX / (double)WINDOW_X);
	cam.pas.first_p.z = cam.vec_horiz.z * ((double)FOVX / (double)WINDOW_X);
	screen.x = 0;
	while (screen.x < WINDOW_X)
	{
		screen.y = 0;
		ang.y = cam.upleft.y - cam.origin.y;
		ang.x = cam.upleft.x - cam.origin.x + (cam.pas.first_p.x * screen.x);
		ang.z = cam.upleft.z - cam.origin.z + (cam.pas.first_p.z * screen.x);
		while (screen.y < WINDOW_Y)
		{
			count = 0;
			d = 0;
			if (big->objects[0].type)
				b = big->intersec[big->objects[count].type - 1](big->objects[count], ang, 0, cam.origin);
			while (big->objects[count].type)
			{
				c = big->intersec[big->objects[count].type - 1](big->objects[count], ang, 0, cam.origin);
				if ((c >= 0 && c < b) || b < 0)
				{
					b = c;
					d = count;
				}
				count++;
			}
			normalized_ang = normalize(ang);
			if (b >= 0)
			{
				if (big->objects[d].type == 3)
					d += 0;
				cam.intersection = addition_v(cam.origin, multiplication_v(normalized_ang, b));
				light.normale = soustraction_v(light.origin, cam.intersection);
				if (big->objects[d].type == 1)
					cam.intersection_d = soustraction_v(cam.intersection,
							big->objects[d].origin);
				else if (big->objects[d].type == 2)
					cam.intersection_d = (scalar_product(ang,
							big->objects[d].normale) < 0 ?
							big->objects[d].normale : soustraction_v((t_dpos3d){0, 0, 0}, big->objects[d].normale));
				else if (big->objects[d].type == 3)
				{
					big->objects[d].normale = normalize(big->objects[d].normale);
					b = (scalar_product(normalized_ang, big->objects[d].normale)
						* b) + scalar_product(soustraction_v(cam.origin,
						big->objects[d].origin), big->objects[d].normale);
					cam.intersection_d = soustraction_v(cam.intersection,
						addition_v(big->objects[d].origin,
						multiplication_v(normalize(big->objects[d].normale),
						b)));
				}
				light.normale = normalize(light.normale);
				cam.intersection_d = normalize(cam.intersection_d);
				if (big->objects[d].type != 0)
					b = scalar_product(light.normale, cam.intersection_d) * 0.8;
				if (b < 0)
					b = 0;
				count = 0;
				c = big->intersec[1](light,
					light.normale, 0, cam.intersection);
				while (big->objects[count].type)
				{
					if (count != d)
					{
						a = big->intersec[big->objects[count].type - 1](big->objects[count],
								light.normale, 0, cam.intersection);
						if (a >= 0 && a < c)
							b = 0;
					}
					count++;
				}
				cam.point_colo[0] = big->objects[d].color.b * (0.2 + b);
				cam.point_colo[1] = big->objects[d].color.g * (0.2 + b);
				cam.point_colo[2] = big->objects[d].color.r * (0.2 + b);
				print_pixel(&(big->img), &screen, cam.point_colo);
			}
			screen.y++;
			ang = soustraction_v(ang, cam.pas.second_p);
		}
		screen.x++;
	}
}

t_camera	init_cam(t_camera cam)
{
	cam.upleft.x = cam.origin.x + ((cam.vecdir.x * cam.distance) +
			(cam.vec_vertic.x * (FOVY / 2))) - (cam.vec_horiz.x * (FOVX / 2));
	cam.upleft.y = cam.origin.y + ((cam.vecdir.y * cam.distance) +
			(cam.vec_vertic.y * (FOVY / 2))) - (cam.vec_horiz.y * (FOVX / 2));
	cam.upleft.z = cam.origin.z + ((cam.vecdir.z * cam.distance) +
			(cam.vec_vertic.z * (FOVY / 2))) - (cam.vec_horiz.z * (FOVX / 2));
	return (cam);
}

int     quit_button(t_big *big)
{
	free(big->objects);
	exit(EXIT_SUCCESS);
	return (0);
}

int			main()
{
	t_big		big;
	t_camera	*cam;

	cam = &(big.camera);
	big.objects = (t_primitiv*)malloc(sizeof(t_primitiv) * 7);
	big.objects[0].type = 1;
	big.objects[0].origin.x = 100;
	big.objects[0].origin.y = 0;
	big.objects[0].origin.z = 0;
	big.objects[0].rayon = 30;
	big.objects[0].color.r = 255;
	big.objects[0].color.g = 123;
	big.objects[0].color.b = 68;
	big.objects[1].type = 1;
	big.objects[1].origin.x = 85;
	big.objects[1].origin.y = 20;
	big.objects[1].origin.z = 0;
	big.objects[1].rayon = 20;
	big.objects[1].color.r = 123;
	big.objects[1].color.g = 255;
	big.objects[1].color.b = 68;
	big.objects[2].type = 2;
	big.objects[2].origin.x = 200;
	big.objects[2].origin.y = 0;
	big.objects[2].origin.z = 0;
	big.objects[2].normale.x = 10;
	big.objects[2].normale.y = 0;
	big.objects[2].normale.z = 0;
	big.objects[2].color.r = 255;
	big.objects[2].color.g = 255;
	big.objects[2].color.b = 123;
	big.objects[3].type = 2;
	big.objects[3].origin.x = 0;
	big.objects[3].origin.y = -10;
	big.objects[3].origin.z = 0;
	big.objects[3].normale.x = 0;
	big.objects[3].normale.y = 20;
	big.objects[3].normale.z = 0;
	big.objects[3].color.r = 123;
	big.objects[3].color.g = 68;
	big.objects[3].color.b = 255;
	big.objects[4].type = 2;
	big.objects[4].origin.x = 0;
	big.objects[4].origin.y = 0;
	big.objects[4].origin.z = 50;
	big.objects[4].normale.x = 0;
	big.objects[4].normale.y = 0;
	big.objects[4].normale.z = 10;
	big.objects[4].color.r = 255;
	big.objects[4].color.g = 255;
	big.objects[4].color.b = 255;
	big.objects[5].type = 3;
	big.objects[5].origin.x = 87;
	big.objects[5].origin.y = 0;
	big.objects[5].origin.z = -30;
	big.objects[5].rayon = 10;
	big.objects[5].normale.x = -2;
	big.objects[5].normale.y = 10;
	big.objects[5].normale.z = -2;
	big.objects[5].color.r = 255;
	big.objects[5].color.g = 0;
	big.objects[5].color.b = 255;
	big.objects[6].type = 0;
	big.camera.origin.x = -150;
	big.camera.origin.y = 10;
	big.camera.origin.z = 0;
	big.camera.direction.x = 5;
	big.camera.direction.y = 0;
	big.camera.direction.z = 0;
	big.camera.distance = 40;
	big.intersec[0] = &sphere_c;
	big.intersec[1] = &plan_c;
	big.intersec[2] = &cyl_c;
	big.camera.vec_horiz.x = -big.camera.direction.z;
	big.camera.vec_horiz.y = 0;
	big.camera.vec_horiz.z = big.camera.direction.x;
	if (big.camera.vec_horiz.x == 0 && big.camera.vec_horiz.z == 0)
		big.camera.vec_horiz.z = 1;
	big.camera.vec_vertic.x = -((cam->direction.y * cam->vec_horiz.z) -
		(cam->direction.z * cam->vec_horiz.y));
	big.camera.vec_vertic.y = -((cam->direction.z * cam->vec_horiz.x) -
		(cam->direction.x * cam->vec_horiz.z));
	big.camera.vec_vertic.z = -((cam->direction.x * cam->vec_horiz.y) -
		(cam->direction.y * cam->vec_horiz.x));
	big.camera.vecdir = normalize(big.camera.direction);
	big.camera.vec_horiz = normalize(big.camera.vec_horiz);
	big.camera.vec_vertic = normalize(big.camera.vec_vertic);
	big.camera = init_cam(big.camera);
	big.mlx.mlx = mlx_init();
	window_creation(&(big.img), &(big.mlx), &big);
	raytracing(big.camera, &big);
	mlx_put_image_to_window(big.mlx.mlx, big.mlx.win, big.mlx.image, 0, 0);
	mlx_hook(big.mlx.win, 17, 0, quit_button, &big);
	mlx_loop(big.mlx.mlx);
	return (0);
}
