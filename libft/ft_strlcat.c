/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:02:35 by sderet            #+#    #+#             */
/*   Updated: 2017/11/10 13:50:43 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t a;
	size_t b;
	size_t c;

	a = 0;
	b = 0;
	while (src[b] != '\0')
		b++;
	while (dst[a] != '\0' && a < size)
		a++;
	if (a == size)
		return (size + b);
	c = b;
	b = 0;
	while (src[b] != '\0' && b + a < size)
	{
		dst[a + b] = src[b];
		b++;
	}
	if (b + a == size)
		dst[a + b - 1] = '\0';
	else if (src[b] == '\0')
		dst[a + b] = '\0';
	return (a + c);
}
