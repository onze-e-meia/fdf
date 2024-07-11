/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:59:01 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 19:51:52 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include "MLX42/MLX42.h"

# define WIDTH 1170
# define HEIGHT 950

# define IMG_W 950
# define MENU_W 220

/* HEXADECIMAL */
# define HEX_LOW "0123456789abcdef"
# define HEX_UPP "0123456789ABCDEF"

/* COLORS */
# define WHITE 0xffffff96
# define GREY 0x9696ff96
# define FRAME_C 0x7ca84f7d
# define MENU_C 0x6e

enum e_grad00
{
	COLOR00 = 0x833ab496,
	COLOR01 = 0xc52a6296,
	COLOR02 = 0xfd1d1d96,
	COLOR03 = 0xfd5e2f96,
	COLOR04 = 0xfcb04596
};

enum e_grad01
{
	COLOR10 = 0xfdbb2d96,
	COLOR11 = 0xb2be5896,
	COLOR12 = 0x89bf7d96,
	COLOR13 = 0x59c09e96,
	COLOR14 = 0x22c1c396
};

typedef enum e_bool
{
	NO,
	YES,
}			t_bool;

typedef enum e_prj_tp
{
	ORTHO,
	PERSP,
	PART,
}			t_prj_tp;

typedef enum e_mov_proj
{
	OBJ,
	CAM,
}			t_mov_proj;

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
	int			**colorh;
	int			c;
}				t_map;

typedef struct s_window
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*menu;
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
	enum e_prj_tp	prj_tp;
	float			part;
	float			proj_m[4][4];
	float			vport_m[4][4];
}					t_cam;

typedef struct s_mov_vec
{
	float			dsp[4];
	float			ang[3];
	float			part;
	float			scl;
	float			fct;
	enum e_mov_proj	mov_proj;
	enum e_bool		redraw;
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
}		t_ctrl;

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

/* KEY HOOKS Functions */
void	resize(t_fdf *fdf);
void	object_mov(t_fdf *fdf);
void	object_scale(t_fdf *fdf);

/* KEY HOOKS Functions Utils */
void	set_fdct_mov(float *type, float mov, t_mov_vec *mov_vec);
void	set_mov(float *type, float mov, t_mov_vec *mov_vec);
void	set_part(float *type, float part, t_mov_vec *mov_vec);

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

/* COLOR HEIGHT and MALLOC ERROR Functions */
void	init_colorh(t_fdf *fdf);

/* CAMERA BUILD Functions */
void	init_view_port(float matrix[4][4], float nx, float ny);
void	init_camera(t_fdf *fdf);
void	camera_orient(t_cam *cam);
void	rebuild_cam(t_cam *cam, t_mov_vec *mov_vec);

/* CAMERA UTILS Functions */
float	aperture(int info_nb[4]);
int		img_size(int width, int height);
void	point_proj(t_cam *cam, float point[4], float new_point[4]);

/* PROJECTION Functions */
void	orthographic(float matrix[4][4], t_vol view);
void	perspective(float matrix[4][4], t_vol vw);
void	partial(float matrix[4][4], t_vol vol, float part);

/* FDF DRAW FUnctions */
void	fdf_draw(t_fdf *fdf);
void	fdf_transform(t_map *map, t_mov_vec *mov_vec);

/* LINE DRAW Functions */
void	bresenham(t_fdf *fdf, t_vrtx start, t_vrtx end);

/* COLOR Functions */
t_color	intrplt_color(t_color start, t_color end, float step);
t_color	color_get_rgb(uint32_t color);
void	color_palete(t_map *map, int i);

/* MENU Functions */
void	text_menu(t_window *win);
void	basic_keys(mlx_key_data_t keydata, void *param);
void	draw_frame(mlx_image_t *img);
void	draw_menu(t_window *win);

/* VECTOR Operation Functions */
void	init_vector(float x, float y, float z, float vector[4]);
void	vector_mult(float vector[4], float c);
void	v_plus_v(float vec_a[4], float vec_b[4], float vector[4]);
void	vector_copy(float vector[4], float copy[4]);

/* MATRIX Operation Functions */
void	matrix_unit(float matrix[4][4], float diagonal, float other);
void	matrix_vector(float matrix[4][4], float vector[4]);
void	matrix_mult(float ma[4][4], float mb[4][4], float result[4][4]);

/* TRANSFORM Functions */
void	translation(float matrix[4][4], float vector[4]);
void	scaling(float matrix[4][4], float value);

/* ROTATE Functions */
void	rotate_x(float matrix[4][4], float theta);
void	rotate_y(float matrix[4][4], float theta);
void	rotate_z(float matrix[4][4], float theta);
void	rotation(float rot[4][4], float ang[3]);

/* MATH Functions */
t_vrtx	init_vrtx(t_fdf *fdf, float ***batch, int line, int col);
float	dist_2d(int p0[4], int p1[4]);

#endif
