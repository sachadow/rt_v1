/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:00:24 by sderet            #+#    #+#             */
/*   Updated: 2017/11/15 17:33:07 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t a;

	a = 0;
	while (s1[a] == s2[a] && s1[a] != '\0' && s2[a] != '\0' && a < n)
		a++;
	if (a == n)
		return ((int)((unsigned char)s1[a - 1] - (unsigned char)s2[a - 1]));
	else
		return ((int)((unsigned char)s1[a] - (unsigned char)s2[a]));
}
