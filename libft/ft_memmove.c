/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:44:29 by sderet            #+#    #+#             */
/*   Updated: 2017/11/14 15:37:54 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*csrc;
	char	*cdst;

	if (dst > src)
	{
		cdst = (char*)dst;
		csrc = (char*)src;
		while (len-- != 0)
			cdst[len] = csrc[len];
		return (cdst);
	}
	else
		return (ft_memcpy(dst, src, len));
}
