/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annexe_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 18:57:03 by sderet            #+#    #+#             */
/*   Updated: 2018/06/04 19:32:02 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*annoct(char *str, unsigned long long val, int a, char *base)
{
	char *tmp;

	if (!(str = (char*)malloc(1 + (sizeof(val)
						* CHAR_BIT + 2) / 3 + 1)))
		exit(0);
	a = 1 + (sizeof(val) * CHAR_BIT + 2) / 3 + 1;
	str[--a] = '\0';
	while (val != 0 || a == (sizeof(val) * CHAR_BIT + 2) / 3 + 1)
	{
		str[--a] = base[val % 8];
		val /= 8;
	}
	tmp = str;
	str = ft_strjoin(str + a, "");
	free(tmp);
	return (str);
}
