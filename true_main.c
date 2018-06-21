/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:18:55 by sderet            #+#    #+#             */
/*   Updated: 2018/06/21 19:12:26 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"
#include "libft/libft.h"
#include <stdlib.h>

double		scalar_product(t_dpos3d a, t_dpos3d b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
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

double		sphere_coup(t_primitiv sphere, t_dpos3d ang, double a, t_dpos3d origin)
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
	t_ray		light;

	light.origin.x = 30;
	light.origin.z = -20;
	light.origin.y = 20;
	ang.x = cam.upleft.x - cam.origin.x;
	ang.y = cam.upleft.y - cam.origin.y;
	ang.z = cam.upleft.z - cam.origin.z;
	cam.pas.second_p.x = cam.vec_vertic.x * ((double)FOVX / (double)WINDOW_X);
	cam.pas.second_p.y = (cam.vec_vertic.y)
		* ((double)FOVY / (double)WINDOW_Y);
	cam.pas.second_p.z = cam.vec_vertic.z * ((double)FOVX / (double)WINDOW_X);
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
			b = sphere_coup(big->objects[count], ang, 0, cam.origin);
			while (big->objects[count].type)
			{
				c = sphere_coup(big->objects[count], ang, 0, cam.origin);
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
				cam.intersection.x = cam.origin.x + (b) * normalized_ang.x;
				cam.intersection.y = cam.origin.y + (b) * normalized_ang.y;
				cam.intersection.z = cam.origin.z + (b) * normalized_ang.z;
				light.direction.x = light.origin.x - cam.intersection.x;
				light.direction.y = light.origin.y - cam.intersection.y;
				light.direction.z = light.origin.z - cam.intersection.z;
				cam.intersection_d.x = cam.intersection.x - big->objects[d].origin.x;
				cam.intersection_d.y = cam.intersection.y - big->objects[d].origin.y;
				cam.intersection_d.z = cam.intersection.z - big->objects[d].origin.z;
				light.direction = normalize(light.direction);
				cam.intersection_d = normalize(cam.intersection_d);
				b = scalar_product(light.direction, cam.intersection_d) * 0.8;
				if (b < 0)
					b = 0;
				count = 0;
				while (big->objects[count].type)
				{
					if (count != d)
					{
						a = sphere_coup(big->objects[count],
								light.direction, 0, cam.intersection);
						if (a >= 0)
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
			ang.x -= cam.pas.second_p.x;
			ang.y -= cam.pas.second_p.y;
			ang.z -= cam.pas.second_p.z;
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
	big += 0;
	exit(EXIT_SUCCESS);
	return (0);
}

int			main()
{
	t_big		big;
	t_camera	*cam;

	cam = &(big.camera);
	big.objects = (t_primitiv*)malloc(sizeof(t_primitiv) * 3);
	big.objects[0].type = "sphere";
	big.objects[0].origin.x = 100;
	big.objects[0].origin.y = 0;
	big.objects[0].origin.z = 0;
	big.objects[0].rayon = 30;
	big.objects[0].color.r = 255;
	big.objects[0].color.g = 123;
	big.objects[0].color.b = 68;
	big.objects[1].type = "sphere";
	big.objects[1].origin.x = 80;
	big.objects[1].origin.y = 20;
	big.objects[1].origin.z = 0;
	big.objects[1].rayon = 20;
	big.objects[1].color.r = 123;
	big.objects[1].color.g = 255;
	big.objects[1].color.b = 68;
	big.objects[2].type = 0;
	big.camera.origin.x = 0;
	big.camera.origin.y = 0;
	big.camera.origin.z = 0;
	big.camera.direction.x = 5;
	big.camera.direction.y = 0;
	big.camera.direction.z = 0;
	big.camera.distance = 40;
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
