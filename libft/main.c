/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 14:06:01 by sderet            #+#    #+#             */
/*   Updated: 2018/06/04 19:28:51 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include <stdio.h>
#include "ft_printf.h"

int main(int argc, char **argv)
{
	int a;
	char c;

	argc += 0;
	argv += 0;
	c = 0;
	a = ft_printf("%d", 42);
	printf("\n%d\n", a);
	a = printf("%d", 42);
	printf("\n%d\n", a);
	return (0);
}
