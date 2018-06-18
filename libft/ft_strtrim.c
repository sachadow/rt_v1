/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:42:11 by sderet            #+#    #+#             */
/*   Updated: 2017/11/15 17:04:20 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <string.h>

char		*ft_strtrim(char const *s)
{
	size_t	a;
	size_t	c;

	if (s == 0)
		return (NULL);
	a = 0;
	c = ft_strlen(s) - 1;
	while (s[a] == '\t' || s[a] == '\n' || s[a] == ' ')
		a++;
	while ((s[c] == '\t' || s[c] == '\n' || s[c] == ' ') && c > a)
		c--;
	return (ft_strsub(s, a, c - a + 1));
}
