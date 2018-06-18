/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 17:21:10 by sderet            #+#    #+#             */
/*   Updated: 2018/06/04 19:32:15 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <wchar.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

/*
**	Structure qui donne differentes infos sur ce qu'on fait, et qui contient
**	les pointeurs sur les fonctions d'affichage.
**	formats : conversions de base, contient tout ce que l'on gere
**	flags : les 'vrais' flags, donc #, 0, +, etc
**	len : les autres flags, l, ll, h, etc
**
**	Les fonctions fun_ptr affichent des characteres selon les sflags
**	et le flags. Ils retournent un pointeur vers le prochain charactere a
**	afficher apres la fin du format.
*/
typedef struct	s_format
{
	char	*formats;
	char	*flags;
	char	**len;
	int		minim;
	int		prc;
	char	*actual_flags;
	char	*actual_len;
}				t_format;

typedef struct	s_big
{
	int			nbprint;
	va_list		ap;
	t_format	lists;
	int			compteur;
	int			sign;
	void		(*fun_ptr[15])(struct s_big *big, char *parse);
}				t_big;

int				ft_printf(const char *format, ...);

int				inflags(char parse, t_big big);

int				inacflags(char parse, t_big big);

int				inlen(char parse, t_big big);

int				informat(char parse, t_big big);

void			put_flags(char *actual_flags[10], char *parse, t_big big);

void			put_len(char *actual_len[3], char *parse, t_big big);

void			printform(t_big *big, char *parse);

void			print_char(t_big *big, char *parse);

void			print_int(t_big *big, char *parse);

void			print_up_int(t_big *big, char *parse);

void			print_percent(t_big *big, char *parse);

void			print_str(t_big *big, char *parse);

void			print_wstr(t_big *big, char *parse);

void			print_ptr(t_big *big, char *parse);

void			print_dec(t_big *big, char *parse);

void			print_hex(t_big *big, char *parse);

void			print_oct(t_big *big, char *parse);

void			print_up_hex(t_big *big, char *parse);

void			print_up_oct(t_big *big, char *parse);

int				wchar_size(wchar_t c);

void			ft_putwchar(wchar_t const c);

void			ft_putwstr(wchar_t const *str);

int				ft_wstrlen(wchar_t const *str);

int				ft_wstrsize(wchar_t const *str);

wchar_t			*ft_wstrjoin(wchar_t const *s1, wchar_t const *s2);

void			ft_wstrset(wchar_t *str, wchar_t wch, int len);

int				inside_printtype(char *parse, int a, t_big *big);

void			startbig(t_big *big);

int				dec_prc(t_big *big, char *val);

int				intprc(t_big *big, char *val);

void			loop(char *parse, char *tmp, t_big *big);

void			bigset(t_big *big);

char			*ft_printtype(char *parse, t_big *big);

int				hex_prc(t_big *big);

char			*annhex(char *str, unsigned long long val, int a, char *base);

char			*annoct(char *str, unsigned long long val, int a, char *base);

char			*annptr(char *str, unsigned long long val, int a, char *base);

char			*annint(char *str, int *minus, int a, t_big *big);

#endif
