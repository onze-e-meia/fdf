/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:59:01 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 19:50:33 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include "MLX42/MLX42.h"

# define WIDTH 950
# define HEIGHT 950

/* HEXADECIMAL */
# define HEX_LOW "0123456789abcdef"
# define HEX_UPP "0123456789ABCDEF"

/* COLORS */
# define WHITE 0xffffff96
# define GREY 0x9696ff96

typedef enum e_bool
{
	NO,
	YES,
}			t_bool;

typedef union u_color
{
	uint32_t	value;
	struct
	{
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
		uint8_t	a;
	};
}				t_color;

typedef struct s_map
{
	int			info_nb[4];
	float		obj_cent[4];
	float		ang[3];
	float		***array;
	uint32_t	**colors;
}				t_map;

typedef struct s_window
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_window;

typedef struct s_vol
{
	float	left;
	float	right;
	float	top;
	float	bottom;
	float	near;
	float	far;
}			t_vol;

typedef struct s_cam
{
	float			orgn[4];
	float			ang[3];
	float			aprt;
	t_vol			vol;
	float			proj_m[4][4];
	float			vport_m[4][4];
}					t_cam;

typedef struct s_mov_vec
{
	float			dsp[4];
	float			ang[3];
}					t_mov_vec;

typedef struct s_fdf
{
	struct s_map		map;
	struct s_window		win;
	struct s_cam		cam;
	struct s_mov_vec	mov_vec;
}						t_fdf;

typedef struct s_vertex
{
	int			point[4];
	t_color		color;
}				t_vrtx;

typedef struct s_bresenham
{
	int		dx;
	int		sx;
	int		dy;
	int		sy;
	int		err;
	int		e2;
	float	dist;
	float	step;
}			t_ctrl;

/* MAIN */
void	redraw(t_fdf *fdf);

/* INIT Functions */
void	init_map(t_map *map);
void	init_window(t_fdf *fdf, char *file);

/* ERROR Functions */
void	error_text(char *str);
void	free_array(void ***array, int line, int column, int elem);
void	free_map_arrays(t_fdf *fdf);
void	mlx_check(t_fdf *fdf);
void	check_close(int file_descriptor);

/* READ FILE Functions */
void	count_columns(char *str, int *info_nb_x);
int		fdf_read(t_map *map, char *file);
int		is_hexdecimal(char ch);

/* ARRAY Functions */
void	init_array(t_map *map, int file_descriptor);

/* MALLOC ERROR Functions for Array */
void	close_gnl_fd(int fd, char *gnl_str, char *text);
void	array_fst_check(t_map *map, int fd);
void	array_snd_check(t_map *map, char *str, int fd, int line);
void	array_thr_check(t_map *map, char *str, int fd, int pos[2]);

/* CAMERA BUILD Functions */
void	init_view_port(float matrix[4][4], float nx, float ny);
void	init_camera(t_fdf *fdf);
void	camera_orient(t_cam *cam);

/* CAMERA UTILS Functions */
float	aperture(int info_nb[4]);
int		img_size(int width, int height);
void	point_proj(t_cam *cam, float point[4], float new_point[4]);

/* PROJECTION Functions */
void	orthographic(float matrix[4][4], t_vol view);

/* FDF DRAW FUnctions */
void	fdf_draw(t_fdf *fdf);
void	fdf_transform(t_map *map, t_mov_vec *mov_vec);

/* LINE DRAW Functions */
void	bresenham(t_fdf *fdf, t_vrtx start, t_vrtx end);

/* COLOR Functions */
t_color	intrplt_color(t_color start, t_color end, float step);

/* MENU Functions */
void	basic_keys(mlx_key_data_t keydata, void *param);

/* VECTOR Operation Functions */
void	vector_mult(float vector[4], float c);
void	v_plus_v(float vec_a[4], float vec_b[4], float vector[4]);
void	vector_copy(float vector[4], float copy[4]);

/* MATRIX Operation Functions */
void	matrix_unit(float matrix[4][4], float diagonal, float other);
void	matrix_vector(float matrix[4][4], float vector[4]);
void	matrix_mult(float ma[4][4], float mb[4][4], float result[4][4]);

/* TRANSFORM Functions */
void	translation(float matrix[4][4], float vector[4]);

/* ROTATE Functions */
void	rotate_x(float matrix[4][4], float theta);
void	rotate_y(float matrix[4][4], float theta);
void	rotate_z(float matrix[4][4], float theta);
void	rotation(float rot[4][4], float ang[3]);

/* MATH Functions */
t_vrtx	init_vrtx(t_fdf *fdf, float ***batch, int line, int col);
float	dist_2d(int p0[4], int p1[4]);

#endif
