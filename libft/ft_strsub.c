/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 17:50:57 by sderet            #+#    #+#             */
/*   Updated: 2018/06/28 17:50:59 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dst;

	i = start;
	j = 0;
	if (!s)
		return (NULL);
	if (!(dst = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (s[i] && j < len)
		dst[j++] = s[i++];
	dst[len] = '\0';
	return (dst);
}
