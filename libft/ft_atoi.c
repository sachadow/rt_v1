/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:51:29 by sderet            #+#    #+#             */
/*   Updated: 2017/11/14 15:14:15 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int a;
	int b;
	int c;

	a = 0;
	b = 0;
	c = 1;
	while ((str[a] >= 9 && str[a] <= 13) || str[a] == 32)
		a++;
	if (str[a] == '+' || str[a] == '-')
	{
		if (str[a] == '-')
			c = -c;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9' && str[a] != '\0')
	{
		b = (b * 10) + (str[a] - 48);
		a++;
	}
	b *= c;
	return (b);
}
