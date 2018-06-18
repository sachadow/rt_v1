/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:21:18 by sderet            #+#    #+#             */
/*   Updated: 2017/11/14 15:19:35 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int		a;
	int		b;
	char	ch;

	a = 0;
	b = 0;
	ch = (char)c;
	while (s[a] != '\0')
	{
		if (s[a] == ch)
			b = a;
		a++;
	}
	if (s[a] == ch)
		return ((char*)(s + a));
	if (s[b] == ch)
		return ((char*)(s + b));
	else
		return (NULL);
}
