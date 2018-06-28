/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tang.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarasy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 18:24:47 by asarasy           #+#    #+#             */
/*   Updated: 2018/06/28 19:15:25 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	change_less_zero(char *tan)
{
	int a;
	int b;
	int c;

	a = ft_atoi(tan);
	b = 0;
	c = a;
	while (c > 1)
	{
		c /= 10;
		b++;
	}
	return ((double)a / pow(10, (double)b));
}

int		checktan(char *objet, t_big *b, int index)
{
	char	*tan;
	int		i;

	i = 0;
	tan = ft_strstr(objet, "tan:");
	if (tan == NULL)
		return (1);
	while (tan[i])
	{
		if (tan[i] == ';')
		{
			tan = ft_strsub(tan, 4, i - 3);
			b->objects[index].tangent = change_less_zero(tan);
			i = 0;
			if (tan[i] > 57 && tan[i] < 48)
			{
				free(tan);
				return (1);
			}
			while (tan[i] > 47 && tan[i] < 58)
				i++;
			if (tan[i] != ';')
			{
				free(tan);
				return (1);
			}
			return (0);
		}
		i++;
	}
	return (1);
}
