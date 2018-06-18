/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 17:06:35 by sderet            #+#    #+#             */
/*   Updated: 2018/06/06 19:33:51 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

wchar_t	*ft_wstrjoin(wchar_t const *s1, wchar_t const *s2)
{
	wchar_t	*str;
	int		a;
	int		b;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	if (!(str = (wchar_t *)malloc(sizeof(wchar_t) * (ft_wstrlen(s1) +
				ft_wstrlen(s2) + 1))))
		exit(1);
	if (str != 0)
	{
		a = -1;
		while (s1[++a] != 0)
			str[a] = s1[a];
		b = -1;
		while (s2[++b] != 0)
			str[a + b] = s2[b];
		str[a + b] = 0;
	}
	else
		return (NULL);
	return (str);
}

void	ft_wstrset(wchar_t *str, wchar_t wch, int len)
{
	int a;

	a = 0;
	while (a < len)
	{
		str[a] = wch;
		a++;
	}
}

void	print_up_char(t_big *big)
{
	wchar_t	val;
	int		a;
	char	space;

	space = ' ';
	val = (wchar_t)(wint_t)va_arg(big->ap, void*);
	a = wchar_size(val);
	if (inacflags('0', *big))
		space = '0';
	while (!inacflags('-', *big) && big->lists.minim > a)
	{
		a++;
		ft_putchar(space);
	}
	ft_putwchar(val);
	while (inacflags('-', *big) && big->lists.minim > a)
	{
		a++;
		ft_putchar(' ');
	}
	big->nbprint += a;
}

void	print_char(t_big *big, char *parse)
{
	char	val;
	int		a;
	char	space;

	a = 1;
	space = ' ';
	if (*parse == 'C' || ft_strcmp(big->lists.actual_len, "l") == 0)
		return (print_up_char(big));
	else
		val = (char)va_arg(big->ap, void *);
	if (inacflags('0', *big))
		space = '0';
	while (!inacflags('-', *big) && big->lists.minim > a)
	{
		a++;
		ft_putchar(space);
	}
	ft_putchar(val);
	while (inacflags('-', *big) && big->lists.minim > a)
	{
		a++;
		ft_putchar(' ');
	}
	big->nbprint += a;
}
