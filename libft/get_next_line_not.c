/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:38:37 by sderet            #+#    #+#             */
/*   Updated: 2017/12/21 17:50:21 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"

static int	ft_read(char **str, int fd)
{
	int		nb_read;
	char	buffer[BUFF_SIZE + 1];
	char	*tmp;

	nb_read = read(fd, buffer, BUFF_SIZE);
	if (nb_read < 0)
		return (-1);
	buffer[nb_read] = '\0';
	tmp = *str;
	*str = ft_strjoin(*str, buffer);
	if (*tmp)
		free(tmp);
	return (nb_read);
}

static int	get_line(char **buff, char **line, char *tmpchar)
{
	char	*tmp;
	int		state;

	state = 0;
	if (*tmpchar == '\n')
		state = 1;
	*tmpchar = 0;
	*line = ft_strjoin("", *buff);
	if (state == 0 && ft_strlen(*buff))
	{
		*buff = ft_strnew(1);
		return (1);
	}
	else if (state == 0 && !(ft_strlen(*buff)))
		return (0);
	tmp = *buff;
	*buff = ft_strjoin(tmpchar + 1, "");
	free(tmp);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*buff = 0;
	char		*tmpchar;
	int			nb_read;

	if (line == NULL || BUFF_SIZE < 0)
		return (-1);
	*line = 0;
	if (buff == 0)
		buff = "";
	nb_read = BUFF_SIZE;
	while (line)
	{
		tmpchar = buff;
		while (*tmpchar || nb_read < BUFF_SIZE)
		{
			if (*tmpchar == 0 || *tmpchar == '\n' || *tmpchar == EOF)
				return (get_line(&buff, line, tmpchar));
			tmpchar++;
		}
		if ((nb_read = ft_read(&buff, fd)) == -1)
			return (-1);
	}
	return (-1);
}
