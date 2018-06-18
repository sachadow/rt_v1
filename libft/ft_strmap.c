/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:25:13 by sderet            #+#    #+#             */
/*   Updated: 2017/11/15 14:22:08 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		a;
	char	*strm;

	if (s == 0)
		return (NULL);
	a = 0;
	if (!(strm = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[a] != '\0')
	{
		strm[a] = f(s[a]);
		a++;
	}
	strm[a] = '\0';
	return (strm);
}
