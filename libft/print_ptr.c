/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 17:05:10 by sderet            #+#    #+#             */
/*   Updated: 2018/06/06 19:48:17 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Adds all the necessary 0's at the beginning of the string val.
*/

static char			*add_int_prc(t_big *big, char *val, unsigned long long nbr)
{
	int		total_length;
	int		zero_length;
	char	*zeroes_to_add;
	char	*result;

	if (inacflags('0', *big) && big->lists.minim > big->lists.prc &&
			!inacflags('-', *big) && big->lists.prc == 0)
		total_length = big->lists.minim - big->sign;
	else
		total_length = big->lists.prc;
	total_length -= (nbr != 0 || inacflags('.', *big) ? 0 : 2);
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

	big += 0;
	tmp = val;
	val = ft_strjoin("0x", val);
	free(tmp);
	return (val);
}

void				print_ptr(t_big *big, char *parse)
{
	char				*base;
	unsigned long long	val;
	char				*str;
	int					a;

	parse += 0;
	str = 0;
	a = 0;
	val = (unsigned long long)va_arg(big->ap, void *);
	base = "0123456789abcdef";
	if (val == 0 && inacflags('.', *big) && big->lists.prc == 0)
		str = ft_strnew(1);
	else
		str = annptr(str, val, a, base);
	str = add_int_prc(big, str, val);
	str = add_int_misc(big, str);
	str = add_int_width(big, str);
	ft_putstr(str);
	big->nbprint += ft_strlen(str);
	free(str);
}
