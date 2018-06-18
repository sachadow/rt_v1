/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:12:19 by sderet            #+#    #+#             */
/*   Updated: 2017/11/13 15:19:04 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cs;
	unsigned char	cc;
	size_t			a;

	a = 0;
	cs = (unsigned char*)s;
	cc = (unsigned char)c;
	while (a < n)
	{
		if (cs[a] == cc)
			return (cs + a);
		a++;
	}
	return (NULL);
}
