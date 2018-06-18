/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:19:26 by sderet            #+#    #+#             */
/*   Updated: 2017/11/17 14:21:29 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (lst == 0)
		return ;
	f(lst);
	while (lst->next != NULL)
	{
		lst = lst->next;
		f(lst);
	}
}
