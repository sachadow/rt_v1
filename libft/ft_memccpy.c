/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:29:35 by sderet            #+#    #+#             */
/*   Updated: 2017/11/13 13:57:23 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*csrc;
	unsigned char	*cdst;
	size_t			a;
	unsigned char	b;

	a = 0;
	csrc = (unsigned char*)src;
	cdst = (unsigned char*)dst;
	b = (unsigned char)c;
	while (a < n)
	{
		cdst[a] = csrc[a];
		if (b == csrc[a])
			return (cdst + a + 1);
		a++;
	}
	return (NULL);
}
