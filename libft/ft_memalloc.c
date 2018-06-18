/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:33:55 by sderet            #+#    #+#             */
/*   Updated: 2017/11/13 14:37:40 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void *alloc;

	if (!(alloc = malloc(size)))
		return (NULL);
	ft_bzero(alloc, size);
	return (alloc);
}
