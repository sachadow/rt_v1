/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarasy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 06:58:27 by asarasy           #+#    #+#             */
/*   Updated: 2018/06/29 16:15:31 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_val_color2(char *color, t_color *couleur, int i)
{
	couleur->b = ft_atoi(color + i);
	if (color[i] > 57 && color[i] < 48)
		std_err(0);
	while (color[i] > 47 && color[i] < 58)
		i++;
	if (color[i] != ';')
		std_err(0);
	if (couleur->r < 0 || couleur->r > 255)
		std_err(0);
	if (couleur->g < 0 || couleur->g > 255)
		std_err(0);
	if (couleur->b < 0 || couleur->b > 255)
		std_err(0);
}

int		get_val_color(char *color, t_color *couleur)
{
	int i;

	i = 0;
	couleur->r = ft_atoi(color);
	if (color[i] > 57 && color[i] < 48)
		std_err(0);
	while (color[i] > 47 && color[i] < 58)
		i++;
	if (color[i] != ',')
		std_err(0);
	i++;
	couleur->g = ft_atoi(color + i);
	if (color[i] > 57 && color[i] < 48)
		std_err(0);
	while (color[i] > 47 && color[i] < 58)
		i++;
	if (color[i] != ',')
		std_err(0);
	i++;
	get_val_color2(color, couleur, i);
	free(color);
	return (0);
}
