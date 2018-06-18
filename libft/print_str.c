/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 17:18:39 by sderet            #+#    #+#             */
/*   Updated: 2018/06/06 19:38:25 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Adds all the necessary 0's at the beginning of the string val.
*/

static char			*add_int_prc(t_big *big, char *val)
{
	int		total_length;
	int		zeroes_length;
	char	*zeroes_to_add;
	char	*result;

	if (inacflags('0', *big) && !inacflags('-', *big))
		total_length = big->lists.minim - big->sign;
	else
		return (val);
	zeroes_length = total_length - ft_strlen(val);
	if (zeroes_length > 0)
	{
		if (!(zeroes_to_add = (char*)malloc(sizeof(char) *
						(zeroes_length + 1))))
			exit(1);
		zeroes_to_add[zeroes_length] = '\0';
		ft_memset(zeroes_to_add, '0', sizeof(char) * zeroes_length);
		result = ft_strjoin(zeroes_to_add, val);
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

static char			*add_int_width(t_big *big, char *val)
{
	int		total_length;
	int		spaces_length;
	char	*spaces_to_add;
	char	*result;

	total_length = big->lists.minim;
	spaces_length = total_length - ft_strlen(val);
	if (spaces_length > 0)
	{
		if (!(spaces_to_add = (char*)malloc(sizeof(char) *
						(spaces_length + 1))))
			exit(1);
		spaces_to_add[spaces_length] = '\0';
		ft_memset(spaces_to_add, ' ', sizeof(char) * spaces_length);
		if (!inacflags('-', *big))
			result = ft_strjoin(spaces_to_add, val);
		else
			result = ft_strjoin(val, spaces_to_add);
		free(val);
		free(spaces_to_add);
		return (result);
	}
	else
		return (val);
}

static char			*add_int_misc(t_big *big, char *val)
{
	int a;

	if (inacflags('.', *big))
	{
		a = 0;
		while (a < big->lists.prc)
			a++;
		val[a] = 0;
	}
	return (val);
}

void				print_str(t_big *big, char *parse)
{
	char		*str;

	if (*parse == 'S' || ft_strcmp(big->lists.actual_len, "l") == 0)
		return (print_wstr(big, parse));
	str = (char*)va_arg(big->ap, void*);
	if (str == 0)
		str = ft_strdup("(null)");
	else
		str = ft_strdup(str);
	str = add_int_misc(big, str);
	str = add_int_prc(big, str);
	str = add_int_width(big, str);
	ft_putstr(str);
	big->nbprint += ft_strlen(str);
	free(str);
}
