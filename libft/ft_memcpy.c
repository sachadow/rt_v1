/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:23:26 by sderet            #+#    #+#             */
/*   Updated: 2017/11/13 13:57:14 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		a;
	const char	*csrc;
	char		*cdst;

	a = 0;
	csrc = (const char*)src;
	cdst = (char*)dst;
	while (a < n)
	{
		cdst[a] = csrc[a];
		a++;
	}
	return (cdst);
}
