/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_head.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:36:53 by sderet            #+#    #+#             */
/*   Updated: 2018/09/25 18:49:38 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <float.h>

# define ABS(x) ((x) > 0 ? x : -(x))
# define RAD(x) ((double)(x) / 57.3)
# define WINDOW_X 800
# define WINDOW_Y 800
# define FOVX 60
# define FOVY 60
# define SPHERE 1
# define PLAN 2
# define i_CYL 3
# define i_CONE 4
# define DISK 5

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

typedef struct	s_camera
{
	double		xy_angle;
	double		xz_angle;
	t_dpos3d	origin;
	t_dpos3d	direction;
	t_dpos3d	upleft;
	t_dpos3d	vecdir;
	t_dpos3d	vec_horiz;
	t_dpos3d	vec_vertic;
	int			distance;
	t_dpas		pas;
	t_dpos3d	ang;
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
	double		tangent;
}				t_primitiv;

typedef struct	s_big
{
	t_image		img;
	t_mmlx		mlx;
	t_camera	camera;
	t_map		map;
	char		*name;
	t_primitiv	*objects;
	t_primitiv	light;
	double		(*intersec[5])(t_primitiv, t_dpos3d, double, t_dpos3d);
}				t_big;

void			init_big(t_big *big);

/*
**	Prints one pixel on pos in img. Colors are determined by
**	the first 3 ints in col. They are, in order, Blue Green and
**	Red. They range from 0 to 255.
*/
void			print_pixel(t_image *img, t_pos *pos, int *colo);

/*
**	Creates the image img.
*/
void			window_creation(t_image *img, t_mmlx *mlx, t_big *big);

int				std_err(int err);

int				search_param_objet(char *test, t_big *b);

double			scalar_product(t_dpos3d a, t_dpos3d b);

t_dpos3d		copy_v(t_dpos3d pos);

t_dpos3d		addition_v(t_dpos3d pos1, t_dpos3d pos2);

t_dpos3d		soustraction_v(t_dpos3d pos1, t_dpos3d pos2);

t_dpos3d		multiplication_v(t_dpos3d pos1, double a);

/*
**	Returns the distance from the origin to the intersection to a
**	cone primitive (-1 if there are no intersections).
*/
double			cone_c(t_primitiv cone, t_dpos3d ang, double a,
		t_dpos3d origin);

/*
**	Returns the distance from the origin to the intersection to a
**	cylinder primitive (-1 if there are no intersections).
*/
double			cyl_c(t_primitiv cyl, t_dpos3d ang, double a,
		t_dpos3d origin);

/*
**	Returns the distance from the origin to the intersection to a
**	plane primitive (-1 if there are no intersections).
*/
double			plan_c(t_primitiv plan, t_dpos3d ang, double a,
		t_dpos3d origin);

/*
**	Returns the distance from the origin to the intersection to a
**	disk primitive (-1 if there are no intersections).
*/
double			disk_c(t_primitiv disk, t_dpos3d ang, double a,
		t_dpos3d origin);

/*
**	Returns the distance from the origin to the intersection to a
**	sphere primitive (-1 if there are no intersections).
*/
double			sphere_c(t_primitiv sphere, t_dpos3d ang, double a,
		t_dpos3d origin);

t_dpos3d		normalize(t_dpos3d pos);

t_camera		sending_rays(t_big *big, t_camera cam, t_dpos3d ang);

t_dpos3d		normale_calc(t_camera cam, t_big *big, double b, int d);

t_dpos3d		normale_cylcone(t_camera cam, t_big *big, double b, int d);

double			light_intersections(t_big *big, int d, t_camera cam, double b);

double			test_inter(t_big *big, double *b, t_camera cam, t_dpos3d ang);

int				search_param_light(char *test, t_big *b);

void			ft_get_conf(t_big *big);

int				get_val_pos(char *position, t_dpos3d *pos);

void			get_val_obj(char *objet, t_big *b, int index);

int				checktan(char *objet, t_big *b, int index);

int				get_val_color(char *color, t_color *couleur);

int				test_position_cam(char *camera, t_big *b);

int				test_direction_cam(char *camera, t_big *b);

int				object(char *objet, int *val, int len, t_big *b);

int				put_obj(char *objet, t_big *b, int index);

#endif
