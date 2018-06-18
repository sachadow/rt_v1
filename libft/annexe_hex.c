/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annexe_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 18:57:03 by sderet            #+#    #+#             */
/*   Updated: 2018/06/04 19:14:10 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		hex_prc(t_big *big)
{
	int total_length;

	if (inacflags('0', *big) && big->lists.minim > big->lists.prc &&
			!inacflags('-', *big) && big->lists.prc == 0 &&
			(!inacflags('#', *big) || !inacflags('.', *big)))
		total_length = big->lists.minim - big->sign;
	else
		total_length = big->lists.prc;
	if (total_length == big->lists.minim - big->sign && inacflags('#', *big)
			&& big->compteur != 0)
		total_length -= 2;
	return (total_length);
}

char	*annhex(char *str, unsigned long long val, int a, char *base)
{
	char *tmp;

	if (!(str = (char*)malloc(1 + (sizeof(val)
						* CHAR_BIT + 2) / 3 + 1)))
		exit(0);
	a = 1 + (sizeof(val) * CHAR_BIT + 2) / 3 + 1;
	str[--a] = '\0';
	while (val != 0 || a == (sizeof(val) * CHAR_BIT + 2) / 3 + 1)
	{
		str[--a] = base[val % 16];
		val /= 16;
	}
	tmp = str;
	str = ft_strjoin(str + a, "");
	free(tmp);
	return (str);
}
