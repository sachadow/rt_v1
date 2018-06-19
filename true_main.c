/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:18:55 by sderet            #+#    #+#             */
/*   Updated: 2018/06/19 19:45:04 by sderet           ###   ########.fr       */
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
	t_dpos3d	petit_pas;
	t_dpos3d	ang;
	t_dpos3d	normalized_ang;
	t_dpos3d	relative;
	double		a;
	double		b;
	double		c;

	boule_pos.x = 100;
	boule_pos.y = 0;
	boule_pos.z = 0;
	boule_rayon = 20;
	relative.x = -cam.origin.x + boule_pos.x;
	relative.y = -cam.origin.y + boule_pos.y;
	relative.z = -cam.origin.z + boule_pos.z;
	ang.x = cam.upleft.x;
	ang.y = cam.upleft.y;
	ang.z = cam.upleft.z;
	petit_pas.x = cam.vec_vertic.x * ((double)FOVX / (double)WINDOW_X);
	petit_pas.y = cam.vec_vertic.y * ((double)FOVY / (double)WINDOW_Y);
	petit_pas.z = cam.vec_vertic.z * ((double)FOVX / (double)WINDOW_X);
	pas.x = cam.vec_horizon.x * ((double)FOVX / (double)WINDOW_X);
	pas.z = cam.vec_horizon.z * ((double)FOVX / (double)WINDOW_X);
	screen.x = 0;
	ft_putnbr(ang.x);
	ft_putchar(' ');
	ft_putnbr(ang.y);
	ft_putchar(' ');
	ft_putnbr(ang.z);
	ft_putchar('\n');
	while (screen.x < WINDOW_X)
	{
		screen.y = WINDOW_Y - 1;
		ang.y = cam.upleft.y;
		ang.x = cam.upleft.x + (pas.x * screen.x);
		ang.z = cam.upleft.z + (pas.z * screen.x);
		while (screen.y >= 0)
		{
/*
			b = 2 * (ang.x * (cam.origin.x - boule_pos.x) +
							ang.y * (cam.origin.y - boule_pos.y) +
							ang.z * (cam.origin.z - boule_pos.z));
			a = scalar_product(ang, ang);
			c = ((pow(cam.origin.x - boule_pos.x, (double)2) +
							pow(cam.origin.y - boule_pos.y, (double)2) +
							pow(cam.origin.z - boule_pos.z, (double)2)))
							- pow(boule_rayon, (double)2);
			a = pow(b, (double)2) - (4 * a * c);
			if (a >= 0)
				print_pixel(&(big->img), &screen, 0);
*/
			normalized_ang = normalize(ang);
			a = scalar_product(relative, normalized_ang);
			b = pow(boule_rayon, (double)2) - (scalar_product(relative, relative)
						- pow(a, (double)2));
			if (b >= 0)
				print_pixel(&(big->img), &screen, 0);

			screen.y--;
			ang.x -= petit_pas.x;
			ang.y -= petit_pas.y;
			ang.z -= petit_pas.z;
		}
		screen.x++;
	}
	ft_putnbr(ang.x);
	ft_putchar(' ');
	ft_putnbr(ang.y);
	ft_putchar(' ');
	ft_putnbr(ang.z);
	ft_putchar('\n');
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

int     quit_button(t_big *big)
{
	big += 0;
	exit(EXIT_SUCCESS);
	return (0);
}

int			main()
{
	t_big big;

	big.camera.origin.x = 50;
	big.camera.origin.y = 0;
	big.camera.origin.z = 0;
	big.camera.direction.x = 100;
	big.camera.direction.y = 0;
	big.camera.direction.z = 0;
	big.camera.distance = 40;
	big.camera.vec_horizon.x = -big.camera.direction.z;
	big.camera.vec_horizon.y = 0;
	big.camera.vec_horizon.z = big.camera.direction.x;
	if (big.camera.vec_horizon.x == 0 && big.camera.vec_horizon.z == 0)
		big.camera.vec_horizon.z = 1;
	big.camera.vec_vertic.y = -big.camera.direction.x - big.camera.direction.z;
	big.camera.vec_vertic.x = big.camera.direction.y;
	big.camera.vec_vertic.z = big.camera.direction.y;
	big.camera.vecdir = normalize(big.camera.direction);
	big.camera.vec_horizon = normalize(big.camera.vec_horizon);
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
