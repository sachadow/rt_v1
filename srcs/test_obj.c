/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarasy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 18:11:27 by asarasy           #+#    #+#             */
/*   Updated: 2018/09/25 19:09:01 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/rtv1.h"

int		checkpos(char *objet, t_big *b, int index)
{
	char	*position;
	int		i;

	i = 0;
	position = ft_strstr(objet, "position:");
	if (position == NULL)
		return (1);
	while (position[i])
	{
		if (position[i] == ';')
		{
			position = ft_strsub(position, 9, i - 8);
			i = get_val_pos(position, &(b->objects[index].origin));
			free(position);
			if (i == 1)
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (1);
}

int		checknorm(char *objet, t_big *b, int index)
{
	char	*normale;
	int		i;

	i = 0;
	normale = ft_strstr(objet, "normale:");
	if (normale == NULL)
		return (1);
	while (normale[i])
	{
		if (normale[i] == ';')
		{
			normale = ft_strsub(normale, 8, i - 7);
			i = get_val_pos(normale, &(b->objects[index].normale));
			free(normale);
			if (i == 1)
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (1);
}

int		checkcolor(char *objet, t_big *b, int index)
{
	char	*color;
	int		i;

	i = 0;
	color = ft_strstr(objet, "color:");
	if (color == NULL)
		return (1);
	while (color[i])
	{
		if (color[i] == ';')
		{
			color = ft_strsub(color, 6, i - 5);
			i = get_val_color(color, &(b->objects[index].color));
			return (i);
		}
		i++;
	}
	return (1);
}

int		checkray(char *objet, t_big *b, int index)
{
	char	*rayon;
	int		i;

	i = -1;
	rayon = ft_strstr(objet, "rayon:");
	if (rayon == NULL)
		return (1);
	while (rayon[++i])
	{
		if (rayon[i] == ';')
		{
			rayon = ft_strsub(rayon, 6, i - 5);
			b->objects[index].rayon = ft_atoi(rayon);
			i = 0;
			if (rayon[i] > 57 && rayon[i] < 48)
				return (std_err(0));
			while (rayon[i] > 47 && rayon[i] < 58)
				i++;
			if (rayon[i] != ';')
				return (std_err(0));
			free(rayon);
			return (0);
		}
	}
	return (1);
}

void	get_val_obj(char *objet, t_big *b, int index)
{
	int erreur;

	erreur = 0;
	erreur += checkpos(objet, b, index);
	erreur += checkcolor(objet, b, index);
	if (b->objects[index].type == 1 || b->objects[index].type == 3 ||
			b->objects[index].type == 5)
		erreur += checkray(objet, b, index);
	if (b->objects[index].type > 1)
		erreur += checknorm(objet, b, index);
	if (b->objects[index].type == 4)
		erreur += checktan(objet, b, index);
	if (erreur > 0)
		std_err(0);
	free(objet);
}
