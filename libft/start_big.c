/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_big.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 18:29:20 by sderet            #+#    #+#             */
/*   Updated: 2018/06/06 19:28:57 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	startbig_2(t_big *big)
{
	big->fun_ptr[0] = &print_str;
	big->fun_ptr[1] = &print_str;
	big->fun_ptr[2] = &print_ptr;
	big->fun_ptr[3] = &print_int;
	big->fun_ptr[4] = &print_int;
	big->fun_ptr[5] = &print_int;
	big->fun_ptr[6] = &print_oct;
	big->fun_ptr[7] = &print_oct;
	big->fun_ptr[8] = &print_dec;
	big->fun_ptr[9] = &print_dec;
	big->fun_ptr[10] = &print_hex;
	big->fun_ptr[11] = &print_hex;
	big->fun_ptr[12] = &print_char;
	big->fun_ptr[13] = &print_char;
	big->fun_ptr[14] = &print_percent;
}

void	startbig(t_big *big)
{
	if (!(big->lists.len = (char**)malloc(sizeof(char*) * 7)) ||
			!(big->lists.actual_flags = (char*)malloc(sizeof(char) * 10)) ||
			!(big->lists.actual_len = (char*)malloc(sizeof(char) * 3)))
		exit(1);
	big->lists.formats = "sSpdDioOuUxXcC%";
	big->lists.flags = "#-+ 0.";
	big->lists.len[0] = "hh";
	big->lists.len[1] = "h";
	big->lists.len[2] = "ll";
	big->lists.len[3] = "l";
	big->lists.len[4] = "j";
	big->lists.len[5] = "z";
	big->nbprint = 0;
	startbig_2(big);
}
