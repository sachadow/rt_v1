/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:17:06 by sderet            #+#    #+#             */
/*   Updated: 2017/11/10 19:17:25 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			a;
	unsigned char	*ch;

	ch = (unsigned char*)b;
	a = 0;
	while (a < len)
	{
		ch[a] = (unsigned char)c;
		a++;
	}
	return (b);
}
