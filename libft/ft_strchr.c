/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:48:46 by sderet            #+#    #+#             */
/*   Updated: 2017/11/13 13:21:44 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	int		a;

	ch = (char)c;
	a = 0;
	while (s[a] != ch && s[a] != '\0')
		a++;
	if (s[a] == ch)
		return ((char*)(s + a));
	else
		return (NULL);
}
