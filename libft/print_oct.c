/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_oct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 18:15:06 by sderet            #+#    #+#             */
/*   Updated: 2018/06/06 19:49:08 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long	get_int_type(t_big *big, char *parse)
{
	if (ft_strcmp(big->lists.actual_len, "l") == 0 || *parse == 'O')
		return ((unsigned long long)va_arg(big->ap, unsigned long));
	else if (ft_strcmp(big->lists.actual_len, "h") == 0)
		return ((unsigned long long)(unsigned short int)va_arg(big->ap, int));
	else if (ft_strcmp(big->lists.actual_len, "hh") == 0)
		return ((unsigned long long)(unsigned char)va_arg(big->ap, int));
	else if (ft_strcmp(big->lists.actual_len, "j") == 0)
		return ((unsigned long long)va_arg(big->ap, uintmax_t));
	else if (ft_strcmp(big->lists.actual_len, "z") == 0)
		return ((unsigned long long)va_arg(big->ap, size_t));
	else if (ft_strcmp(big->lists.actual_len, "ll") == 0)
		return ((unsigned long long)va_arg(big->ap, unsigned long long));
	else
		return ((unsigned long long)(unsigned int)va_arg(big->ap, void *));
}

/*
**	Adds all the necessary 0's at the beginning of the string val.
*/

static char			*add_int_prc(t_big *big, char *val)
{
	int		total_length;
	int		zero_length;
	char	*zeroes_to_add;
	char	*result;

	if (inacflags('0', *big) && big->lists.minim > big->lists.prc &&
			!inacflags('-', *big) && big->lists.prc == 0 &&
			!inacflags('.', *big))
		total_length = big->lists.minim - big->sign;
	else
		total_length = big->lists.prc;
	zero_length = total_length - ft_strlen(val);
	if (zero_length > 0)
	{
		if (!(zeroes_to_add = (char*)malloc(sizeof(char) * (zero_length + 1))))
			exit(1);
		zeroes_to_add[zero_length] = '\0';
		ft_memset(zeroes_to_add, '0', sizeof(char) * zero_length);
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
	char	*tmp;

	if (inacflags('#', *big) && val[0] != '0'
			&& (ft_atoi(val) != 0 || val[0] == 0))
	{
		tmp = val;
		val = ft_strjoin("0", val);
		free(tmp);
	}
	return (val);
}

void				print_oct(t_big *big, char *parse)
{
	unsigned long long	val;
	char				*str;
	char				*base;
	int					a;

	val = get_int_type(big, parse);
	base = "012345678";
	a = 0;
	str = 0;
	if (val == 0 && inacflags('.', *big) && big->lists.prc == 0)
		str = ft_strnew(1);
	else
		str = annoct(str, val, a, base);
	str = add_int_prc(big, str);
	str = add_int_misc(big, str);
	str = add_int_width(big, str);
	ft_putstr(str);
	big->nbprint += ft_strlen(str);
	free(str);
}
