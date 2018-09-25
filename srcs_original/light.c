/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarasy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 08:45:55 by asarasy           #+#    #+#             */
/*   Updated: 2018/06/28 18:19:04 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/rtv1.h"

int		test_position_light(char *light, t_big *b)
{
	char	*position;
	int		i;

	i = 0;
	position = ft_strstr(light, "position:");
	if (position == NULL)
		exit(0);
	while (position[i])
	{
		if (position[i] == ';')
		{
			position = ft_strsub(position, 9, i - 8);
			i = get_val_pos(position, &(b->light.origin));
			free(position);
			if (i == 0)
				exit(0);
			return (1);
		}
		i++;
	}
	exit(0);
}

int		search_param_light(char *test, t_big *b)
{
	char	*light;
	int		i;

	i = 7;
	light = ft_strstr(test, "Light:{");
	if (light == NULL)
		exit(0);
	while (light[i] && i >= 0)
	{
		if (light[i] == '{')
			exit(0);
		if (light[i] == '}')
		{
			light = ft_strsub(light, 7, i - 7);
			if (test_position_light(light, b) == 1)
			{
				free(light);
				return (1);
			}
			free(light);
			exit(0);
		}
		i++;
	}
	exit(0);
}
