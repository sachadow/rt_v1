/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarasy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 06:58:27 by asarasy           #+#    #+#             */
/*   Updated: 2018/06/28 16:49:24 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		get_val_color(char *color, t_color *couleur)
{
	int i;

	i = 0;
	//printf("color = %s\n", color);
	couleur->r = ft_atoi(color);
	if (color[i] > 57 && color[i] < 48)
		return (1);
	while (color[i] > 47 && color[i] < 58)
		i++;
	if (color[i] != ',')
		return (1);
	i++;
	couleur->g = ft_atoi(color + i);
	if (color[i] > 57 && color[i] < 48)
		return (1);
	while (color[i] > 47 && color[i] < 58)
		i++;
	if (color[i] != ',')
		return (1);
	i++;
	couleur->b = ft_atoi(color + i);
	if (color[i] > 57 && color[i] < 48)
		return (1);
	while (color[i] > 47 && color[i] < 58)
		i++;
	if (color[i] != ';')
		return (1);
	if (couleur->r < 0 || couleur->r > 255)
		return (1);
	if (couleur->g < 0 || couleur->g > 255)
		return (1);
	if (couleur->b < 0 || couleur->b > 255)
		return (1);
	i++;
	free(color);
	return (0);
}
