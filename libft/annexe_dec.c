/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annexe_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 18:43:51 by sderet            #+#    #+#             */
/*   Updated: 2018/06/04 18:46:05 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	dec_prc(t_big *big, char *val)
{
	int	total_length;

	if (inacflags('0', *big) && big->lists.minim > big->lists.prc &&
			!inacflags('-', *big) && big->lists.prc == 0)
		total_length = big->lists.minim - big->sign;
	else
		total_length = big->lists.prc;
	if (inacflags('0', *big) && big->lists.minim > big->lists.prc &&
			!inacflags('-', *big) && big->lists.prc == 0)
		total_length = big->lists.minim - big->sign;
	else
		total_length = big->lists.prc;
	return (total_length);
}
