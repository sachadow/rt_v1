/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objet.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarasy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 15:07:26 by asarasy           #+#    #+#             */
/*   Updated: 2018/06/29 16:44:00 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/rtv1.h"

int		test_number_object(char *objet)
{
	char	*number;
	int		i;
	int		len;

	i = 7;
	number = ft_strstr(objet, "number:");
	if (number == NULL)
		return (std_err(0));
	if (number[i] > 57 && number[i] < 48)
		return (std_err(0));
	len = ft_atoi(number + i);
	while (number[i] < 58 && number[i] > 47)
		i++;
	if (number[i] != ';')
		return (std_err(0));
	if (len == 0)
		return (std_err(0));
	return (len);
}

int		put_obj(char *objet, t_big *b, int index)
{
	char	*type;
	int		nbr;
	int		i;

	nbr = 0;
	i = 5;
	type = ft_strstr(objet, "type:");
	if (type == NULL)
		return (std_err(0));
	if (type[i] > 48 && type[i] < 53)
		nbr = type[i] - 48;
	else
		return (std_err(0));
	i++;
	if (type[i] != ';')
		return (std_err(0));
	b->objects[index].type = nbr;
	get_val_obj(objet, b, index);
	return (0);
}

int		test_obj(char *objet, t_big *b, int len)
{
	int		*val;

	if (!(val = (int*)malloc(sizeof(int) * 3)))
		return (std_err(0));
	val[0] = -1;
	val[2] = 0;
	while (objet[++val[0]])
		object(objet, val, len, b);
	if (val[2] != len)
		return (std_err(0));
	b->objects[val[2]].type = 0;
	free(val);
	return (0);
}

int		test_objet(char *objet, t_big *b)
{
	int len;

	len = test_number_object(objet);
	if (!(b->objects = (t_primitiv *)malloc(sizeof(t_primitiv) * (len + 1))))
	{
		free(objet);
		return (std_err(0));
	}
	test_obj(objet, b, len);
	return (0);
}

int		search_param_objet(char *test, t_big *b)
{
	char	*objet;
	int		i;

	i = 7;
	objet = ft_strstr(test, "Objet:{");
	if (objet == NULL)
		return (std_err(0));
	while (objet[i] && i >= 0)
	{
		if (objet[i] == '{')
			return (std_err(0));
		if (objet[i] == '}')
		{
			objet = ft_strsub(objet, 7, i - 7);
			test_objet(objet, b);
			free(objet);
			return (0);
		}
		i++;
	}
	return (std_err(0));
	return (0);
}
