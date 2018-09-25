/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarasy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:53:26 by asarasy           #+#    #+#             */
/*   Updated: 2018/06/29 16:23:07 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/rtv1.h"

int		get_val_pos(char *position, t_dpos3d *pos)
{
	int i;

	i = 0;
	pos->x = ft_atoi(position);
	if (position[i] > 57 && position[i] < 48 && position[i] != '-')
		return (0);
	while ((position[i] > 47 && position[i] < 58) || position[i] == '-')
		i++;
	if (position[i++] != ',')
		return (0);
	pos->y = ft_atoi(position + i);
	if (position[i] > 57 && position[i] < 48 && position[i] != '-')
		return (0);
	while ((position[i] > 47 && position[i] < 58) || position[i] == '-')
		i++;
	if (position[i++] != ',')
		return (0);
	pos->z = ft_atoi(position + i);
	if (position[i] > 57 && position[i] < 48 && position[i] != '-')
		return (0);
	while ((position[i] > 47 && position[i] < 58) || position[i] == '-')
		i++;
	if (position[i] == ';')
		return (1);
	return (0);
}

int		search_param_camera(char *test, t_big *b)
{
	char	*camera;
	int		i;

	i = 7;
	camera = ft_strstr(test, "Camera:{");
	if (camera == NULL)
		return (std_err(0));
	while (camera[++i] && i >= 0)
	{
		if (camera[i] == '{')
			return (std_err(0));
		if (camera[i] == '}')
		{
			camera = ft_strsub(camera, 8, i - 8);
			if (test_position_cam(camera, b) == 1
					&& test_direction_cam(camera, b) == 1)
			{
				free(camera);
				return (1);
			}
			free(camera);
			return (std_err(0));
		}
	}
	return (std_err(0));
}

int		test_conf(char *conf, t_big *b)
{
	int i;

	i = 0;
	search_param_camera(conf, b);
	search_param_objet(conf, b);
	search_param_light(conf, b);
	return (1);
}

void	ft_get_conf(t_big *b)
{
	char	*line;
	char	*tmp;
	int		i;
	int		fd;

	i = 0;
	fd = open("rt_conf", O_RDONLY);
	if (!(tmp = ft_strnew(0)))
		std_err(0);
	while ((i = get_next_line(fd, &line)) > 0)
	{
		if (!(ft_isascii(line[0])))
			std_err(0);
		if (!(tmp = ft_strjoinfree(tmp, line, 3)))
			std_err(0);
		if (!(tmp = ft_strjoinfree(tmp, "\n", 1)))
			std_err(0);
	}
	if (i == -1)
		std_err(0);
	test_conf(tmp, b);
	free(tmp);
}
