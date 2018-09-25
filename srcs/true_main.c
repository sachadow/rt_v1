/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:18:55 by sderet            #+#    #+#             */
/*   Updated: 2018/09/25 19:01:16 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
#include "../head/rtv1.h"
#include "../libft/libft.h"
#include <stdlib.h>

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

	big.camera.xy_angle = 90;
	big.camera.xz_angle = 0;

	big.camera.distance = 0;
	ft_get_conf(&big);
	big.camera.xy_angle = RAD(big.camera.xy_angle);
	big.camera.xz_angle = RAD(big.camera.xz_angle);
	big.camera.direction.x = cos(big.camera.xz_angle) * cos(big.camera.xy_angle);
	big.camera.direction.z = sin(big.camera.xz_angle) * cos(big.camera.xy_angle);
	big.camera.direction.y = sin(big.camera.xy_angle);
	if (big.camera.direction.x == 0 && big.camera.direction.y == 0 &&
			big.camera.direction.z == 0)
		exit(0);
	big.camera.distance = 40;
	big.intersec[0] = &sphere_c;
	big.intersec[1] = &plan_c;
	big.intersec[2] = &cyl_c;
	big.intersec[3] = &cone_c;
	big.intersec[4] = &disk_c;
	big.camera = init_cam(big.camera);
	big.mlx.mlx = mlx_init();
	window_creation(&(big.img), &(big.mlx), &big);
	raytracing(big.camera, &big);
	mlx_put_image_to_window(big.mlx.mlx, big.mlx.win, big.mlx.image, 0, 0);
	mlx_hook(big.mlx.win, 17, 0, quit_button, &big);
	mlx_loop(big.mlx.mlx);
	return (0);
}
