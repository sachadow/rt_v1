/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:18:55 by sderet            #+#    #+#             */
/*   Updated: 2018/06/18 16:52:20 by sderet           ###   ########.fr       */
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

void		raytracing(t_camera cam, t_big *big)
{
	t_dpos3d	boule_pos;
	double		boule_rayon;
	t_pos		screen;
	t_dpos3d	pas;
	t_dpos3d	ang;
	t_dpos3d	relative;
	double		a;
	double		b;
	double		c;

	boule_pos.x = 0;
	boule_pos.y = 0;
	boule_pos.z = 0;
	boule_rayon = 20;
	relative.x = ABS(cam.origin.x - boule_pos.x);
	relative.y = ABS(cam.origin.y - boule_pos.y);
	relative.z = ABS(cam.origin.z - boule_pos.z);
	ang.x = cam.upleft.x;
	ang.y = cam.upleft.y;
	ang.z = cam.upleft.z;
	pas.x = cam.vec_horizon.x * ((double)FOVX / (double)WINDOW_X);
	pas.y = cam.vec_vertic.y * ((double)FOVY / (double)WINDOW_Y);
	pas.z = cam.vec_horizon.z * ((double)FOVX / (double)WINDOW_X);
	screen.x = 0;
	while (screen.x < WINDOW_X)
	{
		screen.y = 0;
		ang.y = cam.upleft.y;
		while (screen.y < WINDOW_Y)
		{
			b = 2 * (ang.x * (cam.origin.x - boule_pos.x) +
							ang.y * (cam.origin.y - boule_pos.y) +
							ang.z * (cam.origin.z -
							boule_pos.z));
			a = scalar_product(ang, ang);
			c = ((pow(cam.origin.x - boule_pos.x, (double)2) +
							pow(cam.origin.y - boule_pos.y,(double)2) +
							pow(cam.origin.z - boule_pos.z, (double)2))
							- pow(boule_rayon, (double)2));
			a = pow(b, (double)2) - (4 * a * c);
			if (a >= 0)
				ft_putchar('0');
			else
				ft_putchar(' ');
			screen.y++;
			ang.y -= pas.y;
		}
		ft_putchar('\n');
		screen.x++;
		ang.x += pas.x * cam.vec_horizon.x;
		ang.z += pas.z * cam.vec_horizon.z;
	}
}

t_camera	init_cam(t_camera cam)
{
	cam.upleft.x = cam.origin.x + ((cam.vecdir.x * cam.distance) +
			(cam.vec_vertic.x * (FOVY / 2))) - (cam.vec_horizon.x * (FOVX / 2));
	cam.upleft.y = cam.origin.y + ((cam.vecdir.y * cam.distance) +
			(cam.vec_vertic.y * (FOVY / 2))) - (cam.vec_horizon.y * (FOVX / 2));
	cam.upleft.z = cam.origin.z + ((cam.vecdir.z * cam.distance) +
			(cam.vec_vertic.z * (FOVY / 2))) - (cam.vec_horizon.z * (FOVX / 2));
	return (cam);
}

int			main()
{
	t_big big;

	big.camera.origin.x = 50;
	big.camera.origin.y = 0;
	big.camera.origin.z = 0;
	big.camera.direction.x = -1;
	big.camera.direction.y = 0;
	big.camera.direction.z = 0;
	big.camera.distance = (WINDOW_X / 2) / (tan(RAD(FOVX / 2)));
	big.camera.vec_horizon.x = -big.camera.direction.z;
	big.camera.vec_horizon.y = 0;
	big.camera.vec_horizon.z = -big.camera.direction.x;
	big.camera.vec_vertic.y = big.camera.direction.y;
	big.camera.vec_vertic.y += (big.camera.direction.y == 0 ? 1 : 0);
	big.camera.vec_vertic.x = 0;
	big.camera.vec_vertic.z = 0;
	big.camera.vecdir = normalize(big.camera.direction);
	big.camera.vec_horizon = normalize(big.camera.vec_horizon);
	big.camera.vec_vertic = normalize(big.camera.vec_vertic);
	big.camera = init_cam(big.camera);
//	big.mlx.mlx = mlx_init();
//	window_creation(&(big.img), &(big.mlx), &big);
	raytracing(big.camera, &big);
//	mlx_put_image_to_window(big.mlx.mlx, big.mlx.win, big.mlx.image, 0, 0);
	return (0);
}
