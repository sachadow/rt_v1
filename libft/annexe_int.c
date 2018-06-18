/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annexe_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 19:14:33 by sderet            #+#    #+#             */
/*   Updated: 2018/06/06 15:37:56 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		intprc(t_big *big, char *val)
{
	int total_length;

	if (((inacflags('0', *big) && big->lists.minim > big->lists.prc &&
			!inacflags('-', *big) && big->lists.prc == 0 &&
			(inacflags(' ', *big) && ft_atoi(val) >= 0)) ||
			(inacflags('+', *big) && ft_atoi(val) == 0)) &&
			!inacflags('.', *big))
		total_length = big->lists.minim - big->sign - 1;
	else if (inacflags('0', *big) && big->lists.minim > big->lists.prc &&
			!inacflags('-', *big) && !inacflags('.', *big))
		total_length = big->lists.minim - big->sign;
	else
		total_length = big->lists.prc;
	return (total_length);
}

char	*annint(char *str, int *minus, int a, t_big *big)
{
	char	*tmp;

	*minus = 1;
	tmp = str;
	str = ft_strsub(str, 1, ft_strlen(str));
	a = ft_strlen(str);
	while (!ft_isdigit(str[a]))
		a--;
	str[++a] = 0;
	free(tmp);
	big->sign = 1;
	return (str);
}
