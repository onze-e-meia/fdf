/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:05:20 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 17:49:05 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	pick_palete(int i, t_color grad[5]);
static void	paint_color(t_map *map, int line, int col, int c);

t_color	intrplt_color(t_color start, t_color end, float step)
{
	t_color	color;

	color.r = start.r + (end.r - start.r) * step;
	color.g = start.g + (end.g - start.g) * step;
	color.b = start.b + (end.b - start.b) * step;
	color.a = start.a + (end.a - start.a) * step;
	return (color);
}

t_color	color_get_rgb(uint32_t color)
{
	t_color	copy;

	copy.r = ((color >> 24) & 0xFF);
	copy.g = ((color >> 16) & 0xFF);
	copy.b = ((color >> 8) & 0xFF);
	copy.a = ((color) & 0xFF);
	return (copy);
}

void	color_palete(t_map *map, int c)
{
	int	col;
	int	line;

	line = 0;
	while (line < map->info_nb[1])
	{
		col = 0;
		while (col < map->info_nb[0])
		{
			paint_color(map, line, col, c);
			col++;
		}
		line++;
	}
}

static void	paint_color(t_map *map, int line, int col, int c)
{
	t_color	grad[5];
	t_color	color;
	float	step;
	int		i;

	pick_palete(c, grad);
	step = (float) map->info_nb[2] / 4;
	i = 1;
	while (i < 5)
	{
		if (map->colorh[line][col] / step >= (i - 1)
			&& map->colorh[line][col] / step <= (i))
		{
			color = intrplt_color(grad[i - 1],
					grad[i],
					map->colorh[line][col] / (i * step));
			map->colors[line][col] = color.value;
		}
		i++;
	}
}

static void	pick_palete(int c, t_color grad[5])
{
	if (c)
	{
		grad[0] = color_get_rgb(COLOR00);
		grad[1] = color_get_rgb(COLOR01);
		grad[2] = color_get_rgb(COLOR02);
		grad[3] = color_get_rgb(COLOR03);
		grad[4] = color_get_rgb(COLOR04);
	}
	else
	{
		grad[0] = color_get_rgb(COLOR10);
		grad[1] = color_get_rgb(COLOR11);
		grad[2] = color_get_rgb(COLOR12);
		grad[3] = color_get_rgb(COLOR13);
		grad[4] = color_get_rgb(COLOR14);
	}
}
