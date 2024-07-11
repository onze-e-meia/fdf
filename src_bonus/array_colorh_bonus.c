/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_colorh_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:23:19 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 17:48:53 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	colorh_col(t_fdf *fdf, int line);
static void	color_fst_check(t_fdf *fdf);
static void	color_snd_check(t_fdf *fdf, int line);

void	init_colorh(t_fdf *fdf)
{
	int		line;

	fdf->map.colorh = malloc(fdf->map.info_nb[1] * sizeof(int *));
	color_fst_check(fdf);
	line = 0;
	while (fdf->map.info_nb[1] > line)
	{
		colorh_col(fdf, line);
		line++;
	}
}

static void	color_fst_check(t_fdf *fdf)
{
	if (!fdf->map.colorh)
	{
		free_map_arrays(fdf);
		error_text("Could not malloc memory for COLOR HEIGHT LINE\n");
	}
}

static void	colorh_col(t_fdf *fdf, int line)
{
	int		col;

	fdf->map.colorh[line] = malloc(fdf->map.info_nb[0] * sizeof(int));
	color_snd_check(fdf, line);
	col = 0;
	while (fdf->map.info_nb[0] > col)
	{
		fdf->map.colorh[line][col] = abs((int) fdf->map.array[line][col][2]);
		col++;
	}
}

static void	color_snd_check(t_fdf *fdf, int line)
{
	if (line >= 0 && !fdf->map.colorh[line])
	{
		free_array((void ***) fdf->map.colorh, line, fdf->map.info_nb[0], 1);
		fdf->map.colorh = NULL;
		free_map_arrays(fdf);
		error_text("Could not malloc memory for COLOR HEIGHT COLUMN\n");
	}
}
