/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annexe_funchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 18:36:30 by sderet            #+#    #+#             */
/*   Updated: 2018/06/04 18:39:52 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Puts length modifiers in actual_len based on the ones in big.lists.len
*/

void	put_len(char **actual_len, char *parse, t_big big)
{
	int a;

	a = 0;
	while (a < 6)
	{
		if (ft_strncmp(parse, big.lists.len[a],
					ft_strlen(big.lists.len[a])) == 0)
			ft_strncpy(*actual_len, parse, ft_strlen(big.lists.len[a]));
		a++;
	}
}

/*
**	On affiche ici un wchar_t. Pour ce faire, on print a l'ecran plusieurs
**	char a la suite, ceux composant notre wchar_t. Les operations >> 6, 12, 18
**	permettent d'afficher seulement une partie de la chaine en les combinant
**	aux operations & 63.
**	Les + a la fin correspondent aux valeurs a ajouter a chaque char a
**	afficher en UTF-8.
**	128 = 1000 0000
**	192 = 1100 0000
**	etc...
*/

void	ft_putwchar(wchar_t const c)
{
	if (c <= 127)
		ft_putchar(c);
	else if (c <= 2047)
	{
		ft_putchar((c >> 6) + 192);
		ft_putchar((c & 63) + 128);
	}
	else if (c <= 65535)
	{
		ft_putchar((c >> 12) + 224);
		ft_putchar(((c >> 6) & 63) + 128);
		ft_putchar((c & 63) + 128);
	}
	else if (c <= 1114111)
	{
		ft_putchar((c >> 18) + 240);
		ft_putchar(((c >> 12) & 63) + 128);
		ft_putchar(((c >> 6) & 63) + 128);
		ft_putchar((c & 63) + 128);
	}
}

int		wchar_size(wchar_t c)
{
	if (c <= 127)
		return (1);
	else if (c <= 2047)
		return (2);
	else if (c <= 65535)
		return (3);
	else if (c <= 1114111)
		return (4);
	return (-1);
}

int		ft_wstrlen(wchar_t const *str)
{
	int a;
	int b;

	a = 0;
	b = 0;
	while (str[a])
	{
		b += wchar_size(str[a]);
		a++;
	}
	return (b);
}

int		ft_wstrsize(wchar_t const *str)
{
	int a;

	a = 0;
	while (str[a])
		a++;
	return (a);
}
