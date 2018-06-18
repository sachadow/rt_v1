/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:51:32 by sderet            #+#    #+#             */
/*   Updated: 2017/11/10 14:45:18 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	a;
	size_t	b;

	a = 0;
	if (needle[0] == '\0')
		return ((char*)(haystack));
	while (haystack[a] != '\0' && a < len)
	{
		b = 0;
		while (haystack[a + b] == needle[b] && needle[b] != '\0')
			b++;
		if (a + b > len)
			return (NULL);
		if (needle[b] == '\0')
			return ((char*)(haystack + a));
		a++;
	}
	return (NULL);
}
