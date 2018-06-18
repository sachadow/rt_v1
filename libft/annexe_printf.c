/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annexe_printf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 18:48:12 by sderet            #+#    #+#             */
/*   Updated: 2018/06/04 18:53:49 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	loop(char *parse, char *tmp, t_big *big)
{
	while (*parse != 0)
	{
		if (*parse == '%')
		{
			bigset(big);
			*parse = 0;
			ft_putstr(tmp);
			big->nbprint += ft_strlen(tmp);
			parse = ft_printtype((parse + 1), big);
			tmp = parse;
		}
		else
			parse++;
	}
	ft_putstr(tmp);
	big->nbprint += ft_strlen(tmp);
}
