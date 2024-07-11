/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:06:45 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 20:06:37 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"fdf.h"

static float	***batching(t_fdf *fdf, int max_y, int max_x);
static void		fdf_lines(t_fdf *fdf, float ***batch, int max_y, int max_x);
static void		remap(float rot[4][4], t_map *map);

void	fdf_draw(t_fdf *fdf)
{
	float	***batch;
	int		max_y;
	int		max_x;

	max_y = fdf->map.info_nb[1];
	max_x = fdf->map.info_nb[0];
	batch = batching(fdf, max_y, max_x);
	fdf_lines(fdf, batch, max_y, max_x);
	free_array((void ***) batch, max_y, max_x, 4);
}

static float	***batching(t_fdf *fdf, int max_y, int max_x)
{
	int		line;
	int		col;
	float	***batch;

	line = 0;
	batch = malloc(max_y * sizeof(float **));
	if (!batch)
		error_text("line BATCH malloc\n");
	while (max_y > line)
	{
		col = 0;
		batch[line] = malloc(max_x * sizeof(float *));
		if (!batch[line])
			error_text("column BATCH malloc\n");
		while (max_x > col)
		{
			batch[line][col] = malloc(4 * sizeof(float));
			if (!batch[line][col])
				error_text("element BATCH malloc\n");
			point_proj(&fdf->cam, fdf->map.array[line][col], batch[line][col]);
			col++;
		}
		line++;
	}
	return (batch);
}

static void	fdf_lines(t_fdf *fdf, float ***batch, int max_y, int max_x)
{
	int		line;
	int		col;
	t_vrtx	start;

	line = 0;
	while (max_y > line)
	{
		col = 0;
		while (max_x > col)
		{
			start = init_vrtx(fdf, batch, line, col);
			if (max_x > col + 1)
				bresenham(fdf, start, init_vrtx(fdf, batch, line, col + 1));
			if (max_y > line + 1)
				bresenham(fdf, start, init_vrtx(fdf, batch, line + 1, col));
			col++;
		}
		line++;
	}
}

void	fdf_transform(t_map *map, t_mov_vec *mov_vec)
{
	float	trans[4][4];
	float	rot[4][4];
	float	matrix[4][4];
	float	origin[4];

	vector_copy(map->obj_cent, origin);
	vector_mult(origin, -1);
	translation(trans, origin);
	rotation(rot, mov_vec->ang);
	matrix_mult(rot, trans, matrix);
	v_plus_v(map->obj_cent, mov_vec->dsp, origin);
	vector_copy(origin, map->obj_cent);
	translation(trans, map->obj_cent);
	matrix_mult(trans, matrix, rot);
	remap(rot, map);
}

static void	remap(float rot[4][4], t_map *map)
{
	int		line;
	int		col;

	line = 0;
	while (map->info_nb[1] > line)
	{
		col = 0;
		while (map->info_nb[0] > col)
			matrix_vector(rot, map->array[line][col++]);
		line++;
	}
}
