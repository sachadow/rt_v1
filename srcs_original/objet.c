/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objet.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarasy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 16:30:53 by asarasy           #+#    #+#             */
/*   Updated: 2018/06/29 16:41:41 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/rtv1.h"

int		object(char *objet, int *val, int len, t_big *b)
{
	char *obj;

	if (objet[val[0]] == '(')
	{
		val[1] = val[0];
		while (objet[++val[0]] && val[1] != 0)
		{
			if (objet[val[0]] == '(')
				return (std_err(0));
			if (objet[val[0]] == ')')
			{
				obj = ft_strsub(objet, val[1] + 1, val[0] - val[1] - 1);
				put_obj(obj, b, val[2]);
				val[2]++;
				val[1] = 0;
				if (val[2] > len)
					return (std_err(0));
			}
		}
	}
	return (0);
}
