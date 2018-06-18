/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:10:49 by sderet            #+#    #+#             */
/*   Updated: 2018/05/29 18:34:58 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	a;
	size_t	b;

	a = 0;
	b = (size_t)start;
	if (s == 0)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(char) * (len))))
		return (NULL);
	while (a < len)
	{
		str[a] = s[b];
		b++;
		a++;
	}
	str[len - 1] = '\0';
	return (str);
}
