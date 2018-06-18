/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:21:00 by sderet            #+#    #+#             */
/*   Updated: 2017/11/14 15:46:46 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*cs1;
	unsigned char	*cs2;
	size_t			a;

	a = 0;
	cs1 = (unsigned char*)s1;
	cs2 = (unsigned char*)s2;
	while (a < n)
	{
		if (cs1[a] != cs2[a])
			return (cs1[a] - cs2[a]);
		a++;
	}
	return (0);
}
