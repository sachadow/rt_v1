/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_head.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:36:53 by sderet            #+#    #+#             */
/*   Updated: 2018/06/25 17:51:03 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <math.h>

# define ABS(x) ((x) > 0 ? x : -(x))
# define RAD(x) ((double)(x) / 57.3)
# define WINDOW_X 800
# define WINDOW_Y 800
# define FOVX 60
# define FOVY 60

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct	s_pos3d
{
	int	x;
	int	y;
	int z;
}				t_pos3d;

typedef struct	s_image
{
	double	angx;
	double	angy;
	double	pasx;
	double	pasy;
	char	*map;
	int		line_len;
	int		trash;
	int		bpp;
	int		t_len;
	int		endian;
	int		maxx;
	int		maxy;
	t_pos	*pos;
}				t_image;

typedef struct	s_mmlx
{
	void *mlx;
	void *win;
	void *image;
}				t_mmlx;

typedef struct	s_dpos
{
	double	x;
	double	y;
}				t_dpos;

typedef struct	s_dpos3d
{
	double	x;
	double	y;
	double	z;
}				t_dpos3d;

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct	s_map
{
	int	**map;
	int slice;
	int	center_x;
	int	center_y;
	int	len;
	int	hgt;
	int distance;
}				t_map;

typedef	struct	s_dpas
{
	t_dpos3d	first_p;
	t_dpos3d	second_p;
}				t_dpas;

typedef struct	s_char
{
	t_dpos3d	origin;
	t_dpos3d	direction;
	t_dpos3d	upleft;
	t_dpos3d	vecdir;
	t_dpos3d	vec_horiz;
	t_dpos3d	vec_vertic;
	int			distance;
	t_dpas		pas;
	t_dpos3d	intersection;
	t_dpos3d	intersection_d;
	t_dpos3d	relative;
	int			point_colo[3];
}				t_camera;

typedef struct	s_ray
{
	t_dpos3d	origin;
	t_dpos3d	direction;
	t_dpos3d	vecdir;
	int			distance;
}				t_ray;

typedef	struct	s_primitiv
{
	int			type;
	t_dpos3d	origin;
	double		rayon;
	t_dpos3d	normale;
	t_color		color;
	double		length;
}				t_primitiv;

typedef struct	s_big
{
	t_image		img;
	t_mmlx		mlx;
	t_camera	camera;
	t_map		map;
	char		*name;
	t_primitiv	*objects;
	t_ray		*lights;
	double		(*intersec[3])(t_primitiv, t_dpos3d, double, t_dpos3d);
}				t_big;

void			init_big(t_big *big);

char			*genl(char *filename);

/*
** Function for parsing. Completes the map given as a paraneter.
*/

void			*youpi(char *filename, t_map *map);

/*
**	Prints one pixel on pos in img. Colors are determined by
**	the first 3 ints in col. They are, in order, Blue Green and
**	Red. They range from 0 to 255.
*/
void			print_pixel(t_image *img, t_pos *pos, int *colo);

/*
**	Prints one pixel on pos in img. Color is based on
**	different settings, in order to make a good looking
**	fractol.
*/
void			print_pixelc(t_image *img, t_pos *pos, t_dpos *c, int slice);

/*
**	Creates the image img.
*/
void			window_creation(t_image *img, t_mmlx *mlx, t_big *big);

int				std_err(int err, t_map *map);

int				check_wall(t_pos pos, t_map map);

void			clean_map(t_image *img);

#endif
