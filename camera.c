/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarasy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 16:16:00 by asarasy           #+#    #+#             */
/*   Updated: 2018/06/29 16:22:44 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		test_position_cam(char *camera, t_big *b)
{
	char	*position;
	int		i;

	i = 0;
	position = ft_strstr(camera, "position:");
	if (position == NULL)
		return (std_err(0));
	while (position[i])
	{
		if (position[i] == ';')
		{
			position = ft_strsub(position, 9, i - 8);
			i = get_val_pos(position, &(b->camera.origin));
			free(position);
			if (i == 0)
				return (std_err(0));
			return (1);
		}
		i++;
	}
	return (std_err(0));
}

int		test_direction_cam(char *camera, t_big *b)
{
	char	*direction;
	int		i;

	i = 0;
	direction = ft_strstr(camera, "direction:");
	if (direction == NULL)
		return (std_err(0));
	while (direction[i])
	{
		if (direction[i] == ';')
		{
			direction = ft_strsub(direction, 10, i - 9);
			i = get_val_pos(direction, &(b->camera.direction));
			free(direction);
			if (i == 0)
				return (std_err(0));
			return (1);
		}
		i++;
	}
	return (std_err(0));
}
