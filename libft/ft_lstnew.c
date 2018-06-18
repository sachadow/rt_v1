/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 18:38:47 by sderet            #+#    #+#             */
/*   Updated: 2017/11/17 14:00:44 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *list;

	if (!(list = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	list->next = NULL;
	if (content == 0)
	{
		list->content_size = 0;
		list->content = 0;
		return (list);
	}
	if (!(list->content = ft_memalloc(content_size)))
		return (NULL);
	ft_memcpy(list->content, content, content_size);
	list->content_size = content_size;
	return (list);
}
