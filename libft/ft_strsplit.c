/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 19:37:54 by sderet            #+#    #+#             */
/*   Updated: 2018/06/06 19:27:47 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	nb_words(const char *str, char e)
{
	int a;
	int b;
	int c;

	a = 0;
	c = 0;
	while (str[a + 1] != '\0' && str[a] != '\0')
	{
		b = 0;
		while (str[a] == e)
			a++;
		while (str[a] != e && str[a] != '\0')
		{
			a++;
			b++;
		}
		if (b > 0)
			c++;
	}
	return (c);
}

static char	**nb_char(const char *str, int c, char **tab, char e)
{
	int a;
	int b;
	int d;

	d = 0;
	a = 0;
	while (d < c)
	{
		b = 0;
		while (str[a] == e)
			a++;
		while (str[a] != e)
		{
			a++;
			b++;
		}
		if (b > 0)
			if (!(tab[d] = (char*)malloc(sizeof(char) * (b + 1))))
				return (NULL);
		d++;
	}
	return (tab);
}

static char	**ist_tab(const char *str, char **tab, char e)
{
	int a;
	int b;
	int c;

	a = 0;
	c = 0;
	while (str[a] != '\0')
	{
		b = 0;
		while (str[a] == e)
			a++;
		while (str[a] != e && str[a] != '\0')
		{
			tab[c][b] = str[a];
			a++;
			b++;
		}
		if (str[a] != '\0')
			tab[c][b] = '\0';
		c++;
	}
	return (tab);
}

char		**ft_strsplit(char const *s, char c)
{
	int		a;
	int		e;
	int		d;
	char	**tab;

	if (s == 0)
		return (NULL);
	e = nb_words(s, c);
	tab = (char**)malloc(sizeof(char*) * (e + 1));
	if (tab == 0)
		return (NULL);
	a = 0;
	d = 0;
	tab = nb_char(s, e, tab, c);
	tab = ist_tab(s, tab, c);
	tab[e] = 0;
	return (tab);
}
