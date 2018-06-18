/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:51:51 by sderet            #+#    #+#             */
/*   Updated: 2018/05/25 17:24:51 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <stdlib.h>

char	*ft_uitoa(unsigned long long n)
{
	unsigned long long	a;
	size_t				len;
	char				*str;

	a = n;
	if (n == -n)
		return (ft_strdup((n == 0) ? "0" : "-9223372036854775808"));
	len = (n <= 0 ? 2 : 1);
	while (n != 0 && len++)
		n /= 10;
	if (!(str = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	ft_strclr(str);
	len--;
	while (a != 0)
	{
		len--;
		str[len] = (a % 10 + '0');
		a /= 10;
	}
	return (str);
}
