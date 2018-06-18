/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 17:18:39 by sderet            #+#    #+#             */
/*   Updated: 2018/06/06 19:38:40 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Adds all the necessary 0's at the beginning of the string val.
*/

static wchar_t		*add_int_prc(t_big *big, wchar_t *val)
{
	int		total_length;
	int		zeroes_length;
	wchar_t	*zeroes_to_add;
	wchar_t	*result;

	if (inacflags('0', *big))
		total_length = big->lists.minim - big->sign;
	else
		return (val);
	zeroes_length = total_length - ft_wstrlen(val);
	if (zeroes_length > 0)
	{
		if (!(zeroes_to_add = (wchar_t*)malloc(sizeof(wchar_t) *
						(zeroes_length + 1))))
			exit(1);
		zeroes_to_add[zeroes_length] = '\0';
		ft_wstrset(zeroes_to_add, L'0', zeroes_length);
		result = ft_wstrjoin(zeroes_to_add, val);
		free(val);
		free(zeroes_to_add);
		return (result);
	}
	else
		return (val);
}

/*
**	Adds all the necessary ' ' (spaces) at the beginning of the string val.
*/

static wchar_t		*add_int_width(t_big *big, wchar_t *val)
{
	int		total_length;
	int		spaces_length;
	wchar_t	*spaces_to_add;
	wchar_t	*result;

	total_length = big->lists.minim;
	spaces_length = total_length - ft_wstrlen(val);
	if (spaces_length > 0)
	{
		if (!(spaces_to_add = (wchar_t*)malloc(sizeof(wchar_t) *
						(spaces_length + 1))))
			exit(1);
		ft_wstrset(spaces_to_add, L' ', spaces_length);
		spaces_to_add[spaces_length] = '\0';
		if (!inacflags('-', *big))
			result = ft_wstrjoin(spaces_to_add, val);
		else
			result = ft_wstrjoin(val, spaces_to_add);
		free(val);
		free(spaces_to_add);
		return (result);
	}
	else
		return (val);
}

static wchar_t		*add_int_misc(t_big *big, wchar_t *val)
{
	int a;
	int b;

	if (inacflags('.', *big))
	{
		b = 0;
		a = 0;
		while (b < big->lists.prc)
		{
			b += wchar_size(val[a]);
			a++;
		}
		if (b > big->lists.prc)
			a--;
		val[a] = 0;
	}
	return (val);
}

void				print_wstr(t_big *big, char *parse)
{
	wchar_t	*str;
	int		a;
	wchar_t	*tmp;

	parse += 0;
	tmp = (wchar_t*)va_arg(big->ap, void*);
	if (tmp == 0)
	{
		big->nbprint += 6;
		return (ft_putstr("(null)"));
	}
	else
		str = (wchar_t*)malloc(sizeof(wchar_t) * (ft_wstrlen(tmp) + 1));
	if (str == 0)
		exit(1);
	a = -1;
	while (tmp[++a])
		str[a] = tmp[a];
	str[a] = 0;
	str = add_int_misc(big, str);
	str = add_int_prc(big, str);
	str = add_int_width(big, str);
	ft_putwstr(str);
	big->nbprint += ft_wstrlen(str);
	free(str);
}
