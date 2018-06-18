/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 15:11:24 by sderet            #+#    #+#             */
/*   Updated: 2018/06/04 18:24:53 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>

void	printform(t_big *big, char *parse)
{
	int a;

	a = 0;
	while (big->lists.formats[a] != '\0')
	{
		if (*parse == big->lists.formats[a])
			big->fun_ptr[a](big, parse);
		a++;
	}
}

void	print_percent(t_big *big, char *parse)
{
	int		a;
	char	space;

	parse += 0;
	big += 0;
	space = ' ';
	a = 1;
	if (inacflags('0', *big))
		space = '0';
	while (!inacflags('-', *big) && big->lists.minim > a)
	{
		a++;
		ft_putchar(space);
	}
	ft_putchar('%');
	while (inacflags('-', *big) && big->lists.minim > a)
	{
		a++;
		ft_putchar(' ');
	}
	big->nbprint += a;
}

void	ft_putwstr(wchar_t const *str)
{
	int a;

	a = 0;
	while (str[a] != 0)
	{
		ft_putwchar(str[a]);
		a++;
	}
}
