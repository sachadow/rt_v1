/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 16:45:37 by sderet            #+#    #+#             */
/*   Updated: 2018/06/04 18:56:49 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include <stdlib.h>

/*
**	Recupere toutes les informations qui se trouvent avant le format
**	puis appelle printform pour l'afficher.
*/

char	*ft_printtype(char *parse, t_big *big)
{
	int	a;
	int b;
	int c;

	a = 0;
	c = 1;
	put_flags(&(big->lists.actual_flags), parse, *big);
	while (informat(parse[a], *big) != 1 && parse[a] != 0)
	{
		c = a;
		a = inside_printtype(parse, a, big);
		b = 0;
		while (b < 6)
		{
			if (ft_strncmp(&(parse[a]), big->lists.len[b],
						ft_strlen(big->lists.len[b])) == 0)
				a += ft_strlen(big->lists.len[b]);
			b++;
		}
		if (c == a)
			break ;
	}
	if (informat(parse[a], *big))
		printform(big, parse + a);
	return ((c == a ? parse + a : parse + a + 1));
}

int		inside_printtype(char *parse, int a, t_big *big)
{
	while (inflags(parse[a], *big) == 1 && parse[a] != 0 && parse[a] != '.')
		a++;
	if (ft_isdigit(parse[a]))
		big->lists.minim = ft_atoi(&(parse[a]));
	while (ft_isdigit(parse[a]))
		a++;
	if (parse[a] == '.')
		big->lists.prc = ft_atoi(&(parse[++a]));
	while (ft_isdigit(parse[a]))
		a++;
	if (inlen(parse[a], *big) == 1)
		put_len(&(big->lists.actual_len), &(parse[a]), *big);
	return (a);
}

void	bigset(t_big *big)
{
	int a;

	a = -1;
	while (++a < 10)
		big->lists.actual_flags[a] = '\0';
	a = -1;
	while (++a < 3)
		big->lists.actual_len[a] = '\0';
	big->lists.minim = 0;
	big->lists.prc = 0;
	big->sign = 0;
}

int		ft_printf(const char *format, ...)
{
	char		*parse;
	char		*begin;
	char		*tmp;
	t_big		big;

	startbig(&big);
	va_start(big.ap, format);
	parse = ft_strjoin(format, "");
	begin = parse;
	tmp = parse;
	loop(parse, tmp, &big);
	free(big.lists.actual_flags);
	free(big.lists.actual_len);
	free(big.lists.len);
	free(begin);
	return (big.nbprint);
}
