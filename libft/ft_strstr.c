/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:33:52 by sderet            #+#    #+#             */
/*   Updated: 2017/11/14 15:24:16 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	if (haystack[0] == '\0' && needle[0] == '\0')
		return ((char*)haystack);
	return (ft_strnstr(haystack, needle, ft_strlen(haystack)));
}
