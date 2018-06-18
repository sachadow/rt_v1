/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:15:14 by sderet            #+#    #+#             */
/*   Updated: 2018/05/25 16:29:25 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		a;

	a = 0;
	while (s1[a] != '\0')
		a++;
	if (!(cpy = (char*)malloc(sizeof(char) * (a + 1))))
		return (NULL);
	while (a >= 0)
	{
		cpy[a] = s1[a];
		a--;
	}
	return (cpy);
}
