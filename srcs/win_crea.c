/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_crea.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 16:05:17 by sderet            #+#    #+#             */
/*   Updated: 2018/06/28 16:17:26 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/rtv1.h"
#include "../minilibx/mlx.h"
#include <stdlib.h>
#include <fcntl.h>

void	window_creation(t_image *img, t_mmlx *mlx, t_big *big)
{
	big += 0;
	img->maxx = WINDOW_X;
	img->maxy = WINDOW_Y;
	mlx->win = mlx_new_window(mlx->mlx, img->maxx, img->maxy, "RT v1.0");
	mlx->image = mlx_new_image(mlx->mlx, img->maxx, img->maxy);
	img->map = mlx_get_data_addr(mlx->image,
		&img->bpp, &img->line_len, &img->endian);
}
